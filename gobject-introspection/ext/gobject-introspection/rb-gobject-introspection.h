/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/*
 *  Copyright (C) 2012-2014  Ruby-GNOME2 Project Team
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA  02110-1301  USA
 */

#ifndef RB_GOBJECT_INTROSPECTION_H
#define RB_GOBJECT_INTROSPECTION_H

#include <ruby.h>
#include <rbgobject.h>

#include <girepository.h>

typedef gpointer (*RBGICallbackFinderFunc)(GIArgInfo *info);

typedef struct
{
    GIArgInfo arg_info;
    GIScopeType scope_type;
    GIDirection direction;
    gboolean callback_p;
    gboolean closure_p;
    gboolean destroy_p;
    gboolean array_p;
    gboolean array_length_p;
    gint in_arg_index;
    gint closure_in_arg_index;
    gint destroy_in_arg_index;
    gint array_in_arg_index;
    gint array_length_in_arg_index;
    gint array_length_arg_index;
    gint rb_arg_index;
    gint out_arg_index;
} RBGIArgMetadata;

typedef struct {
    RBGIArgMetadata *metadata;
    VALUE rb_gc_guard_key;
    VALUE rb_callback;
} RBGICallbackData;

void rb_gi_callback_register_finder (RBGICallbackFinderFunc  finder);
void rb_gi_callback_data_free       (RBGICallbackData       *callback_data);

#define RBX_VERSION "2.4.1"

#ifdef RBX_VERSION

#define CONST_ID_CACHE(result, str)			\
    {							\
	static ID rb_intern_id_cache;			\
	if (!rb_intern_id_cache)			\
	    rb_intern_id_cache = rb_intern2((str), (long)strlen(str)); \
	result rb_intern_id_cache;			\
    }
#define CONST_ID(var, str) \
    do CONST_ID_CACHE((var) =, (str)) while (0)
#ifdef __GNUC__
/* __builtin_constant_p and statement expression is available
 * since gcc-2.7.2.3 at least. */
#define rb_intern(str) \
    (__builtin_constant_p(str) ? \
        __extension__ (CONST_ID_CACHE((ID), (str))) : \
        rb_intern(str))
#define rb_intern_const(str) \
    (__builtin_constant_p(str) ? \
     __extension__ (rb_intern2((str), (long)strlen(str))) : \
     (rb_intern)(str))
#else
#define rb_intern_const(str) rb_intern2((str), (long)strlen(str))
#endif

#endif

#endif
