// Copyright The Mumble Developers. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file at the root of the
// Mumble source tree or at <https://www.mumble.info/LICENSE>.

#include "WinSystemBackdrop.h"

// Must be included before other Windows headers
#include "win.h"

#include <dwmapi.h>

#include <QtCore/QOperatingSystemVersion>
#include <QtGui/QWindow>
#include <QtWidgets/QWidget>

namespace {

// These constants are intentionally kept local instead of using their SDK
// names. That allows Mumble to keep building with older Windows SDKs while the
// attributes are detected at runtime.
constexpr DWORD kDwmwaUseImmersiveDarkMode = 20;
constexpr DWORD kDwmwaSystemBackdropType   = 38;
constexpr DWORD kDwmwaMicaEffect           = 1029;

constexpr int kDwmSystemBackdropMainWindow = 2;

} // namespace

namespace WinSystemBackdrop {

bool isMicaAvailable() {
	return QOperatingSystemVersion::current()
		   >= QOperatingSystemVersion(QOperatingSystemVersion::Windows, 10, 0, 22000);
}

bool applyMica(QWidget *widget, bool darkMode) {
	if (!widget || !isMicaAvailable() || !widget->windowHandle()) {
		return false;
	}

	const HWND window = reinterpret_cast< HWND >(widget->windowHandle()->winId());
	if (!window) {
		return false;
	}

	const BOOL useDarkMode = darkMode ? TRUE : FALSE;
	DwmSetWindowAttribute(window, kDwmwaUseImmersiveDarkMode, &useDarkMode, sizeof(useDarkMode));

	const int backdropType = kDwmSystemBackdropMainWindow;
	HRESULT result = DwmSetWindowAttribute(window, kDwmwaSystemBackdropType, &backdropType, sizeof(backdropType));

	if (FAILED(result)) {
		// Windows 11 21H2 predates DWMWA_SYSTEMBACKDROP_TYPE, but supports
		// the legacy Mica attribute. Unknown attributes fail harmlessly.
		const BOOL enableMica = TRUE;
		result                = DwmSetWindowAttribute(window, kDwmwaMicaEffect, &enableMica, sizeof(enableMica));
	}

	return SUCCEEDED(result);
}

} // namespace WinSystemBackdrop
