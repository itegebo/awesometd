#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([awesometd], [0.5], [awesometd@trygvevea.com])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11 -Wall -Werror foreign])

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_INSTALL
AC_PROG_LN_S

# pkgconfig checks
PKG_CHECK_MODULES([GL],[gl])
PKG_CHECK_MODULES([SDL],[sdl])

# Checks for libraries.
AC_CHECK_LIB([m], [sqrt])
AC_CHECK_LIB([SDL_image],[IMG_Load])

AC_CHECK_LIB([GL], [glLoadIdentity])
AC_CHECK_LIB([SDL], [SDL_Init])

# Checks for header files.
AC_CHECK_HEADERS([stdint.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_STRTOD
AC_CHECK_FUNCS([memmove memset sqrt strdup strtol])

AC_CONFIG_FILES([Makefile
				 src/Makefile])
AC_OUTPUT
