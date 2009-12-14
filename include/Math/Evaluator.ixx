/*!
 * \file   Evaluator.ixx
 * \brief  
 * 
 * \author Helfer Thomas
 * \date   12 jan 2009
 */

#ifndef _LIB_TFEL_MATH_EVALUATOR_IXX_
#define _LIB_TFEL_MATH_EVALUATOR_IXX_ 

#include"Math/Parser/Function.hxx"
#include"Math/Parser/BinaryFunction.hxx"

namespace tfel
{

  namespace math
  {

    template<double (*f)(const double)>
    tfel::utilities::SmartPtr<tfel::math::parser::Expr>
    StandardFctGenerator(tfel::utilities::SmartPtr<tfel::math::parser::Expr> e)
    {
      using namespace tfel::utilities;
      using namespace tfel::math::parser;
      return SmartPtr<Expr>(new StandardFunction<f>(e));
    } // end of Evaluator::FctGenerator::StandardFctGenerator

    template<double (*f)(const double,const double)>
    tfel::utilities::SmartPtr<tfel::math::parser::Expr>
    StandardBinaryFctGenerator(tfel::utilities::SmartPtr<tfel::math::parser::Expr> e1,
			       tfel::utilities::SmartPtr<tfel::math::parser::Expr> e2)
    {
      using namespace tfel::utilities;
      using namespace tfel::math::parser;
      return SmartPtr<Expr>(new StandardBinaryFunction<f>(e1,e2));
    } // end of Evaluator::FctGenerator::StandardBinaryFctGenerator
  
  } // end of namespace math

} // end of namespace tfel

#endif /* _LIB_TFEL_MATH_EVALUATOR_IXX */
