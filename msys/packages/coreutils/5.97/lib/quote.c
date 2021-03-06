/* quote.c - quote arguments for output
   Copyright (C) 1998, 1999, 2000, 2001, 2003, 2006 Free Software
   Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.  */

/* Written by Paul Eggert <eggert@twinsun.com> */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "stdbool.h"
#include "quotearg.h"
#include "quote.h"

/* Return an unambiguous printable representation of NAME,
   allocated in slot N, suitable for diagnostics.  */
char const *
quote_n (int n, char const *name)
{
#if __CYGWIN__ || __MSYS__
  extern bool quote_eight_bit;
  bool save = quote_eight_bit;
  char const *result;
  quote_eight_bit = true;
  result = quotearg_n_style (n, locale_quoting_style, name);
  quote_eight_bit = save;
  return result;
#else /* ! __CYGWIN__ */
  return quotearg_n_style (n, locale_quoting_style, name);
#endif /* ! __CYGWIN__ */
}

/* Return an unambiguous printable representation of NAME,
   suitable for diagnostics.  */
char const *
quote (char const *name)
{
  return quote_n (0, name);
}
