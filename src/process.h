#ifndef SCREEN_PROCESS_H
#define SCREEN_PROCESS_H

#include <stdbool.h>	//
#include <stdint.h>	//

#include "comm.h"	// for struct action

struct acluser;
struct mchar;
struct paster;
struct Window;
struct WinMsgBufContext;

void InitKeytab(void);
void ProcessInput(char *, size_t);
void ProcessInput2(char *, size_t);
void DoProcess(struct Window *, char **, size_t *, struct paster *);
void DoAction(struct action *);
int FindCommnr(const char *);
void DoCommand(char **, int *);
void Activate(int);
void KillWindow(struct Window *);
void SetForeWindow(struct Window *);
int Parse(char *, int, char **, int *);
void SetEscape(struct acluser *, int, int);
void DoScreen(char *, char **);
int IsNumColon(char *, char *, int);
void ShowWindows(struct action *, int);
char *AddWindows(struct WinMsgBufContext *, int, int, int);
char *AddWindowFlags(char *, int, struct Window *);
char *AddOtherUsers(char *, int, struct Window *);
int WindowByNoN(char *);
struct Window *FindNiceWindow(struct Window *, char *);
int CompileKeys(char *, int, unsigned char *);
void RefreshXtermOSC(void);
uint64_t ParseAttrColor(char *, int);
void ApplyAttrColor(uint64_t, struct mchar *);
void SwitchWindow(struct Window *);
int StuffKey(int);

/* global variables */

extern bool hardcopy_append;

extern char *noargs[];
extern char *zmodem_recvcmd;
extern char *zmodem_sendcmd;

extern int idletimo;
extern int kmap_extn;
extern int zmodem_mode;
extern int TtyMode;

extern struct action idleaction;
extern struct action dmtab[];
extern struct action ktab[];
extern struct action mmtab[];
extern struct action umtab[];

extern struct kmap_ext *kmap_exts;

extern int maptimeout;

#endif				/* SCREEN_PROCESS_H */
