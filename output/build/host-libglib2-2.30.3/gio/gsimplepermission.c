/*
 * Copyright © 2010 Codethink Limited
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the licence, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * Author: Ryan Lortie <desrt@desrt.ca>
 */

#include "config.h"

#include "gsimplepermission.h"
#include "gpermission.h"


/**
 * SECTION:gsimplepermission
 * @title: GSimplePermission
 * @short_description: A GPermission that doesn't change value
 *
 * #GSimplePermission is a trivial implementation of #GPermission that
 * represents a permission that is either always or never allowed.  The
 * value is given at construction and doesn't change.
 *
 * Calling request or release will result in errors.
 **/

/**
 * GSimplePermission:
 *
 * #GSimplePermission is an opaque data structure.  There are no methods
 * except for those defined by #GPermission.
 **/

typedef GPermissionClass GSimplePermissionClass;

struct _GSimplePermission
{
  GPermission parent_instance;
};

G_DEFINE_TYPE (GSimplePermission, g_simple_permission, G_TYPE_PERMISSION)

static void
g_simple_permission_init (GSimplePermission *simple)
{
}

static void
g_simple_permission_class_init (GSimplePermissionClass *class)
{
}

/**
 * g_simple_permission_new:
 * @allowed: %TRUE if the action is allowed
 * @returns: the #GSimplePermission, as a #GPermission
 *
 * Creates a new #GPermission instance that represents an action that is
 * either always or never allowed.
 *
 * Since: 2.26
 **/
GPermission *
g_simple_permission_new (gboolean allowed)
{
  GPermission *permission = g_object_new (G_TYPE_SIMPLE_PERMISSION, NULL);

  g_permission_impl_update (permission, allowed, FALSE, FALSE);

  return permission;
}
