#ifndef SCREEN_UTMP_H
#define SCREEN_UTMP_H

#include <stdbool.h>

struct Window;

#ifdef ENABLE_UTMP
void InitUtmp(void);
void RemoveLoginSlot(void);
void RestoreLoginSlot(void);
int SetUtmp(struct Window *);
int RemoveUtmp(struct Window *);
#endif				/* ENABLE_UTMP */
void SlotToggle(bool);
#ifdef CAREFULUTMP
void CarefulUtmp(void);
#else
# define CarefulUtmp()		/* nothing */
#endif				/* CAREFULUTMP */

#endif				/* SCREEN_UTMP_H */
