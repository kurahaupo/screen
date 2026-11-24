#! /bin/sh

_=${AWK:=awk}
_=${CC:=cc}
_=${srcdir:=.}

LC_ALL=C
export LC_ALL

# Tell the compiler where to look for ‘#include "filename.h"’, but preferably
# without changing where it looks for ‘#include <filename.h>’.
case /$CC in
    */gcc | */clang) IQ=-iquote ;;
    *)               IQ=-I ;;
esac

source_file=$srcdir/comm.c

mkdir tmp$$
trap 'rm -rf tmp$$' 0

{

# Some version of ‘comm.h’ must be visible to the following invocation of the
# compiler's preprocessor; this can be either the empty tmp$$/comm.h currently
# under construction, or the previously built ./comm.h; either is OK.
#
# Do not re-order the compilation relative to the other steps, lest you
# encounter a dangling #ifdef in the partially build tmp$$/comm.h.

$CC -E $IQ./tmp$$ $IQ. "$IQ$srcdir" "$source_file" > tmp$$/comm.cpp || exit $?

cat << EOF
/*
 * This file is automagically created from $source_file by $0 -- DO NOT EDIT
 */

#ifndef SCREEN_COMM_H
#define SCREEN_COMM_H

#include "acls.h"

struct comm {
	char *name;
	int flags;
	AclBits userbits[ACL_BITS_PER_CMD];
};

extern struct comm comms[];

#define ARGS_ANY		5	/* interpreted as "more than 4" */

#define ARGS(n)			(1U << (n))
#define NEED_FORE		0x1000U		/* command needs a fore window */
#define NEED_DISPLAY		0x2000U		/* command needs a display */
#define NEED_LAYER		0x4000U		/* command needs a layer */
#define CAN_QUERY		0x8000U		/* command can be queried using ‘-Q’ to print a result to stdout */

#define ARGS_RANGE(lo,hi)	(ARGS(hi+1) - ARGS(lo))
#define ARGS_ATLEAST(lo)	ARGS_RANGE(lo, ARGS_ANY)
#define ARGS_MASK		ARGS_ATLEAST(0)
#define ARGS_MORE		ARGS(ARGS_ANY)

struct action {
	int nr;
	char **args;
	int *argl;
	int quiet;		/* Suppress (currently unused)
				 * 0x01 - Error message
				 * 0x02 - Normal message
				 */
};

#define RC_ILLEGAL -1

EOF

< $source_file >&2 \
$AWK -v source_file="$source_file" '
/^[[:space:]]+[{][[:space:]]*"/ {   #}
    if (split($0, f, "\"") < 3) {
        printf "*** ERROR: invalid line %u in %s!!!\n\n", NR, source_file;
        exit 1;
    }
    if (old > f[2]) {
        printf "*** ERROR: %s on line %u should precede %s on line %u in %s!!!\n\n", f[2], NR, old, NR-1, source_file;
        exit 1;
    }
    old = f[2];
}
' || exit $?

< tmp$$/comm.cpp \
$AWK -v source_file="$source_file" '
/^[[:space:]]*[{][[:space:]]*"/ {    #}
    split($0, f, "\"")
    printf "#define %-15s %u\t/* line %u in %s */\n", "RC_" toupper(f[2]), i++, NR, source_file;
}
END {
    printf "\n"
    printf "#define %-15s %u\n", "RC_LAST", i-1;
}
'

cat <<EOF

#endif				/* SCREEN_COMM_H */
EOF
} > tmp$$/comm.h || exit $?

chmod a-w tmp$$/comm.h
mv -f tmp$$/comm.h comm.h
