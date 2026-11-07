#ifndef SCREEN_RESIZE_H
#define SCREEN_RESIZE_H

#include <stddef.h>	// for size_t

struct Display;
struct Layer;
struct Window;

int ChangeWindowSize(struct Window *, int, int, int);
void ChangeScreenSize(int, int, int);
void CheckScreenSize(int);
void *xrealloc(void *, size_t);
void ResizeLayersToCanvases(void);
void ResizeLayer(struct Layer *, int, int, struct Display *);
int MayResizeLayer(struct Layer *);
void FreeAltScreen(struct Window *);
void EnterAltScreen(struct Window *);
void LeaveAltScreen(struct Window *);

/* global variables */

extern struct winsize glwz;

#endif				/* SCREEN_RESIZE_H */
