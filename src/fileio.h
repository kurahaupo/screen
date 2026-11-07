#ifndef SCREEN_FILEIO_H
#define SCREEN_FILEIO_H

#include <stdint.h>	//
#include <stdio.h>	// for FILE

struct acluser;
struct Window;

int StartRc(char *, int);
void FinishRc(char *);
void RcLine(char *, int);
FILE *secfopen(char *, char *);
int secopen(char *, int, int);
void WriteFile(struct acluser *, char *, int);
char *ReadFile(char *, int *);
void KillBuffers(void);
int printpipe(struct Window *, char *);
int readpipe(char **);
void do_source(char *);

/* global variables */

extern char *rc_name;

#endif
