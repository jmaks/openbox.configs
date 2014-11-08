/* 
 * xicursorset - set cursor image for an XInput2 pointer
 *
 * Copyright (C) 2010 Antonio Ospite <ospite@studenti.unina.it>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <X11/Xcursor/Xcursor.h>
#include <X11/extensions/XInput2.h>
#include <assert.h>

int main(int argc, char *argv[])
{
	Display* dpy;
	int screen;
	Window win;

	int ptrid;
	char *shape_name;
	int shape;
	int size;
	char *theme;
	XcursorImage *image;
	Cursor cursor;

	if (argc < 3 || argc > 4) {
		printf("usage: %s <ptrid> <shape> [<theme>]\n",
				basename(argv[0]));
		return 1;
	}

	/* TODO: verify that the pointer id is sane and
	 * that it is a master pointer
	 */
	ptrid = atoi(argv[1]);

	shape_name = argv[2];
	shape = XcursorLibraryShape(shape_name);
	if (shape < 0) {
		fprintf(stderr, "Invalid shape name.\n");
		return EXIT_FAILURE;
	}

	dpy = XOpenDisplay(NULL);
	assert(dpy != NULL);

	/* TODO: check return value? */
	screen = DefaultScreen(dpy);

	/* TODO: check return value? */
	win = RootWindow(dpy, screen);

	size = XcursorGetDefaultSize(dpy);
	if (size == 0) {
		fprintf(stderr, "Can't get cursor size.\n");
		return EXIT_FAILURE;
	}


	if (argc == 4)
		theme = argv[3];
	else
		theme = XcursorGetTheme(dpy);
		if (theme == NULL) {
			fprintf(stderr, "Can't get cursor theme.\n");
			return EXIT_FAILURE;
		}

	image = XcursorShapeLoadImage(shape, theme, size);
	if (image == NULL) {
		fprintf(stderr, "Can't get cursor image, check <shape> or <theme>.\n");
		return EXIT_FAILURE;
	}

	cursor = XcursorImageLoadCursor(dpy, image);

	XIDefineCursor(dpy, ptrid, win, cursor);
	XFlush(dpy);

	XCloseDisplay(dpy);
	return 0;
}
