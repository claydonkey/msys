#ifndef COMPAT_H
/*
 * File: compat.h
 * Centralised platform dependency handling for man's C compilation units.
 *
 * Copyright (C) 2005, Keith D. Marshall <keithmarshall@users.sourceforge.net>
 *
 * This file is part of the man package.
 *
 * man is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2, or (at your option) any later version.
 *
 * man is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along
 * with man; see the file COPYING.  If not, write to the Free Software
 * Foundation, 51 Franklin St - Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */
#define COMPAT_H

/* Always include config.h, if we have it. */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

/* If we don't have nl_types.h,
 * then we won't be able to incorporate national language support.
 */

#ifndef HAVE_NL_TYPES_H
# define NONLS 1
#endif

/* Always prefer strchr() over index(), and strrchr() over rindex(),
 * if we have them.
 */

#ifdef HAVE_STRCHR
# define index  strchr
#endif
#ifdef HAVE_STRRCHR
# define rindex strrchr
#endif

#ifdef __MINGW32__
/*
 * This could probably be better handled by autoconf,
 * but, as a quick and dirty hack for now...
 *
 * On MinGW based platforms, glob.c will not currently compile,
 * unless we define...
 */

# define _POSIX_SOURCE
# define __GNU_LIBRARY__
#endif

#ifdef _WIN32
/*
 * Handle various nuisances/peculiarities of Microsoft's
 * 32-bit Windows platform.
 *
 * Win32 Path Name Handling
 * ------------------------
 *
 * Silently correct the misdemeanours of Win32, and its
 * "dyed in the wool" users who refuse to believe that it is ok
 * to use "/" instead of "\" in path names; however, we must
 * still use ";" as the path separator.
 */

extern const char *win32posix(const char *);
#define PATH_SEPARATOR_CHAR ';'

/*
 * Because we are forcing the use of "/" as a directory separator,
 * we don't need to check for leading "\" as an absolute path indicator,
 * but we *do* still need to allow for a drive designator.
 */

#define isabspath(p) ((*(p) == '/') || (((p)[1] == ':') && ((p)[2] == '/')))

/*
 * Win32 User Identification
 * -------------------------
 *
 * Win32 user model is not consistent with POSIX,
 * so, when we care, just pretend we are running as root...
 */

#define getuid()   0
#define geteuid()  0
#define getgid()   0
#define getegid()  0

#else /* !_WIN32 */
/*
 * POSIX Style Path Name Handling
 * ------------------------------
 *
 * On an already POSIXy system,
 * we don't need any Win32 normalisation of the DIR separator,
 * and we keep to the standard ":" as the path separator.
 */

#define win32posix(p) p
#define PATH_SEPARATOR_CHAR ';'

/*
 * POSIX mandates that absolute path names begin with a "/".
 */

#define isabspath(p)  (*(p) == '/')
#endif

#endif /* COMPAT_H */