#ifndef SCREEN_AALIMITS_H
#define SCREEN_AALIMITS_H

#define MAXSTR		768
#define MAXARGS 	64
#define MSGWAIT 	5
#define MSGMINWAIT 	1
#define SILENCEWAIT	30

/*
 * if a nasty user really wants to try a history of 3000 lines on all 10
 * windows, he will allocate 8 MegaBytes of memory, which is quite enough.
 */
#define MAXHISTHEIGHT		3000
#define DEFAULTHISTHEIGHT	100
#define DEFAULT_BUFFERFILE	"/tmp/screen-exchange"

#endif /*SCREEN_AALIMITS_H*/
