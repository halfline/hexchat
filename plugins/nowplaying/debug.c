/*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
*
*/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wchar.h>
#include <glib.h>
#include "hexchat-plugin.h"

extern hexchat_plugin *ph;

static BOOL CALLBACK 
debug_enum_func (HWND hwnd, LPARAM param)
{
	wchar_t window_text[1024] = {0};
	wchar_t window_class[1024] = {0};

	if (GetWindowTextW (hwnd, window_text, sizeof(window_text))
		&& GetClassNameW (hwnd, window_class, sizeof(window_class)))
	{
		if (wcscmp (window_class, L"IME") && wcscmp (window_class, L"MSCTFIME UI"))
		{
			char *text, *cls;

			text = g_utf16_to_utf8 (window_text, -1, NULL, NULL, NULL);
			cls = g_utf16_to_utf8 (window_class, -1, NULL, NULL, NULL);

			hexchat_printf (ph, "Class: %s | Title: %s", cls, text);

			g_free (text);
			g_free (cls);
		}
	}

	return 1;
}

static char *
debug_cb (void)
{
	EnumWindows (debug_enum_func, 0);
	return NULL;
}
