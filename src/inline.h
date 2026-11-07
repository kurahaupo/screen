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

#ifndef SCREEN_ANSIINLINE_H
#define SCREEN_ANSIINLINE_H

#include <stdbool.h>	// before inline.h
#include <stdint.h>	// before inline.h
#include <string.h>	// before inline.h, for memmove & size_t

#include "ansi.h"	// before inline.h, for UTF8
#include "image.h"	// before inline.h, for struct mline

/* Inline functions moved from image.h */

#define save_mline(ml, n)  copy_mline2(&mline_old, 0, ml, 0, n)
#define copy_mline(ml, xf, xt, n) copy_mline2(ml, xt, ml, xf, n)
static inline void copy_mline2(struct mline *mt, size_t ot, struct mline const *mf, size_t of, size_t n)
{
	memmove(mt->image + ot, mf->image + of, n * sizeof *mt->image);
	memmove(mt->attr + ot, mf->attr + of, n * sizeof *mt->attr);
	memmove(mt->font + ot, mf->font + of, n * sizeof *mt->font);
	memmove(mt->colorbg + ot, mf->colorbg + of, n * sizeof *mt->colorbg);
	memmove(mt->colorfg + ot, mf->colorfg + of, n * sizeof *mt->colorfg);
}

static inline void clear_mline(struct mline *ml, size_t o, size_t n)
{
        for (size_t i = 0; i<n; ++i)
		ml->image[i+o] = ' ';
	memset(ml->attr + o, 0, n * sizeof *ml->attr);
	memset(ml->font + o, 0, n * sizeof *ml->font);
	memset(ml->colorbg + o, 0, n * sizeof *ml->colorbg);
	memset(ml->colorfg + o, 0, n * sizeof *ml->colorfg);
}

static inline bool cmp_mline(struct mline const *ml1, struct mline const *ml2, size_t x)
{
	return ml1->image[x] == ml2->image[x]
	    && ml1->attr[x] == ml2->attr[x]
	    && ml1->font[x] == ml2->font[x]
	    && ml1->colorbg[x] == ml2->colorbg[x]
	    && ml1->colorfg[x] == ml2->colorfg[x];
}

static inline bool cmp_mchar(struct mchar const *mc1, struct mchar const *mc2)
{
	return mc1->image == mc2->image
	    && mc1->attr == mc2->attr
	    && mc1->font == mc2->font
	    && mc1->colorbg == mc2->colorbg
	    && mc1->colorfg == mc2->colorfg;
}

static inline bool cmp_mchar_mline(struct mchar const *mc, struct mline const *ml, size_t x)
{
	return mc->image == ml->image[x]
	    && mc->attr == ml->attr[x]
	    && mc->font == ml->font[x]
	    && mc->colorbg == ml->colorbg[x]
	    && mc->colorfg == ml->colorfg[x];
}

static inline void copy_mchar2mline(struct mchar const *mc, struct mline *ml, size_t x)
{
	ml->image[x] = mc->image;
	ml->attr[x] = mc->attr;
	ml->font[x] = mc->font;
	ml->colorbg[x] = mc->colorbg;
	ml->colorfg[x] = mc->colorfg;
}

static inline void copy_mline2mchar(struct mchar *mc, struct mline const *ml, size_t x)
{
	mc->image = ml->image[x];
	mc->attr = ml->attr[x];
	mc->font = ml->font[x];
	mc->colorbg = ml->colorbg[x];
	mc->colorfg = ml->colorfg[x];
	mc->mbcs = 0;
}

/* Inline functions moved from ansi.h */

static inline bool is_dw_font(int f)
{
	return f && (f & 0x60) == 0;
}

static inline bool dw_left(struct mline *ml, int x, int enc)
{
	font_t *font = ml->font;
	font_t fx = font[x];
	return enc == UTF8 ? font[x + 1] == 0xff && ml->image[x + 1] == 0xff
			   : (fx & 0xe0) == 0 && (fx & 0x1f) != 0;
			// : (fx-1 & 0xff) < 0x1f;	/* equivalent */
}

static inline bool dw_right(struct mline *ml, int x, int enc)
{
	font_t *font = ml->font;
	font_t fx = font[x];
	return enc == UTF8 ? fx == 0xff && ml->image[x] == 0xff
			   : (fx & 0xe0) == 0x80;
	/* TODO: check whether that should be «(fx & 0xc0) == 0x80» */
}

#endif
