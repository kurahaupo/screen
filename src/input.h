#ifndef SCREEN_INPUT_H
#define SCREEN_INPUT_H

#include <stdlib.h>

void  inp_setprompt (char *, char *);
typedef  void InputCallback(char *, size_t, void *);
void  Input (char *, size_t, int, InputCallback, void *, int);
int   InInput (void);

#endif /* SCREEN_INPUT_H */
