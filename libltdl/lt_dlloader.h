/* lt_dlloader.h -- dynamic library loader interface
   Copyright (C) 2004 Free Software Foundation, Inc.
   Originally by Gary V. Vaughan  <gary@gnu.org>

   NOTE: The canonical source of this file is maintained with the
   GNU Libtool package.  Report bugs to bug-libtool@gnu.org.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

As a special exception to the GNU Lesser General Public License,
if you distribute this file as part of a program or library that
is built using GNU libtool, you may include it under the same
distribution terms that you use for the rest of that program.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
02111-1307  USA

*/

#if !defined(LT_DLLOADER_H)
#define LT_DLLOADER_H 1

#include <libltdl/lt_system.h>

LT_BEGIN_C_DECLS

typedef	void *	lt_dlloader;
typedef void *	lt_module;
typedef void *	lt_user_data;

/* Function pointer types for module loader vtable entries:  */
typedef lt_module   lt_module_open	(lt_user_data data,
					 const char *filename);
typedef int	    lt_module_close	(lt_user_data data,
					 lt_module module);
typedef void *	    lt_find_sym		(lt_user_data data, lt_module module,
					 const char *symbolname);
typedef int	    lt_dlloader_init	(lt_user_data data);
typedef int	    lt_dlloader_exit	(lt_user_data data);

/* Default priority is LT_DLLOADER_PREPEND if none is explicitly given.  */
typedef enum {
  LT_DLLOADER_PREPEND = 0, LT_DLLOADER_APPEND
} lt_dlloader_priority;

/* This structure defines a module loader, as populated by the get_vtable
   entry point of each loader.  */
typedef struct {
  const char *		name;
  const char *		sym_prefix;
  lt_module_open *	module_open;
  lt_module_close *	module_close;
  lt_find_sym *		find_sym;
  lt_dlloader_init *	dlloader_init;
  lt_dlloader_exit *	dlloader_exit;
  lt_user_data		dlloader_data;
  lt_dlloader_priority	priority;
} lt_dlvtable;

LT_SCOPE int		lt_dlloader_add	   (const lt_dlvtable *vtable);
LT_SCOPE lt_dlloader	lt_dlloader_next   (const lt_dlloader loader);

LT_SCOPE const lt_dlvtable *lt_dlloader_remove	(const char *name);
LT_SCOPE const lt_dlvtable *lt_dlloader_find	(const char *name);
LT_SCOPE const lt_dlvtable *lt_dlloader_get	(lt_dlloader loader);


/* Type of a function to get a loader's vtable:  */
typedef  const lt_dlvtable *lt_get_vtable	(lt_user_data data);

LT_END_C_DECLS

#endif /*!defined(LT_DLLOADER_H)*/