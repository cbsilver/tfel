/*!
 * \file   FctArrayExpr.hxx 
 * \brief  This file implements the type generated by the application of standard mathematical functions on arrays.
 * \author Helfer Thomas
 * \date   01 jui 2006
 */

#ifndef _LIB_TFEL_FCT_ARRAY_EXPR_HXX_
#define _LIB_TFEL_FCT_ARRAY_EXPR_HXX_ 

#include <string>

#include"TFEL/Config/TFELConfig.hxx"

#include"TFEL/Utilities/Name.hxx"

#include"TFEL/Metaprogramming/StaticAssert.hxx"
#include"TFEL/Metaprogramming/Implements.hxx"
#include"TFEL/TypeTraits/IsTemporary.hxx"

#include"TFEL/Math/Array/ArrayConcept.hxx"
#include"TFEL/Math/General/FctObjectRandomAccessConstIterator.hxx"

namespace tfel{

  namespace math {

    /*!											
     * brief  Defines the FctArrayExpr.						
     * param  A, a vector type								
     * author Helfer Thomas								
     * date   01 jui 2006								
     */											
    template<typename A,typename Func>
    class FctArrayExpr	       						                
    {										        
      										        
      TFEL_STATIC_ASSERT((tfel::meta::Implements<A,ArrayConcept>::cond));
      TFEL_STATIC_ASSERT((tfel::meta::Implements<Func,FunctionConcept>::cond));
										        
      typedef typename ArrayTraits<A>::NumType   NumTypeA;                             
      typedef unsigned int IndexType;			        
      static const bool IsATemporary = tfel::typetraits::IsTemporary<A>::cond;          
      										        
      typename tfel::meta::IF<IsATemporary,const A,const A&>::type a;                   
      const Func f;
      const typename A::RunTimeProperties RTP;                                          
            									        
      FctArrayExpr();							         	
										        
    public:									        
      										        
      typedef typename ComputeUnaryResult<NumTypeA,Func>::Handle NumType;             
      										        
      static const std::string 
      getName(void){ 
	using namespace std;
	using namespace tfel::utilities;
	return string("FctArrayExpr<")
	  +Name<A>::getName()
	  +Name<Func>::getName()
	  +string(">");        
      }
       								        
    protected:									        
										        
      typedef A    first_arg;
      typedef Func second_arg;

      typedef NumType        value_type;                                                
      typedef NumType*       pointer;	    						
      typedef const NumType* const_pointer; 						
      typedef NumType&       reference;	    						
      typedef const NumType& const_reference;						
      typedef IndexType      size_type;	    						
      typedef ptrdiff_t      difference_type;						
										        
      TFEL_MATH_INLINE FctArrayExpr(const A& l,const Func& r)				        
	: a(l),f(r),RTP(a.getRunTimeProperties())					        
      {}         							                
										        
      TFEL_MATH_INLINE FctArrayExpr(const FctArrayExpr& src)	        	        
	: a(src.a),f(src.f),RTP(src.RTP)						        
      {}									        
      										        
      TFEL_MATH_INLINE const NumType                                                    
      operator()(const IndexType i) const                                               
      {                                                                                 
	return f(a(i)); 						                
      }										        

      TFEL_MATH_INLINE const NumType                                                    
      operator()(const IndexType i,const IndexType j) const
      {                                                                                 
	return f(a(i,j));
      }										        

      TFEL_MATH_INLINE const NumType                                                    
      operator()(const IndexType i,const IndexType j,const IndexType k) const
      {                                                                                 
	return f(a(i,j,k));
      }										        
                                                                                        
    public:                                                                             
                                                                                        
      typedef typename A::RunTimeProperties RunTimeProperties;                          
      typedef FctObjectRandomAccessConstIterator<A,Func> const_iterator;     		
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;		
										        
      TFEL_MATH_INLINE const RunTimeProperties                                          
      getRunTimeProperties(void) const                                                  
      {                                                                                 
	return RTP;                                                                     
      }                                                                                 
                                                                                        
      TFEL_MATH_INLINE const_iterator begin(void) const                           	
      {											
	return const_iterator(a.begin(),f);        					
      }											
 											
      TFEL_MATH_INLINE const_iterator end(void) const	                                
      {											
	return const_iterator(a.end(),f);   						
      }											
											
      TFEL_MATH_INLINE const_reverse_iterator rbegin(void) const		        
      {											
	return const_reverse_iterator(end(),f);						
      }											
											
      TFEL_MATH_INLINE const_reverse_iterator rend(void) const                          
      {											
	return const_reverse_iterator(begin(),f);						
      }                                                                                 

    };
        
  } // end of namespace math

} // end of namespace tfel
  
#endif /* _LIB_TFEL_FCT_ARRAY_EXPR_HXX */
