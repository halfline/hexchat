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
*/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <glib.h>

/* This is an especially bad way to get the info
 * from mpc as it gives almost no information */
static char *
mpc_cb (void)
{
	HWND hWnd = FindWindowW ("MediaPlayerClassicW", NULL);
	if (hWnd != NULL)
	{
		wchar_t window_text[1024] = {0};

		if (GetWindowTextW (hWnd, window_text, sizeof(window_text)))
		{
			char *str;

			str = g_utf16_to_utf8 (window_text, -1, NULL, NULL, NULL);

			/* Nothing playing */
			if (strstr (str, "Media Player Classic") != NULL)
			{
				g_free (str);
				return NULL;
			}

			return str;
		}
	}
	return NULL;
}
