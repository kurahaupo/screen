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

rm -f comm.h
cat << EOF > comm.h
/*
 * This file is automagically created from comm.sh -- DO NOT EDIT
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
#define NEED_FORE		(1<<ARGS_ANY+1)	/* this command needs a fore window */
#define NEED_DISPLAY		(1<<ARGS_ANY+2)	/* this command needs a display */
#define NEED_LAYER		(1<<ARGS_ANY+3)	/* this command needs a layer */
#define CAN_QUERY		(1<<ARGS_ANY+4)	/* this command can be queried using
						   ‘-Q’ to print a result to stdout */

#define ARGS_RANGE(lo,hi)	(ARGS(hi+1)-ARGS(lo))
#define ARGS_ATLEAST(lo)	ARGS_RANGE(lo,ARGS_ANY)
#define ARGS_MASK		ARGS_ATLEAST(0)

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
$AWK < ${srcdir}/comm.c >> comm.h '
/^  [{] ".*/	{   if (old > $2) {
		printf("***ERROR: %s <= %s !!!\n\n", $2, old);
		exit 1;
	    }
	old = $2;
	}
'

$CC -E -I. -I${srcdir} ${srcdir}/comm.c > comm.cpp || exit $?
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
