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
 */

#include "config.h"

#include "comm.h"

/* Do not complain about (intentional) use of default initialisers */
#if defined __GNUC__ && (__GNUC__ * 100 + __GNUC_MINOR__ >= 406) \
 || defined __clang__
  /* ‘#pragma GCC diagnostic ignored’ has been supported since GCC v4.6, and
   * since clang v1.0 */
# pragma GCC diagnostic ignored "-Wmissing-field-initializers"
  /* NB: ensure this list of pragmas remains sorted. */
#elif defined(_MSC_VER)
# pragma warning(disable : 4351 5262) /* Suppresses uninitialized array/struct element warnings */
#endif

/* Note that the #defines in comm.h are generated from the quoted strings in
 * the following statement using a fairly simply AWK match; take care if
 * changing the layout of this initialiser */
struct comm comms[RC_LAST + 1] =
{
  { "acladd",		ARGS_RANGE(1,4) },
  { "aclchg",		ARGS_RANGE(2,3) },
  { "acldel",		ARGS(1) },
  { "aclgrp",		ARGS_RANGE(1,2) },
  { "aclumask",		ARGS_ATLEAST(1) },
  { "activity",		ARGS(1) },
  { "addacl",		ARGS_RANGE(1,4) },
  { "allpartial",	ARGS(1)		| NEED_DISPLAY },
  { "altscreen",	ARGS_RANGE(0,1) },
  { "at",		ARGS_ATLEAST(2) },
  { "auth",		ARGS(1) },
  { "autodetach",	ARGS(1) },
  { "autonuke",		ARGS(1)		| NEED_DISPLAY },
  { "backtick",		ARGS_ATLEAST(1) },
  { "bce",		ARGS_RANGE(0,1)	| NEED_FORE },
  { "bell",		ARGS_RANGE(0,1) },
  { "bell_msg",		ARGS_RANGE(0,1) },
  { "bind",		ARGS_ATLEAST(1) },
  { "bindkey",		ARGS_ATLEAST(0) },
  { "blanker",		ARGS(0)		| NEED_DISPLAY },
  { "blankerprg",	ARGS_ATLEAST(0) },
  { "break",		ARGS_RANGE(0,1)	| NEED_FORE },
  { "breaktype",	ARGS_RANGE(0,1)	| NEED_FORE },
  { "bufferfile",	ARGS_RANGE(0,1) },
  { "bumpleft",		ARGS(0)		| NEED_FORE },
  { "bumpright",	ARGS(0)		| NEED_FORE },
  { "c1",		ARGS_RANGE(0,1)	| NEED_FORE },
  { "caption",		ARGS_RANGE(1,3) },
  { "chacl",		ARGS_RANGE(2,3) },
  { "charset",		ARGS(1)		| NEED_FORE },
  { "chdir",		ARGS_RANGE(0,1) },
  { "cjkwidth",		ARGS_RANGE(0,1) },
  { "clear",		ARGS(0)		| NEED_FORE },
  { "collapse",		ARGS(0) },
  { "colon",		ARGS_RANGE(0,1)	| NEED_LAYER },
  { "command",		ARGS(0)|ARGS(2)	| NEED_DISPLAY },
  { "compacthist",	ARGS_RANGE(0,1) },
  { "console",		ARGS_RANGE(0,1)	| NEED_FORE },
  { "copy",		ARGS(0)		| NEED_FORE | NEED_DISPLAY },
  { "crlf",		ARGS_RANGE(0,1) },
  { "defautonuke",	ARGS(1) },
  { "defbce",		ARGS(1) },
  { "defbreaktype",	ARGS_RANGE(0,1) },
  { "defc1",		ARGS(1) },
  { "defcharset",	ARGS_RANGE(0,1) },
  { "defdynamictitle",	ARGS(1) },
  { "defencoding",	ARGS(1) },
  { "defescape",	ARGS(1) },
  { "defflow",		ARGS_RANGE(1,2) },
  { "defgr",		ARGS(1) },
  { "defhstatus",	ARGS_RANGE(0,1) },
  { "defkanji",		ARGS(1) },
  { "deflog",		ARGS(1) },
#if defined(ENABLE_UTMP)
  { "deflogin",		ARGS(1) },
#endif
  { "defmode",		ARGS(1) },
  { "defmonitor",	ARGS(1) },
  { "defmousetrack",	ARGS(1) },
  { "defnonblock",	ARGS(1) },
  { "defobuflimit",	ARGS(1) },
  { "defscrollback",	ARGS(1) },
  { "defshell",		ARGS(1) },
  { "defsilence",	ARGS(1) },
  { "defslowpaste",	ARGS(1) },
  { "defutf8",		ARGS(1) },
  { "defwrap",		ARGS(1) },
  { "defwritelock",	ARGS(1) },
  { "detach",		ARGS_RANGE(0,1)	| NEED_DISPLAY },
  { "digraph",		ARGS_RANGE(0,2)	| NEED_LAYER },
  { "dinfo",		ARGS(0)		| NEED_DISPLAY },
  { "displays",		ARGS(0)		| NEED_LAYER },
  { "dumptermcap",	ARGS(0)		| NEED_FORE },
  { "dynamictitle",	ARGS(1) },
  { "echo",		ARGS_RANGE(1,2)	| CAN_QUERY },
  { "encoding",		ARGS_RANGE(1,2) },
  { "escape",		ARGS(1) },
  { "eval",		ARGS_ATLEAST(1) },
  { "exec",		ARGS_ATLEAST(0) },
  { "fit",		ARGS(0)		| NEED_DISPLAY },
  { "flow",		ARGS_RANGE(0,1)	| NEED_FORE },
  { "focus",		ARGS_RANGE(0,1)	| NEED_DISPLAY },
  { "focusminsize",	ARGS(0)|ARGS(2) },
  { "gr",		ARGS_RANGE(0,1)	| NEED_FORE },
  { "group",		ARGS_RANGE(0,1)	| NEED_FORE },
  { "hardcopy",		ARGS_RANGE(0,2)	| NEED_FORE },
  { "hardcopy_append",	ARGS(1) },
  { "hardcopydir",	ARGS_RANGE(0,1) },
  { "hardstatus",	ARGS_RANGE(0,2) },
  { "height",		ARGS_RANGE(0,3) },
  { "help",		ARGS(0)|ARGS(2)	| NEED_LAYER },
  { "history",		ARGS(0)		| NEED_DISPLAY | NEED_FORE },
  { "hstatus",		ARGS(1)		| NEED_FORE },
  { "idle",		ARGS_ATLEAST(0) },
  { "ignorecase",	ARGS_RANGE(0,1) },
  { "info",		ARGS(0)		| CAN_QUERY | NEED_LAYER },
  { "kanji",		ARGS_RANGE(1,2)	| NEED_FORE },
  { "kill",		ARGS_RANGE(0,1)	| NEED_FORE },
  { "lastmsg",		ARGS(0)		| CAN_QUERY | NEED_DISPLAY },
  { "layout",		ARGS_ATLEAST(1) },
  { "license",		ARGS(0)		| NEED_LAYER },
  { "lockscreen",	ARGS(0)		| NEED_DISPLAY },
  { "log",		ARGS_RANGE(0,1)	| NEED_FORE },
  { "logfile",		ARGS_RANGE(0,2) },
#if defined(ENABLE_UTMP)
  { "login",		ARGS_RANGE(0,1)	| NEED_FORE },
#endif
  { "logtstamp",	ARGS_RANGE(0,2) },
  { "mapdefault",	ARGS(0)		| NEED_DISPLAY },
  { "mapnotnext",	ARGS(0)		| NEED_DISPLAY },
  { "maptimeout",	ARGS_RANGE(0,1) },
  { "markkeys",		ARGS(1) },
  { "meta",		ARGS(0)		| NEED_LAYER },
  { "monitor",		ARGS_RANGE(0,1)	| NEED_FORE },
  { "mousetrack",	ARGS_RANGE(0,1) | NEED_DISPLAY },
  { "msgminwait",	ARGS(1) },
  { "msgwait",		ARGS(1) },
  { "multiinput",	ARGS_RANGE(0,1) },
  { "multiuser",	ARGS(1) },
  { "next",		ARGS(0) },
  { "nonblock",		ARGS_RANGE(0,1)	| NEED_DISPLAY },
  { "number",		ARGS_RANGE(0,1)	| CAN_QUERY|NEED_FORE },
  { "obuflimit",	ARGS_RANGE(0,1)	| NEED_DISPLAY },
  { "only",		ARGS(0)		| NEED_DISPLAY },
  { "other",		ARGS(0) },
  { "parent",		ARGS(0) },
  { "partial",		ARGS_RANGE(0,1)	| NEED_FORE },
  { "paste",		ARGS_RANGE(0,2)	| NEED_LAYER },
  { "pastefont",	ARGS_RANGE(0,1) },
  { "pow_break",	ARGS_RANGE(0,1)	| NEED_FORE },
  { "pow_detach",	ARGS_RANGE(0,1)	| NEED_DISPLAY },
  { "pow_detach_msg",	ARGS_RANGE(0,1) },
  { "prev",		ARGS(0) },
  { "printcmd",		ARGS_RANGE(0,1) },
  { "process",		ARGS_RANGE(0,1)	| NEED_DISPLAY },
  { "quit",		ARGS_RANGE(0,1) },
  { "readbuf",		ARGS_RANGE(0,3) },
  { "readreg",		ARGS_ATLEAST(0) },
  { "redisplay",	ARGS(0)		| NEED_DISPLAY },
  { "register",		ARGS(2)|ARGS(4) },
  { "remove",		ARGS(0)		| NEED_DISPLAY },
  { "removebuf",	ARGS(0) },
  { "rendition",	ARGS(2) },
  { "reset",		ARGS(0)		| NEED_FORE },
  { "resize",		ARGS_ATLEAST(0)	| NEED_DISPLAY },
  { "screen",		ARGS_ATLEAST(0) },
  { "scrollback",	ARGS(1)		| NEED_FORE },
  { "select",		ARGS_RANGE(0,1)	| CAN_QUERY },
  { "sessionname",	ARGS_RANGE(0,1) },
  { "setenv",		ARGS_RANGE(0,2) },
  { "setsid",		ARGS(1) },
  { "shell",		ARGS(1) },
  { "shelltitle",	ARGS(1) },
  { "silence",		ARGS_RANGE(0,1)	| NEED_FORE },
  { "silencewait",	ARGS(1) },
  { "sleep",		ARGS(1) },
  { "slowpaste",	ARGS_RANGE(0,1)	| NEED_FORE },
  { "sorendition",	ARGS_RANGE(0,2) },
  { "sort",		ARGS(0) },
  { "source",		ARGS(1) },
  { "split",		ARGS_RANGE(0,1)	| NEED_DISPLAY },
  { "startup_message",	ARGS(1) },
  { "status",		ARGS_RANGE(1,2) },
  { "stuff",		ARGS_RANGE(0,2)	| NEED_LAYER },
  { "su",		ARGS_RANGE(0,2)	| NEED_DISPLAY },
  { "suspend",		ARGS(0)		| NEED_DISPLAY },
  { "term",		ARGS(1) },
  { "termcap",		ARGS_RANGE(2,3) },
  { "termcapinfo",	ARGS_RANGE(2,3) },
  { "terminfo",		ARGS_RANGE(2,3) },
  { "title",		ARGS_RANGE(0,1) | CAN_QUERY | NEED_FORE },
  { "truecolor",	ARGS(1) },
  { "umask",		ARGS_ATLEAST(1) },
  { "unbindall",	ARGS(0) },
  { "unsetenv",		ARGS(1) },
  { "utf8",		ARGS_RANGE(0,2)	| NEED_FORE },
  { "vbell",		ARGS_RANGE(0,1) },
  { "vbell_msg",	ARGS_RANGE(0,1) },
  { "vbellwait",	ARGS(1) },
  { "verbose",		ARGS_RANGE(0,1) },
  { "version",		ARGS(0) },
  { "wall",		ARGS(1)		| NEED_DISPLAY },
  { "width",		ARGS_RANGE(0,3) },
  { "windowlist",	ARGS_RANGE(0,2) },
  { "windows",		ARGS_RANGE(0,1)	| CAN_QUERY },
  { "wrap",		ARGS_RANGE(0,1)	| NEED_FORE },
  { "writebuf",		ARGS_RANGE(0,3) },
  { "writelock",	ARGS_RANGE(0,1)	| NEED_FORE },
  { "xoff",		ARGS(0)		| NEED_LAYER },
  { "xon",		ARGS(0)		| NEED_LAYER },
  { "zmodem",		ARGS_RANGE(0,2) },
  { "zombie",		ARGS_RANGE(0,2) },
  { "zombie_timeout",	ARGS(1) },
};
