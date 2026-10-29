#ifndef SCREEN_TELNET_H
#define SCREEN_TELNET_H

#include <stddef.h>

#ifdef ENABLE_TELNET
struct Window;

int TelOpenAndConnect(struct Window *);
int TelIsline(struct Window *);
void TelProcessLine(char **, size_t *);
int DoTelnet(char *, int *, int);
int TelIn(struct Window *, char *, size_t, int);
void TelBreak(struct Window *);
void TelWindowSize(struct Window *);
void TelStatus(struct Window *, char *, size_t);
#endif

#endif				/* SCREEN_TELNET_H */
