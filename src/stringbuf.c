#include "config.h"

#include <stdio.h>

#include "stringbuf.h"

# define Ellipsis "\u2026"	/* \xe2\x80\xa6 … */
//# define Ellipsis "..."
//# undef Ellipsis

bool seputs(char **curr, char *end, char *str)
{
	if (*curr == NULL)
		return false;
	size_t n = end - *curr;
	size_t l = strlen(str);
	if (l < n) {
		memcpy(*curr, str, l+1);
		*curr += l;
		return true;
	}
	memcpy(*curr, str, n-1);
	#ifdef Ellipsis
	strcpy(end-sizeof Ellipsis, Ellipsis);
	#endif /*Ellipsis*/
	*curr = NULL;
	return false;
}

bool vseprintf(char **curr, char *end, char *fmt, va_list v)
{
        if (*curr == NULL)
                return false;
	if (!strchr(fmt, '%'))
		return seputs(curr, end, fmt);
        int l = end - *curr;
        int n = vsnprintf(*curr, l, fmt, v);
        if (n >= 0 && n < l) {
                *curr += n;
		return true;
        }
	#ifdef Ellipsis
	strcpy(end-sizeof Ellipsis, Ellipsis);
	#endif /*Ellipsis*/
        *curr = NULL;
	return false;
}

bool seputsq(char **curr, char *end, char *str)
{
	if (*curr == NULL)
		return false;
	for (; *str && *curr < end-4; ++str) {
		char c = *str;
		static char mapfrom[] = "\a\b\033\f\n\r\t\v\\";
		static char mapto[]   = "abefnrtv\\0";
		char *x = memchr(mapfrom, c, sizeof mapfrom);
		if (x)
			*(*curr)++ = '\\',
			*(*curr)++ = mapto[x-mapfrom];
		else if (isprint(c))
			*(*curr)++ = c;
		else
			seprintf(curr, end, "\\x%02hhx", c);
	}
	for (; *str && *curr < end-1 && isprint(*str) && *str != '\\'; ++str)
		*(*curr)++ = *str;
	**curr = 0;
	if (!*str)
		return true;
	#ifdef Ellipsis
	strcpy(end-sizeof Ellipsis, Ellipsis);
	#endif /*Ellipsis*/
	*curr = NULL;
	return false;
}

