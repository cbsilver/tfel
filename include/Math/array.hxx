/*!
 * \file   array.hxx
 * \brief    
 * \author Helfer Thomas
 * \date   04 May 2006
 */

#ifndef _LIB_TFEL_ARRAY_H_
#define _LIB_TFEL_ARRAY_H_ 

#include <ostream>
#include <cassert>
#include <algorithm>

#include"Config/TFELConfig.hxx"

#include"Utilities/Name.hxx"
#include"Utilities/ToString.hxx"

#include"TypeTraits/IsAssignableTo.hxx"
#include"TypeTraits/IsInvalid.hxx"

#include"Math/General/BasicOperations.hxx"

#include"Math/Array/ArrayConcept.hxx"
#include"Math/Array/ArrayConceptOperations.hxx"
#include"Math/Array/ArrayExpr.hxx"
#include"Math/Array/ArrayRowMajorStorage.hxx"

namespace tfel{
  
  namespace math {

    template<unsigned short N,typename T=double,
	     template<unsigned short,typename> class TStorage=ArrayRowMajorStorage>
    class array;

    template<unsigned short N,typename T,
	     template<unsigned short,typename> class TStorage>
    struct ArrayTraits<array<N,T,TStorage> >
    {
      typedef T NumType;
      static const unsigned short dimension = N;
    };

    template<unsigned short N,typename T,
	     template<unsigned short,typename> class TStorage>
    struct array
      : public ArrayConcept<array<N,T,TStorage> >,
	public TStorage<N,T>
    {
      
      /*!
       * \brief  Return the name of the class.
       * \param  void.
       * \return std::string, the name of the class.
       * \see    Name.
       */
      static
      const std::string
      getName(void){
	using namespace tfel::utilities;
	std::string tmp = "array<"+ToString(N)+","+Name<T>::getName();
	tmp+=","+Name<TStorage<N,T> >::getName()+">";
	return tmp;
      }

      typedef typename TStorage<N,T>::RunTimeProperties RunTimeProperties;
      typedef typename TStorage<N,T>::value_type             value_type;
      typedef typename TStorage<N,T>::pointer                pointer;
      typedef typename TStorage<N,T>::const_pointer          const_pointer;
      typedef typename TStorage<N,T>::iterator               iterator;
      typedef typename TStorage<N,T>::const_iterator         const_iterator;
      typedef typename TStorage<N,T>::const_reverse_iterator const_reverse_iterator;
      typedef typename TStorage<N,T>::reverse_iterator       reverse_iterator;
      typedef typename TStorage<N,T>::reference              reference;
      typedef typename TStorage<N,T>::const_reference        const_reference;
      typedef typename TStorage<N,T>::size_type              size_type;
      typedef typename TStorage<N,T>::difference_type        difference_type;

      array()
	: TStorage<N,T>()
      {}
      
      array(const RunTimeProperties properties)
	: TStorage<N,T>(properties)
      {}

      array(const RunTimeProperties properties, const T init)
	: TStorage<N,T>(properties)
      {
	std::fill(this->begin(),this->end(),init);
      }

      array(const array<N,T,TStorage>& src)
	: TStorage<N,T>(src)
      {}

      array<N,T,TStorage>& operator=(const array<N,T,TStorage>& src)
      {
	TStorage<N,T>::operator=(src);
	return *this;
      }
      
      template<typename T2, typename Expr>
      TFEL_MATH_INLINE 
      typename tfel::meta::EnableIf<
	tfel::typetraits::IsAssignableTo<T2,T>::cond,
	array<N,T,TStorage>&
      >::type
      operator=(const ArrayExpr<array<N,T2,TStorage>,Expr> &expr)
      {
	TStorage<N,T>::operator=(expr);
	return *this;
      }

      using TStorage<N,T>::operator();
      
      template<typename InputIterator>
      TFEL_MATH_INLINE2 void copy(const InputIterator b,const InputIterator e)
      {
	std::copy(b,e,this->begin());
      }

    };
    
    // Serialisation operator
    template<unsigned short N,typename T,
	     template<unsigned short,typename> class TStorage>
    std::ostream & operator << (std::ostream &, const array<N,T,TStorage>&);
    
  } // end of namespace math

  namespace typetraits{
    
    template<unsigned short N,typename T2,typename T,
	     template<unsigned short,typename> class TStorage>
    struct IsAssignableTo<tfel::math::array<N,T2,TStorage>,tfel::math::array<N,T,TStorage> >
    {
      /*!
       *  Result
       */
      static const bool cond = IsAssignableTo<T2,T>::cond;
    };

  } // end of namespace typetraits

} // end of namespace tfel

#include "Math/Array/array.ixx"
#include "Math/Array/arrayResultType.hxx"

#endif /* _LIB_TFEL_ARRAY_H */

