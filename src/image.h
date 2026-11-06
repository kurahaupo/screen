/* Copyright (c) 2008, 2009
 *      Juergen Weigert (jnweiger@immd4.informatik.uni-erlangen.de)
 *      Michael Schroeder (mlschroe@immd4.informatik.uni-erlangen.de)
 *      Micah Cowan (micah@cowan.name)
 *      Sadrul Habib Chowdhury (sadrul@users.sourceforge.net)
 * Copyright (c) 1993-2002, 2003, 2005, 2006, 2007
 *      Juergen Weigert (jnweiger@immd4.informatik.uni-erlangen.de)
 *      Michael Schroeder (mlschroe@immd4.informatik.uni-erlangen.de)
 * Copyright (c) 1987 Oliver Laumann
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program (see the file COPYING); if not, see
 * https://www.gnu.org/licenses/, or contact Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02111-1301  USA
 *
 ****************************************************************
 * $Id$ GNU
 */

#ifndef SCREEN_IMAGE_H
#define SCREEN_IMAGE_H

#include <stdint.h>

/* structure representing single cell of terminal */
struct mchar {
	uint32_t image;		/* actual letter like a, b, c ... as Unicode code point */
	uint32_t attr;		/* attributes - bold, standout etc. */
	uint32_t font;		/* font :) */
	uint32_t colorbg;	/* background color */
	uint32_t colorfg;	/* foreground color */
	uint32_t mbcs;		/* used for multi byte character sets; TODO: possible to remove? use image now that it has 32 bits */
};

struct mline {
	uint32_t *image;
	uint32_t *attr;
	uint32_t *font;
	uint32_t *colorbg;
	uint32_t *colorfg;
};

enum {
	REND_BELL = 0,
	REND_MONITOR,
	REND_SILENCE,
	NUM_RENDS
};

#endif				/* SCREEN_IMAGE_H */

