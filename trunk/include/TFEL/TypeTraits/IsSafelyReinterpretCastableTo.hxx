/*!
 * \file   IsSafelyReinterpretCastableTo.hxx
 * \brief  This file implements the IsSafelyReinterpretCastableTo traits class.
 * \author Helfer Thomas
 * \date   26 Jul 2006
 */

#ifndef _LIB_TFEL_IS_SAFELY_REINTERPRET_CASTABLE_H_
#define _LIB_TFEL_IS_SAFELY_REINTERPRET_CASTABLE_H_ 

namespace tfel{

  namespace typetraits {

    /*!
     * \class IsSafelyReinterpretCastableTo
     * \brief Traits class which says if the expressions:
     *  - reinterpret_cast<B&>(a)
     *  - reinterpret_cast<B*>(p)
     *  - reinterpret_cast<const B&>(a)
     *  - reinterpret_cast<const B* const>(p)
     * shall be considered valid for all object a of type A and for
     * all object of type A*.
     *  
     * \param  A, first type
     * \param  B, second type
     * \return bool cond, true if the above expressions are valid,
     * false otherwise.
     *
     * \author Helfer Thomas
     * \date   28 jun 2006     
     */ 
    template<typename A,typename B>
    struct IsSafelyReinterpretCastableTo;

    /*!
     * Partial specialisation if the two types in argument are valid
     */
    template<typename T>
    struct IsSafelyReinterpretCastableTo<T,T>
    {
      /*!
       *  Result
       */
      static const bool cond = true; 
    }; // end of struct IsSafelyReinterpretCastableTo

  } //end of namespace typetraits

} // end of namespace tfel

#endif /* _LIB_TFEL_IS_SAFELY_REINTERPRET_CASTABLE_H */
