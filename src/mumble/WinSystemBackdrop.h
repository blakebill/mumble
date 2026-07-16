// Copyright The Mumble Developers. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file at the root of the
// Mumble source tree or at <https://www.mumble.info/LICENSE>.

#ifndef MUMBLE_MUMBLE_WINSYSTEMBACKDROP_H_
#define MUMBLE_MUMBLE_WINSYSTEMBACKDROP_H_

class QWidget;

namespace WinSystemBackdrop {

/// Returns whether the current Windows version supports Mica.
bool isMicaAvailable();

/// Applies the Windows 11 Mica backdrop to the given top-level widget.
///
/// Returns false without modifying the widget on unsupported systems or when
/// the native window has not been created yet.
bool applyMica(QWidget *widget, bool darkMode);

} // namespace WinSystemBackdrop

#endif // MUMBLE_MUMBLE_WINSYSTEMBACKDROP_H_
