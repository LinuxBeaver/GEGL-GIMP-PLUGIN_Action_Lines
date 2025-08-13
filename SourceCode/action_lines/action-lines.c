/* This file is an image processing operation for GEGL
 *
 * GEGL is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * GEGL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with GEGL; if not, see <https://www.gnu.org/licenses/>.
 *
 * Credit to Øyvind Kolås (pippin) for major GEGL contributions
 * 2022 Beaver (Action Lines)
 */
/*
June 25 2023 Recreation of GEGL Graph. You can test a static version of this
plugin without installing it by running this syntax in Gimp's GEGL graph plugin.

supernova radius=1200 seed=4422 spokes-count=750 
box-blur radius=1
color-to-alpha color=#ffffff

color-overlay value=#001bff
opacity value=3

 */

#include "config.h"
#include <glib/gi18n-lib.h>

#ifdef GEGL_PROPERTIES

property_double (movex, _("Center X"), 0.50)
  description (_("X coordinates of the center of lines"))
  ui_range (0.20, 0.80)
  ui_meta  ("unit", "relative-coordinate")
  ui_meta  ("axis", "x")

property_double (movey, _("Center Y"), 0.50)
  description (_("Y coordinates of the center of lines"))
  ui_range (0.20, 0.80)
  ui_meta  ("unit", "relative-coordinate")
  ui_meta  ("axis", "y")

property_color (color, _("Color"), "#000000")
    description(_("Select color of the lines."))

property_int (radius, _("Radius"), 3200)
  description (_("Radius of Action Lines"))
  value_range (800, 10000)
  ui_range (1000, 5000)
  ui_meta  ("unit", "pixel-distance")

property_int (lines, _("Increase lines and rotate"), 700)
  description (_("Adds more lines and rotates the effect "))
  value_range (380, 1024)
  ui_range (380, 1024)

property_seed (seed, _("Random seed"), rand)
  description (_("The random seed for lines"))

property_double (opacity, _("Opacity"), 2.0)
	    description (_("Increase the opacity of the lines"))
    value_range (0.6, 3.0)
    ui_range    (0.6, 3.0)



#else

#define GEGL_OP_META
#define GEGL_OP_NAME     actionlines
#define GEGL_OP_C_SOURCE action-lines.c

#include "gegl-op.h"

static void attach (GeglOperation *operation)
{
  GeglNode *gegl = operation->node;
  GeglNode *input, *output, *c2a, *crop, *col, *th, *lines, *blurnova;

  input    = gegl_node_get_input_proxy (gegl, "input");
  output   = gegl_node_get_output_proxy (gegl, "output");


  c2a = gegl_node_new_child (gegl,
                                  "operation", "gegl:color-to-alpha",
                                  NULL);



   lines = gegl_node_new_child (gegl,
                                  "operation", "gegl:supernova",
                                  NULL);

  col = gegl_node_new_child (gegl,
                                  "operation", "gegl:color-overlay",
                                  NULL);


  th = gegl_node_new_child (gegl,
                                  "operation", "gegl:opacity",
                                  NULL);


  blurnova = gegl_node_new_child (gegl,
                                  "operation", "gegl:box-blur", "radius", 1,
                                  NULL);

  crop = gegl_node_new_child (gegl,
                                  "operation", "gegl:crop",
                                  NULL);



  gegl_operation_meta_redirect (operation, "radius", lines, "radius");
  gegl_operation_meta_redirect (operation, "seed", lines, "seed");
  gegl_operation_meta_redirect (operation, "lines", lines, "spokes-count");
  gegl_operation_meta_redirect (operation, "movex", lines, "center-x");
  gegl_operation_meta_redirect (operation, "movey", lines, "center-y");
  gegl_operation_meta_redirect (operation, "color", col, "value");
  gegl_operation_meta_redirect (operation, "opacity", th, "value");


  gegl_node_link_many (input, lines, blurnova, c2a, col, th, crop, output, NULL);
  gegl_node_connect (crop, "aux", input, "output");



}

static void
gegl_op_class_init (GeglOpClass *klass)
{
  GeglOperationClass *operation_class;

  operation_class = GEGL_OPERATION_CLASS (klass);

  operation_class->attach = attach;

  gegl_operation_class_set_keys (operation_class,
    "name",        "lb:action-lines",
    "title",       _("Action Lines"),
    "reference-hash", "45ed5656a28f25j0f0f25sb2ac",
    "description", _("Render line rays that circle the image"
                     ""),
    "gimp:menu-path", "<Image>/Filters/Render/Fun",
    "gimp:menu-label", _("Action Lines..."),
    NULL);
}

#endif
