/*
    Awesome Tower Defense
    Copyright (C) 2008-2009  Trygve Vea and contributors (read AUTHORS)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef __GFX_CHARMAP_H__
#define __GFX_CHARMAP_H__

#include <SDL.h>

#define CHAR_COUNT 42
#define CHAR_SIZE_X 8
#define CHAR_SIZE_Y 8

void draw_text(SDL_Surface *s, const char *text, int x, int y);
void draw_text_color(SDL_Surface *s, const char *text, int x, int y, int r, int g, int b);


#endif /* __GFX_CHARMAP_H__ */
