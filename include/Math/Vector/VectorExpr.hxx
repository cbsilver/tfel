#ifndef _MATH_VECTOR_EXPR_LIB_
#define _MATH_VECTOR_EXPR_LIB_ 1

#include <string>
#include <ostream>

#include "Config/TFELConfig.hxx"

#include "Utilities/Name.hxx"
#include "Metaprogramming/IF.hxx"
#include "Metaprogramming/EmptyClass.hxx"
#include "Metaprogramming/HasIterator.hxx"
#include "Metaprogramming/HasConstIterator.hxx"
#include "TypeTraits/IsTemporary.hxx"
#include "Math/General/BasicOperations.hxx"
#include "Math/Vector/VectorConcept.hxx"

namespace tfel{

  namespace math{

    template<typename T_type, typename Expr>
    class VectorExpr;

    template<typename T_type, typename Expr>
    struct VectorTraits<VectorExpr<T_type,Expr> >{
      typedef typename Expr::NumType NumType;
      typedef typename VectorTraits<T_type>::IndexType IndexType;
    };

    template<typename T_type, typename Expr>
    class VectorExpr
      : public VectorConcept<VectorExpr<T_type,Expr> >,
	public Expr
    {

      VectorExpr& operator=(const VectorExpr&);

    public:

      typedef typename Expr::RunTimeProperties RunTimeProperties;
      typedef typename Expr::value_type      value_type;      
      typedef typename Expr::pointer	     pointer;	    
      typedef typename Expr::const_pointer   const_pointer; 
      typedef typename Expr::reference	     reference;	    
      typedef typename Expr::const_reference const_reference;
      typedef typename Expr::size_type 	     size_type;	    
      typedef typename Expr::difference_type difference_type;

      /*!
       * \brief  Return the name of the class.
       * \param  void.
       * \return std::string, the name of the class.
       * \see    Name.
       */
      static 
      const std::string
      getName(void){
	using namespace std;
	using namespace tfel::utilities;
	return string("VectorExpr<")
	  +Name<T_type>::getName()+string(",")
	  +Name<Expr>::getName()+string(">");
      }

      explicit TFEL_MATH_INLINE VectorExpr()
	: Expr()
      {}

      TFEL_MATH_INLINE VectorExpr(const VectorExpr& src)
	: Expr(src)	
      {}

      explicit TFEL_MATH_INLINE VectorExpr(const typename Expr::first_arg& a_)
	: Expr(a_)
      {}

      explicit TFEL_MATH_INLINE VectorExpr(const typename Expr::first_arg&  a_, 
					   const typename Expr::second_arg& b_)
	: Expr(a_,b_)
      {}
      
      using Expr::operator();

      ~VectorExpr()
      {}

    };

    template<typename T_type, typename Expr>
    struct VectorType<VectorExpr<T_type,Expr> >
    {
      typedef T_type type;
    };

  } // end of math namespace
  
  namespace typetraits{

    template<typename T_type, typename Expr>
    struct IsTemporary<tfel::math::VectorExpr<T_type,Expr> >
    {
      static const bool cond = true;
    };

  }// end of namespace typetraits

} // end of TFEL namespace

#endif /* _MATH_VECTOR_EXPR_LIB_ */
