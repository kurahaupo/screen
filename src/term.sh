#! /bin/sh

if test -z "$AWK"; then
  AWK=awk
fi
if test -z "$srcdir"; then
  srcdir=.
fi

LC_ALL=C
export LC_ALL

source_file=$srcdir/term.c

rm -f term.h
cat << EOF > term.h
/*
 * This file is automagically created from $source_file by $0 -- DO NOT EDIT
 */


#define T_FLG 0
#define T_NUM 1
#define T_STR 2

extern int tgetent(char *, const char *);
extern int tgetflag(char *);
extern int tgetnum(char *);
extern char *tgetstr(char *, char **);
extern char *tgoto(const char *, int, int);
extern int tputs(const char *, int, int (*)(int));
extern char *tparm(char *str, ...);

struct term
{
  char *tcname;
  int type;
};

union tcu
{
  int flg;
  int num;
  char *str;
};

extern struct term term[];

EOF

#
# SCO-Unix sufferers may need to use the following lines:
# perl -p < "$source_file" \
#  -e 's/"/"C/ if /"[A-Z]."/;' \
#  -e 'y/[a-z]/[A-Z]/ if /"/;' \
#
sed < "$source_file" \
  -e '/"[A-Z]."/s/"/"C/' \
  -e '/"/y/abcdefghijklmnopqrstuvwxyz/ABCDEFGHIJKLMNOPQRSTUVWXYZ/' \
| $AWK -v source_file="$source_file" '
/^[[:space:]]+[{] ".*KMAPDEF[(].*$/{
  if (min == 0) min = s
  max = s;
}
/^[[:space:]]+[{] ".*KMAPADEF[(].*$/{
  if (amin == 0) amin = s
  amax = s;
}
/^[[:space:]]+[{] ".*KMAPMDEF[(].*$/{
  if (mmin == 0) mmin = s
  mmax = s;
}
/^[[:space:]]+[{][[:space:]]*".*$/{
a=substr($2,2,length($2)-3);
b=substr($3,3,3);
if (nolist == 0) {
    printf "# define d_%-13s d_tcs[%d].%s\n",a,s,b
    printf "# define D_%-13s DISPLAY(d_%s)\n",a,a
  }
s++;
}
/[[:space:]]*\/[*/]+[[:space:]]+define/{
printf "#define  %-15s %d\t\t/* line %u in %s */\n",$3,s,NR,source_file
}
/[[:space:]]*\/[/*]+[[:space:]]*nolist/{
nolist = 1;
}
/[[:space:]]*\/[/*]+[[:space:]]*list/{
nolist = 0;
}
END {
  printf "\n"
  printf "# define %-15s %d\n", "KMAPDEFSTART", min
  printf "# define %-15s %d\n", "NKMAPDEF", max-min+1
  printf "# define %-15s %d\n", "KMAPADEFSTART", amin
  printf "# define %-15s %d\n", "NKMAPADEF", amax-amin+1
  printf "# define %-15s %d\n", "KMAPMDEFSTART", mmin
  printf "# define %-15s %d\n", "NKMAPMDEF", mmax-mmin+1
}
' | sed -e s/NUM/num/ -e s/STR/str/ -e s/FLG/flg/ \
>> term.h

rm -f kmapdef.c
cat << EOF > kmapdef.c
/*
 * This file is automagically created from $source_file by $0 -- DO NOT EDIT
 */

#include "kmapdef.h"


EOF

$AWK -v"source_file=$source_file" < "$source_file" '
/^[[:space:]]+[{] ".*KMAP.*$/{
  xline[s] = NR
  for (i = 0; i < 3; i++) {
    q = $(5+i)
    if (substr(q, 1, 5) == "KMAPD") {
      if (min == 0) min = s
      max = s
      arr[s] = substr(q, 9, length(q)-9)
    }
    if (substr(q, 1, 5) == "KMAPA") {
      if (amin == 0) amin = s
      amax = s
      anarr[s] = substr(q, 10, length(q)-10)
    }
    if (substr(q, 1, 5) == "KMAPM") {
      if (mmin == 0) mmin = s
      mmax = s
      mnarr[s] = substr(q, 10, length(q)-10)
    }
  }
}
/^[[:space:]]+[{] ".*$/{
  s++;
}
END {
  printf "char *kmapdef[] = {\n"
  for (s = min; s <= max; s++) {
    if (arr[s])
      printf "\t[%u] = %s,\t\t/* line %u in %s */\n", s-min, arr[s], xline[s], source_file;
  }
  printf "};\n\n"
  printf "char *kmapadef[] = {\n"
  for (s = amin; s <= amax; s++) {
    if (anarr[s])
      printf "\t[%u] = %s,\t\t/* line %u in %s */\n", s-amin, anarr[s], xline[s], source_file;
  }
  printf "};\n\n"
  printf "char *kmapmdef[] = {\n"
  for (s = mmin; s <= mmax; s++) {
    if (mnarr[s])
      printf "\t[%u] = %s,\t\t/* line %u in %s */\n", s-mmin, mnarr[s], xline[s], source_file;
  }
  printf "};\n"
}
' >> kmapdef.c

chmod a-w kmapdef.c
chmod a-w term.h

