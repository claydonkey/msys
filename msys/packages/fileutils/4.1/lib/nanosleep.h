/*  Copyright (C) 2000 Free Software Foundation, Inc.

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
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#if ! defined NANOSLEEP_H
# define NANOSLEEP_H

/* You must include config.h before including this file.  */

# include <sys/types.h>
# if TIME_WITH_SYS_TIME
#  include <sys/time.h>
#  include <time.h>
# else
#  if HAVE_SYS_TIME_H
#   include <sys/time.h>
#  else
#   include <time.h>
#  endif
# endif

# if ! HAVE_STRUCT_TIMESPEC
/* Some systems don't define this struct, e.g., AIX 4.1, Ultrix 4.3.  */
struct timespec
{
  time_t tv_sec;
  long tv_nsec;
};
# endif

# if ! HAVE_DECL_NANOSLEEP
/* Don't specify a prototype here.  Some systems (e.g., OSF) declare
   nanosleep with a conflicting one (const-less first parameter).  */
int nanosleep ();
# endif

#endif
