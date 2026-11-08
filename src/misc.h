#ifndef SCREEN_MISC_H
#define SCREEN_MISC_H

#include <stddef.h>	// for size_t

struct mchar;
typedef void signal_handler_t(int);

#include "image.h"	// TODO CHECKME

char *SaveStr(const char *);
char *SaveStrn(const char *, size_t);
#ifndef HAVE_STRERROR
char *strerror(int);
#endif
void centerline(char *, int);
void leftline(char *, int, struct mchar *);
char *Filename(char *);
char *stripdev(char *);
void closeallfiles(int);
int UserContext(void);
void UserReturn(int);
int UserStatus(void);
signal_handler_t *xsignal(int, signal_handler_t *);
#if defined(HAVE_SETEUID) || defined(HAVE_SETREUID)
void xseteuid(int);
void xsetegid(int);
#endif
int AddXChar(char *, int);
int AddXChars(char *, int, char *);

# define UNSAFE_ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#if __STDC_VERSION__ >= 202001

# define UNUSED		[[maybe_unused]]
# define UNUSED_ARG
# define ARRAY_SIZE(x)	_Generic(&(x), \
				typeof(*(x)) (*)[]: UNSAFE_ARRAY_SIZE(x), \
				default: sizeof(char[-1]) /* error: expression is not an array */ \
			)
# define FALLTHROUGH	[[fallthrough]]

#else

# if defined __GNUC__ || defined __clang__

#  define UNUSED	__attribute__((__unused__))
#  define IS_ARRAY(x)	!__builtin_types_compatible_p(__typeof__(x), __typeof__(*(x))*)
#  define FALLTHROUGH	__attribute__((fallthrough))

# else

#  define IS_ARRAY(x)	((void const*)(x) == (void const*)*(x))

# endif

# ifndef TOKEN_CONCAT
#  define TOKEN_CONCAT(X,Y)	X ## Y
# endif
# define UNUSED_ARG	TOKEN_CONCAT(UNUSED_,__LINE__) UNUSED
# define MUST_BE_ARRAY(x) sizeof(char [IS_ARRAY(x)*2-1])
# define ARRAY_SIZE(x)	(MUST_BE_ARRAY(x) * UNSAFE_ARRAY_SIZE(x))

#endif

#ifndef MARK_UNUSED
# ifdef UNUSED
#  define MARK_UNUSED(x)
# else
#  define MARK_UNUSED(x) (void)(x);
# endif
#endif /*MARK_UNUSED*/

#ifndef UNUSED
# define UNUSED /*UNUSED*/
#endif /*UNUSED*/

#ifndef FALLTHROUGH
# define FALLTHROUGH	((void)0) /*FALLTHROUGH*/
#endif /*FALLTHROUGH*/

#ifndef ARRAY_END
# define ARRAY_END(x)	((x) + ARRAY_SIZE(x))
#endif /*ARRAY_END*/


#endif				/* SCREEN_MISC_H */
