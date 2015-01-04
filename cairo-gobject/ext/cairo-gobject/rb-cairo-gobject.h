/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/*
 *  Copyright (C) 2013  Ruby-GNOME2 Project Team
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

#ifndef RB_CAIRO_GOBJECT_H
#define RB_CAIRO_GOBJECT_H

#include <ruby.h>
#include <rbgobject.h>
#include <glib-enum-types.h>

#include <cairo-gobject.h>

#ifndef CAIRO_GOBJECT_TYPE_HINT_METRICS
#  define CAIRO_GOBJECT_TYPE_HINT_METRICS CAIRO_GOBJECT_TYPE_HNT_METRICS
#endif

#ifndef CAIRO_GOBJECT_TYPE_TEXT_CLUSTER_FLAGS
#  define CAIRO_GOBJECT_TYPE_TEXT_CLUSTER_FLAGS cairo_gobject_text_cluster_flags_get_type ()
#endif

#include <rb_cairo.h>

extern void Init_cairo_gobject(void);

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
