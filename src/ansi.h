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

#ifndef SCREEN_ANSI_H
#define SCREEN_ANSI_H

#include <stdbool.h>	//
#include <stddef.h>	// for size_t
#include <stdint.h>	//

#include "aatypes.h"

/*
 *  Parser state
 */
/* keep state_t and state_t_string in sync! */
typedef enum state_e {
	LIT,			/* LITeral input */
	ESC,			/* start of ESCape sequence */
	ASTR,			/* start of control STRing */
	STRESC,			/* ESC seen in control STRing */
	CTL_SEQ,		/* Reading arguments in Control Sequence (CSI Pn ; … KEY) */
	PRIN,			/* Printer mode */
	PRINESC,		/* ESC seen in PRINter mode, looking for '[4i' */
	PRINCSI,		/* CSI seen in PRINter mode, looking for '4i' */
	PRIN4			/* CSI 4 seen in PRINter mode, looking for 'i' */
} state_t;

#define MAX_CS_PARAMS	64	/* ISO-6429 specifies 16, and recommends
				 * silently ignoring any more, but we
				 * need more to correctly support
				 * colon-separated sub-parameters;
				 * furthermore the ISO limit is out of
				 * step with common usage. */

/* keep string_t and string_t_string in sync! */
typedef enum string_e {
	NONE,
	DCS,			/* Device Control String */
	OSC,			/* Operating System Command */
	APC,			/* Application Program Command
				 *  - used for status change */
	PM,			/* Privacy Message */
	AKA,			/* Title for current screen */
	GM,			/* Global Message (to every display) */
	STATUS			/* User hardstatus line */
} string_t;

/*
 *  Types of movement used by GotoPos()
 */
typedef enum move_e {
	M_NONE,
	M_UP,
	M_CUP,
	M_DO,
	M_CDO,
	M_LE,
	M_CLE,
	M_RI,
	M_CRI,
	M_RW,
	M_CR			/* CR and rewrite */
} move_t;

#define EXPENSIVE	1000

#define G0		0
#define G1		1
#define G2		2
#define G3		3

#define ASCII		0

#define STATLINE()		(statuspos.row == STATUS_BOTTOM ? D_height-1 : 0)
#define	STATCOL(width, len)	(statuspos.col == STATUS_LEFT ? 0 : D_width - D_status_len - 2)

#define FONT_KANJI	('B' & 037)
#define FONT_KANJI0212	('D' & 037)
#define FONT_KANA	'I'
#define FONT_LATIN1	0
#define FONT_CN		1
#define FONT_HANGUL	3
#define FONT_BIG5	030
#define FONT_GBK	031

#define EUC_JP		1
#define SJIS		2
#define EUC_KR		3
#define EUC_CN		4
#define BIG5		5
#define KOI8R		6
#define CP1251		7
#define GBK		20
#define KOI8U		21

#define EUC		EUC_JP


#define UTF8		8

#define UCS_REPL	0xfffd	/* character for illegal codes */
#define UCS_REPL_DW	0xff1f	/* character for illegal codes */
#define UCS_HIDDEN	0xffff

typedef enum sgr3_mode_e {
	SGR3_UNSET = 0,
	SGR3_ITALIC = 1,
	SGR3_STANDOUT = 2,
	SGR3_DEFAULT = SGR3_ITALIC, /* legacy compatibility? */
} sgr3_mode_t;

const char *sgr3_mode_desc(sgr3_mode_t);

struct Window;

void ResetAnsiState(struct Window *);
void ResetCharsets(struct Window *);
void WriteString(struct Window *, char *, size_t);
void ChangeAKA(struct Window *, char *, size_t);
void SetCharsets(struct Window *, char *);
int GetAnsiStatus(struct Window *, char *);
void WNewAutoFlow(struct Window *, int);
void WBell(struct Window *, bool);
void WMsg(struct Window *, int, char *);
int MFindUsedLine(struct Window *, int, int);

/* global variables */

extern bool visual_bell;
extern bool use_altscreen;
extern bool use_hardstatus;

extern char *printcmd;

extern image_t *blank;
extern attr_mask_t *null_attr;
extern color_t *null_color;
extern font_t *null_font;

extern uint64_t renditions[];

extern const int Z0width;
extern const int Z1width;

extern struct mline mline_blank;
extern struct mline mline_null;
extern struct mline mline_old;

extern struct mchar mchar_so;
extern struct mchar mchar_blank;
extern struct mchar mchar_null;

#endif				/* SCREEN_ANSI_H */
