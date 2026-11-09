#ifndef SCREEN_TERMCAP_H
#define SCREEN_TERMCAP_H

#include <stdbool.h>

int InitTermcap(int, int);
char *MakeTermcap(bool);
char *gettermcapstring(char *);
int remap(int, int);
void CheckEscape(void);
int CreateTransTable(char *);
void FreeTransTable(void);

/* global variables */

extern char screenterm[];
extern char Term[];
extern char *extra_incap;
extern char *extra_outcap;
extern double ecma48_match_threshold;

#ifndef ANSI_PROBE_FAILURE_LIMIT
#define ANSI_PROBE_FAILURE_LIMIT 2	/* max 2 missing; 5 out of 7 standard attributes must match */
#endif

#endif				/* SCREEN_TERMCAP_H */
