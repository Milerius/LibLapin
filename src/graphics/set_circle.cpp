// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN \
  "%p picture, (%d, %d) position, (%d, %d) size, %p color"

void			bunny_set_circle(t_bunny_buffer		*buffer,
					 t_bunny_position	pos,
					 t_bunny_position	siz,
					 unsigned int		color)
{
  size_t		*type = (size_t*)buffer;
  sf::CircleShape	shape;
  double		coef;

  if (*type != SYSTEM_RAM)
    {
      shape.setRadius(siz.x);
      shape.setScale(sf::Vector2f(1, (double)(coef = (double)siz.y / siz.x)));
      shape.setPosition(sf::Vector2f(pos.x - siz.x, pos.y - siz.y));
      shape.setFillColor(sf::Color::Transparent);
      shape.setOutlineColor
	(sf::Color
	 ((color >> (RED_CMP * 8)) & 0xFF,
	  (color >> (GREEN_CMP * 8)) & 0xFF,
	  (color >> (BLUE_CMP * 8)) & 0xFF,
	  (color >> (ALPHA_CMP * 8)) & 0xFF
	  )
	 );
      shape.setOutlineThickness(1);
    }
  switch (*type)
    {
    case WINDOW:
      {
	struct bunny_window	*pic = (struct bunny_window*)buffer;

	pic->window->draw(shape);
	scream_log_if(PATTERN, "graphics", buffer, pos.x, pos.y, siz.x, siz.y, (void*)(size_t)color);
	return ;
      }
    case TTF_TEXT:
    case GRAPHIC_RAM:
    case GRAPHIC_TEXT:
      {
	struct bunny_picture	*pic = (struct bunny_picture*)buffer;

	pic->texture->draw(shape);
	scream_log_if(PATTERN, "graphics", buffer, pos.x, pos.y, siz.x, siz.y, (void*)(size_t)color);
	return ;
      }
    case SYSTEM_RAM:
      {
	t_bunny_pixelarray	*pix = (t_bunny_pixelarray*)buffer;

	if (gl_bunny_my_set_circle == NULL)
	  fprintf(stderr, "gl_bunny_my_set_circle is not set.\n");
	else
	  gl_bunny_my_set_circle(pix, pos, siz, color);
	scream_log_if(PATTERN, "graphics", buffer, pos.x, pos.y, siz.x, siz.y, (void*)(size_t)color);
	return ;
      }
    default:
      scream_error_if(return, EINVAL, PATTERN, "graphics", buffer, pos.x, pos.y, siz.x, siz.y, (void*)(size_t)color);
    }
}
