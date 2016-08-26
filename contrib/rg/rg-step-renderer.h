/* rg-line-renderer.h
 *
 * Copyright (C) 2015 Christian Hergert <christian@hergert.me>
 *
 * This file is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 3 of the
 * License, or (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef RG_STEP_RENDERER_H
#define RG_STEP_RENDERER_H

#include <gdk/gdk.h>

#include "rg-renderer.h"

G_BEGIN_DECLS

#define RG_TYPE_STEP_RENDERER (rg_step_renderer_get_type())

G_DECLARE_FINAL_TYPE (RgStepRenderer, rg_step_renderer, RG, STEP_RENDERER, GObject)

RgStepRenderer *rg_step_renderer_new (void);
void            rg_step_renderer_set_stroke_color      (RgStepRenderer *self,
                                                        const gchar    *stroke_color);
void            rg_step_renderer_set_stroke_color_rgba (RgStepRenderer *self,
                                                        const GdkRGBA  *stroke_color_rgba);
const GdkRGBA  *rg_step_renderer_get_stroke_color_rgba (RgStepRenderer *self);

G_END_DECLS

#endif /* RG_STEP_RENDERER_H */
