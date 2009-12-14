/*!
 * \file   DifferentiatedFunctionExpr.hxx
 * \brief  
 * 
 * \author Helfer Thomas
 * \date   02 oct 2007
 */

#ifndef _TFEL_LIB_MATH_PARSER_DIFFERENTIATEDFUNCTIONEXPR_H_
#define _TFEL_LIB_MATH_PARSER_DIFFERENTIATEDFUNCTIONEXPR_H_

#include<string>
#include<vector>
#include<stdexcept>

#include"Utilities/SmartPtr.hxx"
#include"Math/Parser/Expr.hxx"
#include"Math/Parser/ExternalFunction.hxx"

namespace tfel
{

  namespace math
  {

    namespace parser
    {

      struct DifferentiatedFunctionExpr
	: public Expr
      {
	DifferentiatedFunctionExpr(tfel::utilities::SmartPtr<ExternalFunction>,
				   std::vector<tfel::utilities::SmartPtr<Expr> >&,
				   const std::vector<std::vector<double>::size_type>&);
	double
	getValue(void) const;
	void
	checkCyclicDependency(const std::vector<std::string>&) const
	  throw(std::runtime_error);
	tfel::utilities::SmartPtr<Expr>
	differentiate(const std::vector<double>::size_type,
		      const std::vector<double>&) const;
	tfel::utilities::SmartPtr<Expr>
	resolveDependencies(void) const;
	tfel::utilities::SmartPtr<Expr>
	clone(const std::vector<double>&) const;
      private:
	tfel::utilities::SmartPtr<ExternalFunction>
	getDerivative(void) const;
	mutable tfel::utilities::SmartPtr<ExternalFunction> f;
	std::vector<tfel::utilities::SmartPtr<Expr> > args;
	std::vector<std::vector<double>::size_type> pvar;
      }; // end of struct DifferentiatedFunctionExpr

    } // end of namespace parser

  } // end of namespace math

} // end of namespace tfel

#endif  /* _TFEL_LIB_MATH_PARSER_DIFFERENTIATEDFUNCTIONEXPR_H_ */
