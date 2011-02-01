/*!
 * \file   IsFundamentalNumericType.hxx
 * \brief  This file declares the IsFundamentalNumericType traits
 * class and specialises it for standard numerical types.
 * \author Helfer Thomas
 * \date   05 jui 2006
 */

#ifndef _LIB_TFEL_ISFUNDAMENTALNUMERICTYPE_HXX_
#define _LIB_TFEL_ISFUNDAMENTALNUMERICTYPE_HXX_ 

#include"TFEL/Math/General/Complex.hxx"

/*!
 * \def    TFEL_META_IS_FUNDAMENTAL_NUMERIC_TYPE
 * \brief An helper macro to specialise IsFundamentalNumericType for
 * each standard numeric types.
 * \author Helfer Thomas
 * \date   28 jun 2006 
 */
#define TFEL_META_IS_FUNDAMENTAL_NUMERIC_TYPE(X)         \
    /*!                                                  \
     * \brief Partial specialisation for X               \
     * \see   IsFundamentalNumericType                   \
     */                                                  \
    template<>                                           \
    struct IsFundamentalNumericType< X >{                \
      /*!						 \
       *  Result					 \
       */						 \
      static const bool cond = true;                     \
    };                                                   \
    /*!                                                  \
     * \brief Partial specialisation for X               \
     * \see   IsFundamentalNumericType                   \
     */                                                  \
    template<>                                           \
    struct IsFundamentalNumericType<const X >{           \
      /*!						 \
       *  Result					 \
       */						 \
      static const bool cond = true;                     \
    }                                 


namespace tfel{

  namespace typetraits{

    /*!
     * \brief Traits class which says if its argument is one of the
     * standard numerical types
     *
     * \param  T, type to be tested.
     * \return bool cond, true if T is one of the standard numerical
     * types, false otherwise.
     *
     * \see IsReal, IsComplex
     *
     * \author Helfer Thomas
     * \date   04 Jul 2006
     */
    template<typename T>
    struct IsFundamentalNumericType{
      /*!
       *  Result
       */
      static const bool cond = false;
    };

    TFEL_META_IS_FUNDAMENTAL_NUMERIC_TYPE(unsigned short);
    TFEL_META_IS_FUNDAMENTAL_NUMERIC_TYPE(unsigned int);
    TFEL_META_IS_FUNDAMENTAL_NUMERIC_TYPE(long unsigned int);
    TFEL_META_IS_FUNDAMENTAL_NUMERIC_TYPE(short);
    TFEL_META_IS_FUNDAMENTAL_NUMERIC_TYPE(int);
    TFEL_META_IS_FUNDAMENTAL_NUMERIC_TYPE(long int);
    TFEL_META_IS_FUNDAMENTAL_NUMERIC_TYPE(float);
    TFEL_META_IS_FUNDAMENTAL_NUMERIC_TYPE(double);
    TFEL_META_IS_FUNDAMENTAL_NUMERIC_TYPE(long double);
    TFEL_META_IS_FUNDAMENTAL_NUMERIC_TYPE(tfel::math::Complex<unsigned short>);
    TFEL_META_IS_FUNDAMENTAL_NUMERIC_TYPE(tfel::math::Complex<unsigned int>);
    TFEL_META_IS_FUNDAMENTAL_NUMERIC_TYPE(tfel::math::Complex<long unsigned int>);
    TFEL_META_IS_FUNDAMENTAL_NUMERIC_TYPE(tfel::math::Complex<short>);
    TFEL_META_IS_FUNDAMENTAL_NUMERIC_TYPE(tfel::math::Complex<int>);
    TFEL_META_IS_FUNDAMENTAL_NUMERIC_TYPE(tfel::math::Complex<long int>);
    TFEL_META_IS_FUNDAMENTAL_NUMERIC_TYPE(tfel::math::Complex<float>);
    TFEL_META_IS_FUNDAMENTAL_NUMERIC_TYPE(tfel::math::Complex<double>);
    TFEL_META_IS_FUNDAMENTAL_NUMERIC_TYPE(tfel::math::Complex<long double>);

  } // end of namespace typetraits

} // end of namespace tfel
  
#endif /* _LIB_TFEL_ISFUNDAMENTALNUMERICTYPE_HXX */
