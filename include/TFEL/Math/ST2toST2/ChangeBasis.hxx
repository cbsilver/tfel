/*!
 * \file   ChangeBasis.hxx
 * \brief    
 * \author THOMAS HELFER
 * \date   13 oct. 2015
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef _LIB_TFEL_MATH_ST2TOST2_CHANGEBASIS_HXX_
#define _LIB_TFEL_MATH_ST2TOST2_CHANGEBASIS_HXX_

#include<type_traits>

namespace tfel{

  namespace math{

    namespace st2tost2_internals{

      /*!
       * \brief an auxiliary structure used to dispatch over the
       * dimension
       */
      template<unsigned short>
      struct ChangeBasis;

      /*!
       * \brief partial specialisation in 1D
       */
      template<>
      struct ChangeBasis<1u>{
	/*!
	 */
	template<typename ST2toST2Type>
	static TFEL_MATH_INLINE2
	typename std::enable_if<(tfel::meta::Implements<ST2toST2Type,tfel::math::ST2toST2Concept>::cond&&
				 tfel::math::ST2toST2Traits<ST2toST2Type>::dime==1u),
				tfel::math::st2tost2<1u,typename tfel::math::ST2toST2Traits<ST2toST2Type>::NumType>
				>::type
	exe(const ST2toST2Type& s,
	    const tfel::math::tmatrix<3,3,typename tfel::typetraits::BaseType<typename tfel::math::ST2toST2Traits<ST2toST2Type>::NumType>::type>&){
	  return s;
	}
      }; // end of ChangeBasis<1u>
      /*!
       * \brief partial specialisation in 2D
       */
      template<>
      struct ChangeBasis<2u>{
	/*!
	 * \param[in] r : rotation matrix
	 */
	template<typename ST2toST2Type>
	static TFEL_MATH_INLINE2
	typename std::enable_if<(tfel::meta::Implements<ST2toST2Type,tfel::math::ST2toST2Concept>::cond&&
				 tfel::math::ST2toST2Traits<ST2toST2Type>::dime==2u),
				tfel::math::st2tost2<2u,typename tfel::math::ST2toST2Traits<ST2toST2Type>::NumType>
				>::type
	exe(const ST2toST2Type& s,
	    const tfel::math::tmatrix<3,3,typename tfel::typetraits::BaseType<typename tfel::math::ST2toST2Traits<ST2toST2Type>::NumType>::type>& r)
	{
	  using st2tost2 = tfel::math::st2tost2<2u,typename tfel::math::ST2toST2Traits<ST2toST2Type>::NumType>;
	  const auto sr  = st2tost2::fromRotationMatrix(r);
	  const auto sir = st2tost2::fromRotationMatrix(transpose(r));
	  return sr*s*sir;
	} // end of ChangeBasis<2u>::exe
      }; // end of ChangeBasis<2u>
      /*!
       * \brief partial specialisation in 3D
       */
      template<>
      struct ChangeBasis<3u>{
	/*!
	 * \return the st2tost2 that has the same effect as applying
	 * the rotation
	 * \param[in] r : rotation matrix
	 */
	template<typename ST2toST2Type>
	static TFEL_MATH_INLINE2
	typename std::enable_if<(tfel::meta::Implements<ST2toST2Type,tfel::math::ST2toST2Concept>::cond&&
				 tfel::math::ST2toST2Traits<ST2toST2Type>::dime==3u),
				tfel::math::st2tost2<3u,typename tfel::math::ST2toST2Traits<ST2toST2Type>::NumType>
				>::type
	exe(const ST2toST2Type& s,
	    const tfel::math::tmatrix<3,3,typename tfel::typetraits::BaseType<typename tfel::math::ST2toST2Traits<ST2toST2Type>::NumType>::type>& r)
	{
	  using st2tost2 = tfel::math::st2tost2<3u,typename tfel::math::ST2toST2Traits<ST2toST2Type>::NumType>;
	  const auto sr  = st2tost2::fromRotationMatrix(r);
	  const auto sir = st2tost2::fromRotationMatrix(transpose(r));
	  return sr*s*sir;
	} // end of ChangeBasis<3u>::exe
      }; // end of ChangeBasis<2u>
         
    } // end of namespace st2tost2_internals
    
  } // end of namespace math
  
} // end of namespace tfel

#endif /* _LIB_TFEL_MATH_ST2TOST2_CHANGEBASIS_HXX_ */