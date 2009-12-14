/*!
 * \file   BinaryFunction.hxx
 * \brief  
 * 
 * \author Helfer Thomas
 * \date   02 oct 2007
 */

#ifndef _LIB_TFEL_BINARYFUNCTION_HXX_
#define _LIB_TFEL_BINARYFUNCTION_HXX_ 

#include"Utilities/SmartPtr.hxx"
#include"Math/Parser/Expr.hxx"

namespace tfel
{
  namespace math
  {

    namespace parser
    {

      struct BinaryFunction
	: public Expr
      {
	virtual ~BinaryFunction();
      };

      template<double (*f)(const double,const double)>
      struct StandardBinaryFunction
	: public BinaryFunction
      {
	StandardBinaryFunction(const tfel::utilities::SmartPtr<Expr>,
			       const tfel::utilities::SmartPtr<Expr>);
	void
	checkCyclicDependency(const std::vector<std::string>&) const
	  throw(std::runtime_error);
	double getValue(void) const;
	tfel::utilities::SmartPtr<Expr>
	resolveDependencies(void) const;
	tfel::utilities::SmartPtr<Expr>
	differentiate(const std::vector<double>::size_type,
		      const std::vector<double>&) const;
	tfel::utilities::SmartPtr<Expr>
	clone(const std::vector<double>&) const;
	~StandardBinaryFunction();
      private:
	const tfel::utilities::SmartPtr<Expr> expr1;
	const tfel::utilities::SmartPtr<Expr> expr2;
      }; // end of struct StandardBinaryFunction

    } // end of namespace parser

  } // end of namespace math

} // end of namespace tfel

#include"Math/Parser/BinaryFunction.ixx"

#endif /* _LIB_TFEL_BINARYFUNCTION_HXX */

