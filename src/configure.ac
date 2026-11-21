AC_INIT([GNU Screen],[5.1.0.4],[https://savannah.gnu.org/bugs/?group=screen],[screen],[https://www.gnu.org/software/screen/])
AC_PREREQ([2.71])

AC_CONFIG_HEADERS([config.h])

AC_DEFINE_UNQUOTED([VERSION_MAJOR],
	[`echo $PACKAGE_VERSION | cut -d . -f 1`],
	[Major version of GNU screen])
AC_DEFINE_UNQUOTED([VERSION_MINOR],
	[`echo $PACKAGE_VERSION | cut -d . -f 2 | cut -d - -f 1`],
	[Minor version of GNU screen])
AC_DEFINE_UNQUOTED([VERSION_REVISION],
	[`echo $PACKAGE_VERSION | cut -d . -f 3 | cut -d - -f 1`],
	[Micro revision of GNU screen])

AH_TEMPLATE([HAVE_EXECVPE], [system has execvpe() defined])
AH_TEMPLATE([HAVE_OPENPTY], [system has openpty() defined])

dnl -
AH_TEMPLATE([ENABLE_UTMP], [Enable utmp support])
AH_TEMPLATE([HAVE_UTEMPTER], [system has utempter helper binary])
AH_TEMPLATE([HAVE_UT_EXIT], [utmpx struct has ut_exit field])
AH_TEMPLATE([HAVE_UT_HOST], [utmpx struct has ut_host field])

dnl -
AH_TEMPLATE([ENABLE_PAM], [Enable Pluggable Authentication Modules support])

dnl -
AH_TEMPLATE([ENABLE_TELNET], [Enable built-in telnet client])

dnl -
AH_TEMPLATE([SOCKET_DIR], [Path to socket directory])

dnl -
AH_TEMPLATE([SYSTEM_SCREENRC], [Path to system screenrc])

dnl - pty settings
AH_TEMPLATE([PTY_MODE], [Default mode for pty devices])
AH_TEMPLATE([PTY_GROUP], [Default group for pty devices])
AH_TEMPLATE([PTY_ROFS], [pty devices are on read only filesystem])

dnl
dnl Check for sane compiler
dnl

AC_USE_SYSTEM_EXTENSIONS
AC_PROG_CC
AC_PROG_AWK
AC_PROG_INSTALL
AC_USE_SYSTEM_EXTENSIONS

dnl
dnl Check for __VA_ARGS__ (standard since C99)
dnl   and for __VA_OPT__ (standard since C23 / C++20)
dnl
AC_MSG_CHECKING([whether the compiler supports __VA_ARGS__ and __VA_OPT__])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([], [
  #define TEST_MACRO(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
  TEST_MACRO("test %d\n", 1);
])],
[
  AC_DEFINE([HAVE_VA_ARGS], [1], [Define to 1 if the compiler supports __VA_ARGS__.])
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([], [
    #define TEST_OPT(fmt, ...) fprintf(stderr, fmt __VA_OPT__(,) __VA_ARGS__)
    TEST_OPT("test\n");
    TEST_OPT("test %d\n", 42);
  ])],
  [
    AC_DEFINE([HAVE_VA_OPT], [1], [Define to 1 if the compiler supports __VA_OPT__.])
    AC_MSG_RESULT([has __VA_ARGS__ and __VA_OPT__])
  ],
  [
    AC_MSG_RESULT([has __VA_ARGS__ but not __VA_OPT__])
  ])
],
[
  AC_MSG_RESULT([lacks __VA_ARGS__ (__VA_OPT__ ignored)])
])

dnl
dnl Check for weirdly named extended integer types
dnl
AC_MSG_CHECKING([whether the compiler supports uint128, _uint128, or __uint128])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [
  uint128_t x = (uint128_t)1 << 128 - 1;
  (void)x;
])], [
  AC_MSG_RESULT([ignored (has uint128_t)])
], [
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [
    _uint128 x = (uint128)1 << 128 - 1;
    (void)x;
  ])], [
    AC_DEFINE([HAVE___UINT128], [1], [Define to 1 if the compiler supports __uint128.])
    AC_MSG_RESULT([has __uint128])
  ], [
    AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [
      __uint128 x = (uint128)1 << 128 - 1;
      (void)x;
    ])], [
      AC_DEFINE([HAVE__UINT128], [1], [Define to 1 if the compiler supports _uint128.])
      AC_MSG_RESULT([has _uint128])
    ], [
      AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [
	uint128 x = (uint128)1 << 128 - 1;
	(void)x;
      ])], [
	AC_DEFINE([HAVE_UINT128], [1], [Define to 1 if the compiler supports uint128.])
	AC_MSG_RESULT([has uint128])
      ], [
        AC_MSG_RESULT([no])
      ])
    ])
  ])
])

AC_MSG_CHECKING([whether the compiler supports uint256, _uint256, or __uint256])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [
  uint256_t x = (uint256_t)1 << 256 - 1;
  (void)x;
])], [
  AC_MSG_RESULT([ignored (has uint256_t)])
], [
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [ 
    _uint256 x = (uint256)1 << 256 - 1;
    (void)x;
  ])], [
    AC_DEFINE([HAVE___UINT256], [1], [Define to 1 if the compiler supports __uint256.])
    AC_MSG_RESULT([has __uint256])
  ], [
    AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [ 
      __uint256 x = (uint256)1 << 256 - 1;
      (void)x;
    ])], [
      AC_DEFINE([HAVE__UINT256], [1], [Define to 1 if the compiler supports _uint256.])
      AC_MSG_RESULT([has _uint256])
    ], [
      AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [
	uint256 x = (uint256)1 << 256 - 1;
	(void)x;
      ])], [
	AC_DEFINE([HAVE_UINT256], [1], [Define to 1 if the compiler supports uint256.])
	AC_MSG_RESULT([has uint256])
      ], [
        AC_MSG_RESULT([no])
      ])
    ])
  ])
])

AC_MSG_CHECKING([whether the compiler supports uint512, _uint512, or __uint512])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [
  uint512_t x = (uint512_t)1 << 512 - 1;
  (void)x;
])], [
  AC_MSG_RESULT([ignored (has uint512_t)])
], [
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [ 
    _uint512 x = (uint512)1 << 512 - 1;
    (void)x;
  ])], [
    AC_DEFINE([HAVE___UINT512], [1], [Define to 1 if the compiler supports __uint512.])
    AC_MSG_RESULT([has __uint512])
  ], [
    AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [ 
      __uint512 x = (uint512)1 << 512 - 1;
      (void)x;
    ])], [
      AC_DEFINE([HAVE__UINT512], [1], [Define to 1 if the compiler supports _uint512.])
      AC_MSG_RESULT([has _uint512])
    ], [
      AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [
	uint512 x = (uint512)1 << 512 - 1;
	(void)x;
      ])], [
	AC_DEFINE([HAVE_UINT512], [1], [Define to 1 if the compiler supports uint512.])
	AC_MSG_RESULT([has uint512])
      ], [
        AC_MSG_RESULT([no])
      ])
    ])
  ])
])

AC_MSG_CHECKING([whether the compiler supports uint1024, _uint1024, or __uint1024])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [
  uint1024_t x = (uint1024_t)1 << 1024 - 1;
  (void)x;
])], [
  AC_MSG_RESULT([ignored (has uint1024_t)])
], [
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [ 
    _uint1024 x = (uint1024)1 << 1024 - 1;
    (void)x;
  ])], [
    AC_DEFINE([HAVE___UINT1024], [1], [Define to 1 if the compiler supports __uint1024.])
    AC_MSG_RESULT([has __uint1024])
  ], [
    AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [ 
      __uint1024 x = (uint1024)1 << 1024 - 1;
      (void)x;
    ])], [
      AC_DEFINE([HAVE__UINT1024], [1], [Define to 1 if the compiler supports _uint1024.])
      AC_MSG_RESULT([has _uint1024])
    ], [
      AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [
	uint1024 x = (uint1024)1 << 1024 - 1;
	(void)x;
      ])], [
	AC_DEFINE([HAVE_UINT1024], [1], [Define to 1 if the compiler supports uint1024.])
	AC_MSG_RESULT([has uint1024])
      ], [
        AC_MSG_RESULT([no])
      ])
    ])
  ])
])

AC_MSG_CHECKING([whether the compiler supports uint2048, _uint2048, or __uint2048])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [
  uint2048_t x = (uint2048_t)1 << 2048 - 1;
  (void)x;
])], [
  AC_MSG_RESULT([ignored (has uint2048_t)])
], [
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [ 
    _uint2048 x = (uint2048)1 << 2048 - 1;
    (void)x;
  ])], [
    AC_DEFINE([HAVE___UINT2048], [1], [Define to 1 if the compiler supports __uint2048.])
    AC_MSG_RESULT([has __uint2048])
  ], [
    AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [ 
      __uint2048 x = (uint2048)1 << 2048 - 1;
      (void)x;
    ])], [
      AC_DEFINE([HAVE__UINT2048], [1], [Define to 1 if the compiler supports _uint2048.])
      AC_MSG_RESULT([has _uint2048])
    ], [
      AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [
	uint2048 x = (uint2048)1 << 2048 - 1;
	(void)x;
      ])], [
	AC_DEFINE([HAVE_UINT2048], [1], [Define to 1 if the compiler supports uint2048.])
	AC_MSG_RESULT([has uint2048])
      ], [
        AC_MSG_RESULT([no])
      ])
    ])
  ])
])

AC_MSG_CHECKING([whether the compiler supports uint4096, _uint4096, or __uint4096])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [
  uint4096_t x = (uint4096_t)1 << 4096 - 1;
  (void)x;
])], [
  AC_MSG_RESULT([ignored (has uint4096_t)])
], [
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [ 
    _uint4096 x = (uint4096)1 << 4096 - 1;
    (void)x;
  ])], [
    AC_DEFINE([HAVE___UINT4096], [1], [Define to 1 if the compiler supports __uint4096.])
    AC_MSG_RESULT([has __uint4096])
  ], [
    AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [ 
      __uint4096 x = (uint4096)1 << 4096 - 1;
      (void)x;
    ])], [
      AC_DEFINE([HAVE__UINT4096], [1], [Define to 1 if the compiler supports _uint4096.])
      AC_MSG_RESULT([has _uint4096])
    ], [
      AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [
	uint4096 x = (uint4096)1 << 4096 - 1;
	(void)x;
      ])], [
	AC_DEFINE([HAVE_UINT4096], [1], [Define to 1 if the compiler supports uint4096.])
	AC_MSG_RESULT([has uint4096])
      ], [
        AC_MSG_RESULT([no])
      ])
    ])
  ])
])

AC_MSG_CHECKING([whether the compiler supports uint8192, _uint8192, or __uint8192])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [
  uint8192_t x = (uint8192_t)1 << 8192 - 1;
  (void)x;
])], [
  AC_MSG_RESULT([ignored (has uint8192_t)])
], [
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [
    _uint8192 x = (uint8192)1 << 8192 - 1;
    (void)x;
  ])], [
    AC_DEFINE([HAVE___UINT8192], [1], [Define to 1 if the compiler supports __uint8192.])
    AC_MSG_RESULT([has __uint8192])
  ], [
    AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [
      __uint8192 x = (uint8192)1 << 8192 - 1;
      (void)x;
    ])], [
      AC_DEFINE([HAVE__UINT8192], [1], [Define to 1 if the compiler supports _uint8192.])
      AC_MSG_RESULT([has _uint8192])
    ], [
      AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <stdint.h>], [
	uint8192 x = (uint8192)1 << 8192 - 1;
	(void)x;
      ])], [
	AC_DEFINE([HAVE_UINT8192], [1], [Define to 1 if the compiler supports uint8192.])
	AC_MSG_RESULT([has uint8192])
      ], [
        AC_MSG_RESULT([no])
      ])
    ])
  ])
])

dnl
dnl Check various system stuff
dnl

dnl check for execvpe()
AC_CHECK_FUNCS([execvpe])

dnl
AC_CHECK_FUNCS([seteuid setegid setreuid setresuid])

dnl bit-counting; ffs SHOULD be strings.h, but some old systems it's in string.h
AC_CHECK_HEADERS([string.h strings.h stdbit.h])
AC_CHECK_FUNCS([ffs ffsll])

AC_CHECK_DECLS([stdc_count_trailing_zeros, stdc_count_ones, stdc_count_zeros], [], [], [[
#ifdef HAVE_STDBIT_H
# include <stdbit.h>
#endif
]])

AC_MSG_CHECKING([for __builtin_ctz])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([], [
  unsigned int val = 42;
  if (val == 0) return 0;
  int res = __builtin_ctz(val);
  (void)res;
])], [
  AC_MSG_RESULT([yes])
  AC_DEFINE([HAVE_BUILTIN_CTZ], [1], [Define to 1 if __builtin_ctz is available])
], [
  AC_MSG_RESULT([no])
])

AC_MSG_CHECKING([for __builtin_popcount])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([], [
  unsigned int val = 42;
  int res = __builtin_popcount(val);
  (void)res;
])], [
  AC_MSG_RESULT([yes])
  AC_DEFINE([HAVE_BUILTIN_POPCOUNT], [1], [Define to 1 if __builtin_popcount is available])
], [
  AC_MSG_RESULT([no])
])

dnl curses compatible lib, we do forward declaration ourselves, only need to link to proper library
AC_SEARCH_LIBS([tgetent], [curses termcap termlib ncursesw tinfow ncurses tinfo], [], [
	AC_MSG_ERROR([unable to find tgetent() function])
])

dnl check for crypt()
AC_SEARCH_LIBS([crypt], [crypt], [], [
	AC_MSG_ERROR([unable to find crypt() function])
])

dnl
AC_CHECK_HEADERS(pty.h util.h libutil.h)
AC_SEARCH_LIBS([openpty], [util openpty bsd], [
	AC_DEFINE(HAVE_OPENPTY)
], [
	AC_MSG_ERROR([unable to find openpty() function])
])

dnl
AC_SEARCH_LIBS([socket], [network], [], [
	AC_MSG_ERROR([unable to find socket() function])
])

dnl
AC_CHECK_HEADERS(langinfo.h)

dnl
AC_CHECK_HEADERS(dirent.h)

dnl
dnl Check user changeable stuff
dnl

AC_ARG_ENABLE(pam, AS_HELP_STRING([--enable-pam],
	      [enable PAM support (default: enabled)]),
	      [enable_pam=$enableval],
	      [enable_pam=yes])
AC_ARG_ENABLE(utmp, AS_HELP_STRING([--enable-utmp],
	      [enable utmp support (default: disabled)]),
	      [enable_utmp=$enableval],
	      [enable_utmp=no])
AC_ARG_ENABLE(telnet, AS_HELP_STRING([--enable-telnet],
	      [enable telnet support (default: disabled)]),
	      [enable_telnet=$enableval],
	      [enable_telnet=no])
AC_ARG_ENABLE(socket-dir, AS_HELP_STRING([--enable-socket-dir],
	      [enable global socket directory (default: disabled)]),
	      [enable_socket_dir=$enableval],
	      [enable_socket_dir=no])

AC_ARG_WITH(system_screenrc, AS_HELP_STRING([--with-system_screenrc],
	    [set location of system screenrc (default: /etc/screenrc)]),
	    [with_system_screenrc=$withval],
	    [with_system_screenrc=/etc/screenrc])
AC_ARG_WITH(pty-mode, AS_HELP_STRING([--with-pty-mode],
	    [set pty mode (default: 0620)]),
	    [with_pty_mode=$withval],
	    [with_pty_mode=0620])
AC_ARG_WITH(pty-group, AS_HELP_STRING([--with-pty-group],
	    [set pty group (default: 5)]),
	    [with_pty_group=$withval],
	    [with_pty_group=5])
AC_ARG_WITH(pty-rofs, AS_HELP_STRING([--with-pty-rofs],
	    [set rofs handling (default: no)]),
	    [with_pty_rofs=$withval],
	    [with_pty_rofs=no])

dnl -- enable_pam

AS_IF([test "x$enable_pam" = "xyes"], [
	AC_MSG_CHECKING(for PAM support)
	oldlibs="$LIBS"
	LIBS="$LIBS -lpam"
	AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include <security/pam_appl.h>]], [[
		pam_start(0, 0, 0, 0);
		pam_authenticate(0, 0);
		pam_end(0,0);
	]])],[AC_MSG_RESULT(yes);
	AC_DEFINE(ENABLE_PAM)],[AC_MSG_ERROR(no);LIBS="$oldlibs"])
])

dnl -- enable_utmp

AS_IF([test "x$enable_utmp" = "xyes"], [
	AC_CHECK_HEADERS(utmpx.h, have_utmpx=yes, have_utmpx=no)
	AS_IF([test "x$have_utmpx" != "xyes"],
	      AC_MSG_ERROR(Missing utmpx.h))

	AC_CHECK_HEADER(utempter.h, have_utempter=yes, have_utempter=no)
	AS_IF([test "x$have_utempter" = "xyes"], [
		AC_DEFINE(HAVE_UTEMPTER)
		LIBS="$LIBS -lutempter"
	])

	AC_MSG_CHECKING(if utmpx struct has ut_host field)
	AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <utmpx.h>]], [[
		struct utmpx u;
		u.ut_host[0] = 0;
	]])],[AC_MSG_RESULT(yes)
	AC_DEFINE(HAVE_UT_HOST)],[AC_MSG_RESULT(no)])

	AC_MSG_CHECKING(if utmpx struct has ut_exit field)
	AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <utmpx.h>]], [[
		struct utmpx u;
		u.ut_exit.e_exit;
	]])],[AC_MSG_RESULT(yes)
	AC_DEFINE(HAVE_UT_EXIT)],[AC_MSG_RESULT(no)])

	AC_DEFINE(ENABLE_UTMP)
])

dnl -- enable_telnet

AS_IF([test "x$enable_telnet" = "xyes"], [
	AC_DEFINE(ENABLE_TELNET)
])

dnl -- enable_socket_dir

AS_IF([test "x$enable_socket_dir" != "xno"], [
	AS_IF([test "x$enable_socket_dir" = "xyes"],
	      [enable_socket_dir="/run/screen"]
	)
	AC_DEFINE_UNQUOTED(SOCKET_DIR, "$enable_socket_dir")
])

dnl -- with_sysscreenrc
AC_DEFINE_UNQUOTED(SYSTEM_SCREENRC, "$with_system_screenrc")

dnl -- with_pty_mode
AC_DEFINE_UNQUOTED(PTY_MODE, $with_pty_mode)

dnl -- with_pty_group
AC_DEFINE_UNQUOTED(PTY_GROUP, $with_pty_group)

dnl -- with_pty_rofs
AS_IF([test "x$with_pty_rofs" = "xyes"], [
	AC_DEFINE(PTY_ROFS)
])

dnl
dnl Generate files from *.in ones
dnl

AC_CONFIG_FILES([Makefile doc/Makefile])
AC_OUTPUT

dnl
dnl Print out config
dnl

echo ""
echo "Configuration:"
echo ""
echo " PAM support: .............................. $enable_pam"
echo " telnet support: ........................... $enable_telnet"
echo " utmp support: ............................. $enable_utmp"
echo " global socket directory: .................. $enable_socket_dir"
echo ""
echo " system screenrc location: ................. $with_system_screenrc"
echo " pty mode: ................................. $with_pty_mode"
echo " pty group: ................................ $with_pty_group"
echo " pty on read only file system: ............. $with_pty_rofs"
echo ""

AS_IF([test "x$enable_pam" != "xyes"], [
	echo "!!! WARNING !!!"
	echo "YOU ARE DISABLING PAM SUPPORT!"
	echo "FOR screen TO WORK IT WILL NEED TO RUN AS SUID root BINARY"
	echo "THIS CONFIGURATION IS _HIGHLY_ NOT RECOMMENDED!"
	echo "!!! WARNING !!!"
])
