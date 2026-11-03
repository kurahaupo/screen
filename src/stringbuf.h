#ifndef SCREEN_STRINGBUF_H
#define SCREEN_STRINGBUF_H

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>

bool seputs(char **curr, char *end, char *v);
bool seputsq(char **curr, char *end, char *v);
bool vseprintf(char **curr, char *end, char *fmt, va_list v);

static inline bool seprintf(char **curr, char *end, char *fmt, ...)
{
	if (!strchr(fmt, '%'))
		return seputs(curr, end, fmt);
	va_list v;
        va_start(v, fmt);
        bool r = vseprintf(curr, end, fmt, v);
        va_end(v);
	return r;
}

/******************************************************************************/

typedef struct stringbuf {
	char *sb_curr;
	char *const sb_end;
	char *const sb_base;
} stringbuf;

static inline bool sbputsq(stringbuf *sb, char *v)
{
	return seputsq(&sb->sb_curr, sb->sb_end, v);
}
static inline bool sbputs(stringbuf *sb, char *v)
{
	return seputs(&sb->sb_curr, sb->sb_end, v);
}

static inline stringbuf NewSB2(char *base, size_t len) {
	return (stringbuf){
		.sb_curr = base,
		.sb_end = base + len,
		.sb_base = base,
	};
}
#define NewSB(B)	NewSB2((B), sizeof(B))

static inline bool sbprintf(stringbuf *sb, char *fmt, ...)
{
	if (!strchr(fmt, '%'))
		return seputs(&sb->sb_curr, sb->sb_end, fmt);
	va_list v;
        va_start(v, fmt);
        bool r = vseprintf(&sb->sb_curr, sb->sb_end, fmt, v);
        va_end(v);
	return r;
}

#endif	/* SCREEN_STRINGBUF_H */
