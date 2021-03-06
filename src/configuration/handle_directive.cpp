// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN						\
  "%s code, %zd i, %p node, %p fileroot -> %s (%s %s on line %d)"

bool			_bunny_handle_directive(const char		*code,
						ssize_t			&i,
						SmallConf		*node,
						t_bunny_configuration	*fileroot,
						void			(*read_separator)
						(const char*,ssize_t&))
{
  char			buffer[512];

  if (readtext(code, i, "@include") && fileroot)
    {
      read_separator(code, i);
      if (readstring(code, i, &buffer[0], sizeof(buffer)) == false)
	return (false);
      if (bunny_load_configuration
	  (bunny_which_format(&buffer[0]), &buffer[0], fileroot) == NULL)
	scream_error_if(return (false), BE_SYNTAX_ERROR, PATTERN,
			"ressource,configuration",
			code, i, node, fileroot, "false", "Error while loading ",
			&buffer[0], whichline(code, i));
    }
  else if (readtext(code, i, "@insert") && node)
    {
      read_separator(code, i);
      if (readstring(code, i, &buffer[0], sizeof(buffer)) == false)
	return (false);
      if (bunny_load_configuration
	  (bunny_which_format(&buffer[0]), &buffer[0], node) == NULL)
	scream_error_if(return (false), BE_SYNTAX_ERROR, PATTERN,
			"ressource,configuration",
			code, i, node, fileroot, "false", "Error while loading ",
			&buffer[0], whichline(code, i));
    }
  else
    scream_error_if(return (false), BE_SYNTAX_ERROR,  PATTERN,
		    "ressource,configuration,syntax",
		    code, i, node, fileroot, "false",
		    "Unknow or unsupported directive ",
		    "", whichline(code, i));
  scream_log_if(PATTERN, "ressource,configuration",
		code, i, node, fileroot, "false", "Success", "", whichline(code, i));
  return (true);
}

