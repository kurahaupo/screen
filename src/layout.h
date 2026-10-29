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

#ifndef SCREEN_LAYOUT_H
#define SCREEN_LAYOUT_H

#include "layer.h"	// before canvas.h, for struct Layer
#include "sched.h"	// before canvas.h & here, for struct Event
#include "canvas.h"	// for struct Canvas

#define MAXLAY 10

struct Window;

typedef struct Layout {
	struct Layout *lay_next;
	char *lay_title;
	int lay_number;
	struct Canvas lay_canvas;
	struct Canvas *lay_forecv;
	struct Canvas *lay_cvlist;
	int lay_autosave;
} Layout;

void FreeLayoutCv(struct Canvas *c);
Layout *CreateLayout(char *, int);
void AutosaveLayout(Layout *);
void LoadLayout(Layout *);
void NewLayout(char *, int);
void SaveLayout(char *, struct Canvas *);
void ShowLayouts(int);
Layout *FindLayout(char *);
void UpdateLayoutCanvas(struct Canvas *, struct Window *);
Layout *CreateLayout(char *, int);
void RemoveLayout(Layout *);
int LayoutDumpCanvas(struct Canvas *, char *);

void RenameLayout(Layout *, const char *);
int RenumberLayout(Layout *, int);

/* global variables */

extern Layout *layout_attach, *layout_last, layout_last_marker;
extern Layout *layouts;

#endif				/* SCREEN_LAYOUT_H */
