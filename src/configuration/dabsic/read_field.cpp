// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

Decision		dabsic_read_field(const char			*code,
					  ssize_t			&i,
					  SmallConf			&conf)
{
  SmallConf		*newnode;
  Decision		ret;

  dabsic_read_separator(code, i);
  if (readtext(code, i, "["))
    {
      if ((newnode = dabsic_field_name(code, i, conf)) == NULL)
	return (BD_ERROR);

      if ((ret = dabsic_read_inside_scope(code, i, *newnode)) != BD_OK)
	return (ret);
      if (readtext(code, i, "]") == false)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "The token ']' was expected to close the dictionnary scope on line %d",
	   whichline(code, i)
	   );
      dabsic_read_separator(code, i);
      return (BD_OK);
    }

  if (readtext(code, i, "{"))
    {
      if ((newnode = dabsic_field_name(code, i, conf)) == NULL)
	return (BD_ERROR);

      if ((ret = dabsic_read_inside_array(code, i, *newnode)) != BD_OK)
	return (ret);
      dabsic_read_separator(code, i);
      if (readtext(code, i, "}") == false)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "The token '}' was expected to close the array scope on line %d",
	   whichline(code, i)
	   );
      dabsic_read_separator(code, i);
      return (BD_OK);
    }

  if (readtext(code, i, "<"))
    {
      if ((newnode = dabsic_field_name(code, i, conf)) == NULL)
	return (BD_ERROR);

      if ((ret = dabsic_read_inside_xml(code, i, *newnode)) != BD_OK)
	return (ret);
      dabsic_read_separator(code, i);
      if (readtext(code, i, ">") == false)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "The token '>' was expected to close the XML scope on line %d",
	   whichline(code, i)
	   );
      dabsic_read_separator(code, i);
      return (BD_OK);
    }

  if ((newnode = dabsic_field_name(code, i, conf, false)) == NULL)
    return (BD_NOT_FOUND);
  if (dabsic_read_field_value(code, i, *newnode) == BD_ERROR)
    return (BD_ERROR);
  dabsic_read_separator(code, i);
  return (BD_OK);
}
