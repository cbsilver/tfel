/*!
 * \file   RealPartType.hxx
 * \brief  This file declares the RealPartType traits class
 * and specialises it for standard numeric types.
 * \author Helfer Thomas
 * \date   23 Aug 2006
 */

#ifndef _LIB_TFEL_REALPARTTYPE_H_
#define _LIB_TFEL_REALPARTTYPE_H_ 

#include"TFEL/Metaprogramming/InvalidType.hxx"
#include"TFEL/Math/General/Complex.hxx"

/*!
 * \def    TFEL_TYPETRAITS_REALPARTTYPE
 * \brief An helper macro to specialise RealPartType for each standard
 * "real" numeric types.
 * \author Helfer Thomas
 * \date   23 Aug 2006
 */
#define TFEL_TYPETRAITS_REALPARTTYPE(X)    \
    /*!                                    \
     * \brief Partial specialisation for X \
     * \see   RealPartType                 \
     */                                    \
    template<>                             \
    struct RealPartType<X>		   \
    {			                   \
      typedef X type;			   \
    }

/*!
 * \def    TFEL_TYPETRAITS_REALPARTTYPEII
 * \brief  An helper macro to specialise RealPartType for each
 * standard "real"
 * numeric types.
 * \author Helfer Thomas
 * \date   23 Aug 2006
 */
#define TFEL_TYPETRAITS_REALPARTTYPEII(X)        \
    /*!                                          \
     * \brief Partial specialisation for X       \
     * \see   RealPartType                       \
     */                                          \
    template<>                                   \
    struct RealPartType<tfel::math::Complex<X> > \
    {				                 \
      typedef X type;		                 \
    }


namespace tfel{

  namespace typetraits{

    /*!
     * \brief  Traits class which associates to its argument its real part type.
     *
     * If the argument is not complex, the result is the argument itself. 
     * 
     * \note The name is not well choosen since the result may be an int for  
     *
     * \param  T, type to be tested.
     * \return type, type of the real part of the argument
     *
     * \author Helfer Thomas
     * \date   23 Aug 2006
     */
    template<typename T>
    struct RealPartType
    {
      typedef tfel::meta::InvalidType type;
    }; // end of struct RealPartType

    TFEL_TYPETRAITS_REALPARTTYPE(unsigned short);
    TFEL_TYPETRAITS_REALPARTTYPE(unsigned int);
    TFEL_TYPETRAITS_REALPARTTYPE(long unsigned int);
    TFEL_TYPETRAITS_REALPARTTYPE(short);
    TFEL_TYPETRAITS_REALPARTTYPE(int);
    TFEL_TYPETRAITS_REALPARTTYPE(long int);
    TFEL_TYPETRAITS_REALPARTTYPE(float);
    TFEL_TYPETRAITS_REALPARTTYPE(double);
    TFEL_TYPETRAITS_REALPARTTYPE(long double);

    TFEL_TYPETRAITS_REALPARTTYPEII(unsigned short);
    TFEL_TYPETRAITS_REALPARTTYPEII(unsigned int);
    TFEL_TYPETRAITS_REALPARTTYPEII(long unsigned int);
    TFEL_TYPETRAITS_REALPARTTYPEII(short);
    TFEL_TYPETRAITS_REALPARTTYPEII(int);
    TFEL_TYPETRAITS_REALPARTTYPEII(long int);
    TFEL_TYPETRAITS_REALPARTTYPEII(float);
    TFEL_TYPETRAITS_REALPARTTYPEII(double);
    TFEL_TYPETRAITS_REALPARTTYPEII(long double);

  } // end of namespace typetraits

} // end of namespace tfel

#endif /* _LIB_TFEL_REALPARTTYPE_H */
