/*!
 * \file   IsScalar.hxx
 * \brief  This file declares the IsScalar traits class
 * and specialises it for standard numeric types.
 * \author Helfer Thomas
 * \date   07 Jun 2006
 */

#ifndef _LIB_TFEL_ISSCALAR_H_
#define _LIB_TFEL_ISSCALAR_H_ 

#include"TFEL/Math/General/Complex.hxx"

/*!
 * \def    TFEL_META_IS_SCALAR
 * \brief An helper macro to specialise IsScalar for each standard
 * "real" numeric types.
 *
 * \author Helfer Thomas
 * \date   28 jun 2006 
 */
#define TFEL_META_IS_SCALAR(X)             \
    /*!                                    \
     * \brief Partial specialisation for X \
     * \see   IsScalar                     \
     */                                    \
    template<>                             \
    struct IsScalar< X >{                  \
      /*!				   \
       *  Result			   \
       */				   \
      static const bool cond = true;       \
    };                                     \
    /*!                                    \
     * \brief Partial specialisation for X \
     * \see   IsScalar                     \
     */                                    \
    template<>                             \
    struct IsScalar<const X >{             \
      /*!				   \
       *  Result			   \
       */				   \
      static const bool cond = true;       \
    }                                 

namespace tfel{

  namespace typetraits{

    /*!
     * \brief  Traits class which says if its argument stands for a scalar
     *
     * \param  T, type to be tested.
     * \return bool cond, true if T stands for a scalar, false otherwise.
     *
     * \see IsReal, IsComplex
     *
     * \author Helfer Thomas
     * \date   04 Jul 2006
     */
    template<typename T>
    struct IsScalar{
      /*!
       *  Result
       */
      static const bool cond = false;
    };

    TFEL_META_IS_SCALAR(unsigned short);
    TFEL_META_IS_SCALAR(unsigned int);
    TFEL_META_IS_SCALAR(long unsigned int);
    TFEL_META_IS_SCALAR(short);
    TFEL_META_IS_SCALAR(int);
    TFEL_META_IS_SCALAR(long int);
    TFEL_META_IS_SCALAR(float);
    TFEL_META_IS_SCALAR(double);
    TFEL_META_IS_SCALAR(long double);
    TFEL_META_IS_SCALAR(tfel::math::Complex<unsigned short>);
    TFEL_META_IS_SCALAR(tfel::math::Complex<unsigned int>);
    TFEL_META_IS_SCALAR(tfel::math::Complex<long unsigned int>);
    TFEL_META_IS_SCALAR(tfel::math::Complex<short>);
    TFEL_META_IS_SCALAR(tfel::math::Complex<int>);
    TFEL_META_IS_SCALAR(tfel::math::Complex<long int>);
    TFEL_META_IS_SCALAR(tfel::math::Complex<float>);
    TFEL_META_IS_SCALAR(tfel::math::Complex<double>);
    TFEL_META_IS_SCALAR(tfel::math::Complex<long double>);

  } // end of namespace typetraits

} // end of namespace tfel

#endif /* _LIB_TFEL_ISSCALAR_H */
