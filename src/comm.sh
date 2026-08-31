#! /bin/sh

if test -z "$AWK"; then
  AWK=awk
fi
if test -z "$CC"; then
  CC=cc
fi
if test -z "$srcdir"; then
  srcdir=.
fi

LC_ALL=C
export LC_ALL

source_file=$srcdir/comm.c

rm -f comm.h
cat << EOF > comm.h
/*
 * This file is automagically created from $source_file by $0 -- DO NOT EDIT
 */

#ifndef SCREEN_COMM_H
#define SCREEN_COMM_H

#include "acls.h"

struct comm
{
  char *name;
  int flags;
  AclBits userbits[ACL_BITS_PER_CMD];
};

extern struct comm comms[];

#define ARGS_ANY		5		/* interpreted as "more than 4" */

#define ARGS(n)			(1U << (n))
#define XXARG(n)		(1U << ARGS_ANY+(n))
#define NEED_FORE		0x1000U		/* command needs a fore window */
#define NEED_DISPLAY		0x2000U		/* command needs a display */
#define NEED_LAYER		0x4000U		/* command needs a layer */
#define CAN_QUERY		0x8000U		/* command can be queried using ‘-Q’ to print a result to stdout */

#define ARGS_RANGE(lo,hi)	(ARGS(hi+1) - ARGS(lo))
#define ARGS_ATLEAST(lo)	ARGS_RANGE(lo, ARGS_ANY)
#define ARGS_MASK		ARGS_ATLEAST(0)
#define ARGS_MORE		ARGS(ARGS_ANY)

struct action
{
  int nr;
  char **args;
  int *argl;
  int quiet;	/* Suppress (currently unused)
		   0x01 - Error message
		   0x02 - Normal message
		*/
};

#define RC_ILLEGAL -1

#endif /* SCREEN_COMM_H */

EOF
$AWK < $source_file >> comm.h '
/^  [{] ".*/	{   if (old > $2) {
		printf("***ERROR: %s <= %s !!!\n\n", $2, old);
		exit 1;
	    }
	old = $2;
	}
'

$CC -E -I. "-I$srcdir" "$source_file" > comm.cpp || exit $?
sed < comm.cpp \
  -n \
  -e '/^ *{ "/y/abcdefghijklmnopqrstuvwxyz/ABCDEFGHIJKLMNOPQRSTUVWXYZ/' \
  -e '/^ *{ "/s/^ *{ "\([^"]*\)".*/\1/p' \
| $AWK '
/.*/ {	printf "#define RC_%s %d\n",$0,i++;
     }
END  {	printf "\n#define RC_LAST %d\n",i-1;
     }
' >> comm.h
chmod a-w comm.h
rm -f comm.cpp
