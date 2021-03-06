/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file depth.h
**
*/

#ifndef				__LAPIN_DEPTH_H__
# define			__LAPIN_DEPTH_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** ******************************************************************
** ************** HANGED BUNNY STUDIO DEPTH ENGINE ******************
** ******************************************************************
**
** This context is the HBS Depth graphic engine. The depth engine
** is a display context: it brings specific objects like map or camera.
** It relies on specificaly designed t_bunny_sprite.
**
** The main purpose of the Depth engine is to display a tilemap with sprites.
** Its main characteristics that makes him special against other tilemap system
** is its layered map and 3D parallax functionnalities:
**  - Depth can display a parallax of raw layers of pictures
**  - Depth can display a parallax of tiles
**  - Depth can stack several maps
** Additionnaly, Depth brings:
**  - Raytraced shadows
**  - Normal maps
**
** All those features can be enabled or disabled as you need.
**
** The engine is not only a context but also a micro set of functions
** that you should use instead of some regular liblapin functions, they
** are mainly display functions that will allow you to draw inside
** the Depth environment.
*/
typedef struct			s_bunny_depth_engine
{
  t_bunny_context_runtime_info	head;
  // Launch only parameters
  const char			*configuration_file;
  const char			*shader_file;
  // Runtime parameter
  bool				enable_shadows;
  t_bunny_color			back_color;
  t_bunny_color			light_color;
  t_bunny_position		camera;
  int				camera_height;
  double			camera_angle;
  const char			_private[512];
}				t_bunny_depth_engine;

extern const t_bunny_context	gl_bunny_depth_context;

#endif	/*			__LAPIN_DEPTH_H__		*/
