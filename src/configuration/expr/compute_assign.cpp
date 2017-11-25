// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

bool			expr_compute_assign(Expression		&exp,
					    bool		dry,
					    SmallConf		*root,
					    SmallConf		*local,
					    SmallConf		*artif,
					    SmallConf		*param)
{
  int			i;


  if (exp.operand[exp.operand.size() - 1]->optor_family != -1)
    {
      if (gl_expr_computation[exp.operand[exp.operand.size() - 1]->optor_family]
	  (*exp.operand[exp.operand.size() - 1], dry, root, local, artif, param)
	  == false)
	return (false);
    }

  for (i = exp.operand.size() - 2; i >= 0; --i)
    {
      Expression	&x = *exp.operand[i];
      SmallConf		*ope;

      if (x.optor_family == -1)
	{} // Operand
      else if (gl_expr_computation[x.optor_family]
	       (x, dry, root, local, artif, param) == false)
	return (false);

      ope = &x.val;
      if (ope->last_type == SmallConf::RAWSTRING)
	{
	  if ((ope = expr_get_variable
	       (*ope, dry, root, local, artif, param)) == NULL)
	    scream_error_if
	      (return (false), BE_BAD_ADDRESS,
	       "Undefined variable or unresolvable address %s on line %d",
	       exp.operand[i]->val.original_value.c_str(), exp.line);
	}
      else
	scream_error_if
	  (return (false), BE_BAD_ADDRESS,
	   "A variable was expected as lvalue for assignation on line %d",
	   exp.line);

      if (i < (int)exp.operand.size() - 1 && dry == false)
	{
	  if (x.optor == Expression::BEO_ASSIGN)
	    *ope = exp.operand[i + 1]->val;
	  else if (x.optor == Expression::BEO_REC_ASSIGN)
	    {
	      if (SmallConf::RecursiveAssign
		  (*ope, exp.operand[i + 1]->val, true, true) == false)
		return (false);
	    }
	  else if (x.optor == Expression::BEO_ARRAY_ASSIGN)
	    {
	      if (SmallConf::RecursiveAssign
		  (*ope, exp.operand[i + 1]->val, false, true) == false)
		return (false);
	    }
	  else if (x.optor == Expression::BEO_HASH_ASSIGN)
	    {
	      if (SmallConf::RecursiveAssign
		  (*ope, exp.operand[i + 1]->val, true, false) == false)
		return (false);
	    }
	  else if (x.optor == Expression::BEO_LOR_ASSIGN)
	    {
	      int	a, b;

	      if (exp.operand[i + 1]->val.last_type == SmallConf::STRING
		  || ope->last_type == SmallConf::STRING)
		scream_error_if
		  (return (false), BE_BAD_ADDRESS,
		   "Operator '||=' expect numeric types on line %d",
		   exp.line);
	      if (ope->GetInt(&a) == false
		  || exp.operand[i + 1]->val.GetInt(&b) == false)
		return (false);
	      a = !!a || !!b;
	      ope->SetInt(a);
	    }
	  else if (x.optor == Expression::BEO_LXOR_ASSIGN)
	    {
	      int	a, b;

	      if (exp.operand[i + 1]->val.last_type == SmallConf::STRING
		  || ope->last_type == SmallConf::STRING)
		scream_error_if
		  (return (false), BE_BAD_ADDRESS,
		   "Operator '^^=' expect numeric types on line %d",
		   exp.line);
	      if (ope->GetInt(&a) == false
		  || exp.operand[i + 1]->val.GetInt(&b) == false)
		return (false);
	      a = (!!a != !!b);
	      ope->SetInt(a);
	    }
	  else if (x.optor == Expression::BEO_LAND_ASSIGN)
	    {
	      int	a, b;

	      if (exp.operand[i + 1]->val.last_type == SmallConf::STRING
		  || ope->last_type == SmallConf::STRING)
		scream_error_if
		  (return (false), BE_BAD_ADDRESS,
		   "Operator '&&=' expect numeric types on line %d",
		   exp.line);
	      if (ope->GetInt(&a) == false
		  || exp.operand[i + 1]->val.GetInt(&b) == false)
		return (false);
	      a = (!!a && !!b);
	      ope->SetInt(a);
	    }

	  else if (x.optor == Expression::BEO_BOR_ASSIGN)
	    {
	      int	a, b;

	      if (exp.operand[i + 1]->val.last_type != SmallConf::INTEGER
		  || ope->last_type != SmallConf::INTEGER)
		scream_error_if
		  (return (false), BE_BAD_ADDRESS,
		   "Operator '|=' expect integer types on line %d",
		   exp.line);
	      if (ope->GetInt(&a) == false
		  || exp.operand[i + 1]->val.GetInt(&b) == false)
		return (false);
	      a = a | b;
	      ope->SetInt(a);
	    }
	  else if (x.optor == Expression::BEO_BXOR_ASSIGN)
	    {
	      int	a, b;

	      if (exp.operand[i + 1]->val.last_type != SmallConf::INTEGER
		  || ope->last_type != SmallConf::INTEGER)
		scream_error_if
		  (return (false), BE_BAD_ADDRESS,
		   "Operator '^=' expect integer types on line %d",
		   exp.line);
	      if (ope->GetInt(&a) == false
		  || exp.operand[i + 1]->val.GetInt(&b) == false)
		return (false);
	      a = (a ^ b);
	      ope->SetInt(a);
	    }
	  else if (x.optor == Expression::BEO_BAND_ASSIGN)
	    {
	      int	a, b;

	      if (exp.operand[i + 1]->val.last_type != SmallConf::INTEGER
		  || ope->last_type != SmallConf::INTEGER)
		scream_error_if
		  (return (false), BE_BAD_ADDRESS,
		   "Operator '&=' expect integer types on line %d",
		   exp.line);
	      if (ope->GetInt(&a) == false
		  || exp.operand[i + 1]->val.GetInt(&b) == false)
		return (false);
	      a = (a & b);
	      ope->SetInt(a);
	    }

	  else if (x.optor == Expression::BEO_LSHIFT_ASSIGN)
	    {
	      int	a, b;

	      if (exp.operand[i + 1]->val.last_type != SmallConf::INTEGER
		  || ope->last_type != SmallConf::INTEGER)
		scream_error_if
		  (return (false), BE_BAD_ADDRESS,
		   "Operator '<<=' expect integer types on line %d",
		   exp.line);
	      if (ope->GetInt(&a) == false
		  || exp.operand[i + 1]->val.GetInt(&b) == false)
		return (false);
	      a = (a << b);
	      ope->SetInt(a);
	    }
	  else if (x.optor == Expression::BEO_RSHIFT_ASSIGN)
	    {
	      int	a, b;

	      if (exp.operand[i + 1]->val.last_type != SmallConf::INTEGER
		  || ope->last_type != SmallConf::INTEGER)
		scream_error_if
		  (return (false), BE_BAD_ADDRESS,
		   "Operator '>>=' expect integer types on line %d",
		   exp.line);
	      if (ope->GetInt(&a) == false
		  || exp.operand[i + 1]->val.GetInt(&b) == false)
		return (false);
	      a = (a >> b);
	      ope->SetInt(a);
	    }

	  else if (x.optor == Expression::BEO_ADD_ASSIGN)
	    {
	      double	a, b;

	      if (exp.operand[i + 1]->val.last_type == SmallConf::STRING
		  || ope->last_type == SmallConf::STRING)
		scream_error_if
		  (return (false), BE_BAD_ADDRESS,
		   "Operator '+=' expect numeric types on line %d",
		   exp.line);
	      if (ope->GetDouble(&a) == false
		  || exp.operand[i + 1]->val.GetDouble(&b) == false)
		return (false);
	      a = (a + b);
	      if (ope->last_type == SmallConf::DOUBLE
		  || exp.operand[i + 1]->val.last_type == SmallConf::DOUBLE)
		ope->SetDouble(a);
	      else
		ope->SetInt(a);
	    }
	  else if (x.optor == Expression::BEO_SUB_ASSIGN)
	    {
	      double	a, b;

	      if (exp.operand[i + 1]->val.last_type == SmallConf::STRING
		  || ope->last_type == SmallConf::STRING)
		scream_error_if
		  (return (false), BE_BAD_ADDRESS,
		   "Operator '-=' expect numeric types on line %d",
		   exp.line);
	      if (ope->GetDouble(&a) == false
		  || exp.operand[i + 1]->val.GetDouble(&b) == false)
		return (false);
	      a = (a - b);
	      if (ope->last_type == SmallConf::DOUBLE
		  || exp.operand[i + 1]->val.last_type == SmallConf::DOUBLE)
		ope->SetDouble(a);
	      else
		ope->SetInt(a);
	    }
	  else if (x.optor == Expression::BEO_MUL_ASSIGN)
	    {
	      double	a, b;

	      if (exp.operand[i + 1]->val.last_type == SmallConf::STRING
		  || ope->last_type == SmallConf::STRING)
		scream_error_if
		  (return (false), BE_BAD_ADDRESS,
		   "Operator '*=' expect numeric types on line %d",
		   exp.line);
	      if (ope->GetDouble(&a) == false
		  || exp.operand[i + 1]->val.GetDouble(&b) == false)
		return (false);
	      a = (a * b);
	      if (ope->last_type == SmallConf::DOUBLE
		  || exp.operand[i + 1]->val.last_type == SmallConf::DOUBLE)
		ope->SetDouble(a);
	      else
		ope->SetInt(a);
	    }
	  else if (x.optor == Expression::BEO_DIV_ASSIGN)
	    {
	      double	a, b;

	      if (exp.operand[i + 1]->val.last_type == SmallConf::STRING
		  || ope->last_type == SmallConf::STRING)
		scream_error_if
		  (return (false), BE_BAD_ADDRESS,
		   "Operator '/=' expect numeric types on line %d",
		   exp.line);
	      if (ope->GetDouble(&a) == false
		  || exp.operand[i + 1]->val.GetDouble(&b) == false)
		return (false);
	      a = (a / b);
	      if (ope->last_type == SmallConf::DOUBLE
		  || exp.operand[i + 1]->val.last_type == SmallConf::DOUBLE)
		ope->SetDouble(a);
	      else
		ope->SetInt(a);
	    }
	  else if (x.optor == Expression::BEO_MOD_ASSIGN)
	    {
	      double	a, b;

	      if (exp.operand[i + 1]->val.last_type == SmallConf::STRING
		  || ope->last_type == SmallConf::STRING)
		scream_error_if
		  (return (false), BE_BAD_ADDRESS,
		   "Operator '%%=' expect numeric types on line %d",
		   exp.line);
	      if (ope->GetDouble(&a) == false
		  || exp.operand[i + 1]->val.GetDouble(&b) == false)
		return (false);
	      a = fmod(a, b);
	      if (ope->last_type == SmallConf::DOUBLE
		  || exp.operand[i + 1]->val.last_type == SmallConf::DOUBLE)
		ope->SetDouble(a);
	      else
		ope->SetInt(a);
	    }
	  else if (x.optor == Expression::BEO_POW_ASSIGN)
	    {
	      double	a, b;

	      if (exp.operand[i + 1]->val.last_type == SmallConf::STRING
		  || ope->last_type == SmallConf::STRING)
		scream_error_if
		  (return (false), BE_BAD_ADDRESS,
		   "Operator '**=' expect numeric types on line %d",
		   exp.line);
	      if (ope->GetDouble(&a) == false
		  || exp.operand[i + 1]->val.GetDouble(&b) == false)
		return (false);
	      a = pow(a, b);
	      if (ope->last_type == SmallConf::DOUBLE
		  || exp.operand[i + 1]->val.last_type == SmallConf::DOUBLE)
		ope->SetDouble(a);
	      else
		ope->SetInt(a);
	    }
	  else if (x.optor == Expression::BEO_ADD_ASSIGN)
	    {
	      std::stringstream ss;
	      const char	*a, *b;

	      if (exp.operand[i + 1]->val.last_type != SmallConf::STRING
		  || ope->last_type != SmallConf::STRING)
		scream_error_if
		  (return (false), BE_BAD_ADDRESS,
		   "Operator '#=' expect string types on line %d",
		   exp.line);
	      if (ope->GetString(&a) == false
		  || exp.operand[i + 1]->val.GetString(&b) == false)
		return (false);
	      ss << a << b;
	      ope->SetString(ss.str());
	    }
	}
    }

  return (true);
}
