/*!
 * \file   include/TFEL/Math/ST2toST2/st2tost2.ixx
 * \brief  This file implements the methods of the class st2tost2.
 * \author Thomas Helfer
 * \date   02 jun 2006
 * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights
 * reserved.
 * This project is publicly released under either the GNU GPL Licence
 * or the CECILL-A licence. A copy of thoses licences are delivered
 * with the sources of TFEL. CEA or EDF may also distribute this
 * project under specific licensing conditions.
 */

#ifndef LIB_TFEL_ST2TOST2IXX
#define LIB_TFEL_ST2TOST2IXX

#include <cmath>
#include <iterator>
#include <algorithm>
#include <type_traits>

#include "TFEL/FSAlgorithm/FSAlgorithm.hxx"
#include "TFEL/TypeTraits/IsSafelyReinterpretCastableTo.hxx"
#include "TFEL/Math/General/BaseCast.hxx"
#include "TFEL/Math/Vector/VectorUtilities.hxx"
#include "TFEL/Math/Matrix/MatrixUtilities.hxx"
#include "TFEL/Math/tmatrix.hxx"
#include "TFEL/Math/TinyMatrixInvert.hxx"
#include "TFEL/Math/ST2toST2/ConvertT2toST2ToST2toST2Expr.hxx"
#include "TFEL/Math/ST2toST2/BuildFromRotationMatrix.hxx"
#include "TFEL/Math/ST2toST2/StensorSymmetricProductDerivative.hxx"
#include "TFEL/Math/ST2toST2/SymmetricStensorProductDerivative.hxx"
#include "TFEL/Math/ST2toST2/ChangeBasis.hxx"

namespace tfel {

  namespace math {

    // Assignement operator
    template <typename Child>
    template <typename ST2toST2Type>
    typename std::enable_if<
        tfel::meta::Implements<ST2toST2Type, ST2toST2Concept>::cond &&
            ST2toST2Traits<Child>::dime == ST2toST2Traits<ST2toST2Type>::dime &&
            tfel::typetraits::IsAssignableTo<ST2toST2NumType<ST2toST2Type>,
                                             ST2toST2NumType<Child>>::cond,
        Child&>::type
    st2tost2_base<Child>::operator=(const ST2toST2Type& src) {
      auto& child = static_cast<Child&>(*this);
      matrix_utilities<
          StensorDimeToSize<ST2toST2Traits<Child>::dime>::value,
          StensorDimeToSize<ST2toST2Traits<Child>::dime>::value,
          StensorDimeToSize<ST2toST2Traits<Child>::dime>::value>::copy(src,
                                                                       child);
      return child;
    }

    template <typename Child>
    template <typename ST2toST2Type>
    typename std::enable_if<
        tfel::meta::Implements<ST2toST2Type, ST2toST2Concept>::cond &&
            ST2toST2Traits<Child>::dime == ST2toST2Traits<ST2toST2Type>::dime &&
            tfel::typetraits::IsAssignableTo<ST2toST2NumType<ST2toST2Type>,
                                             ST2toST2NumType<Child>>::cond,
        Child&>::type
    st2tost2_base<Child>::operator+=(const ST2toST2Type& src) {
      auto& child = static_cast<Child&>(*this);
      matrix_utilities<StensorDimeToSize<ST2toST2Traits<Child>::dime>::value,
                       StensorDimeToSize<ST2toST2Traits<Child>::dime>::value,
                       StensorDimeToSize<ST2toST2Traits<Child>::dime>::value>::
          plusEqual(child, src);
      return child;
    }

    // Assignement operator
    template <typename Child>
    template <typename ST2toST2Type>
    typename std::enable_if<
        tfel::meta::Implements<ST2toST2Type, ST2toST2Concept>::cond &&
            ST2toST2Traits<Child>::dime == ST2toST2Traits<ST2toST2Type>::dime &&
            tfel::typetraits::IsAssignableTo<ST2toST2NumType<ST2toST2Type>,
                                             ST2toST2NumType<Child>>::cond,
        Child&>::type
    st2tost2_base<Child>::operator-=(const ST2toST2Type& src) {
      auto& child = static_cast<Child&>(*this);
      matrix_utilities<StensorDimeToSize<ST2toST2Traits<Child>::dime>::value,
                       StensorDimeToSize<ST2toST2Traits<Child>::dime>::value,
                       StensorDimeToSize<ST2toST2Traits<Child>::dime>::value>::
          minusEqual(child, src);
      return child;
    }

    // *= operator
    template <typename Child>
    template <typename T2>
    typename std::enable_if<
        tfel::typetraits::IsScalar<T2>::cond &&
            std::is_same<
                typename ResultType<ST2toST2NumType<Child>, T2, OpMult>::type,
                ST2toST2NumType<Child>>::value,
        Child&>::type
    st2tost2_base<Child>::operator*=(const T2 s) {
      auto& child = static_cast<Child&>(*this);
      matrix_utilities<StensorDimeToSize<ST2toST2Traits<Child>::dime>::value,
                       StensorDimeToSize<ST2toST2Traits<Child>::dime>::value,
                       StensorDimeToSize<ST2toST2Traits<Child>::dime>::value>::
          multByScalar(child, s);
      return child;
    }

    // /= operator
    template <typename Child>
    template <typename T2>
    typename std::enable_if<
        tfel::typetraits::IsScalar<T2>::cond &&
            std::is_same<
                typename ResultType<ST2toST2NumType<Child>, T2, OpDiv>::type,
                ST2toST2NumType<Child>>::value,
        Child&>::type
    st2tost2_base<Child>::operator/=(const T2 s) {
      auto& child = static_cast<Child&>(*this);
      matrix_utilities<StensorDimeToSize<ST2toST2Traits<Child>::dime>::value,
                       StensorDimeToSize<ST2toST2Traits<Child>::dime>::value,
                       StensorDimeToSize<ST2toST2Traits<Child>::dime>::value>::
          divByScalar(child, s);
      return child;
    }

    template <unsigned short N, typename T>
    template <typename StensorType>
    typename std::enable_if<
        tfel::meta::Implements<StensorType, StensorConcept>::cond &&
            StensorTraits<StensorType>::dime == N &&
            tfel::typetraits::IsAssignableTo<StensorNumType<StensorType>,
                                             T>::cond,
        Expr<st2tost2<N, T>, StensorSquareDerivativeExpr<N>>>::type
    st2tost2<N, T>::dsquare(const StensorType& s) {
      return Expr<st2tost2<N, T>, StensorSquareDerivativeExpr<N>>(s);
    }

    template <unsigned short N, typename T>
    template <typename StensorType, typename ST2toST2Type>
    typename std::enable_if<
        tfel::meta::Implements<StensorType, StensorConcept>::cond &&
            tfel::meta::Implements<ST2toST2Type, ST2toST2Concept>::cond &&
            StensorTraits<StensorType>::dime == N &&
            ST2toST2Traits<ST2toST2Type>::dime == N &&
            tfel::typetraits::IsAssignableTo<
                typename ComputeBinaryResult<StensorNumType<StensorType>,
                                             ST2toST2NumType<ST2toST2Type>,
                                             OpMult>::Result,
                T>::cond,
        Expr<st2tost2<N, T>, StensorSquareDerivativeExpr<N>>>::type
    st2tost2<N, T>::dsquare(const StensorType& s, const ST2toST2Type& C) {
      return Expr<st2tost2<N, T>, StensorSquareDerivativeExpr<N>>(s, C);
    }

    template <unsigned short N, typename T>
    template <typename StensorType>
    typename std::enable_if<
        tfel::meta::Implements<StensorType, tfel::math::StensorConcept>::cond &&
            StensorTraits<StensorType>::dime == N &&
            tfel::typetraits::IsAssignableTo<StensorNumType<StensorType>,
                                             T>::cond,
        tfel::math::st2tost2<N, T>>::type
    st2tost2<N, T>::stpd(const StensorType& s) {
      return StensorSymmetricProductDerivative<N, T>::exe(s);
    }

    template <unsigned short N, typename T>
    template <typename T2toST2Type>
    typename std::enable_if<
        tfel::meta::Implements<T2toST2Type, T2toST2Concept>::cond &&
            T2toST2Traits<T2toST2Type>::dime == N &&
            tfel::typetraits::IsAssignableTo<
                typename T2toST2Traits<T2toST2Type>::NumType,
                T>::cond,
        Expr<st2tost2<N, T>, ConvertT2toST2ToST2toST2Expr<N>>>::type
    st2tost2<N, T>::convert(const T2toST2Type& src) {
      return Expr<st2tost2<N, T>, ConvertT2toST2ToST2toST2Expr<N>>(src);
    }

    template <unsigned short N, typename T>
    st2tost2<N, tfel::typetraits::base_type<T>>
    st2tost2<N, T>::fromRotationMatrix(const rotation_matrix<T>& r) {
      return st2tost2_internals::BuildFromRotationMatrix<N, T>::exe(r);
    }  // end of st2tost2<N,T>::fromRotationMatrix

    template <unsigned short N, typename T>
    template <
        typename T2,
        typename std::enable_if<tfel::typetraits::IsAssignableTo<T2, T>::cond,
                                bool>::type>
    constexpr st2tost2<N, T>::st2tost2(const T2& init)
        : fsarray<StensorDimeToSize<N>::value * StensorDimeToSize<N>::value, T>(
              init) {}

    template <unsigned short N, typename T>
    template <
        typename T2,
        typename std::enable_if<tfel::typetraits::IsAssignableTo<T2, T>::cond,
                                bool>::type>
    constexpr st2tost2<N, T>::st2tost2(const std::initializer_list<T2>& init)
        : fsarray<StensorDimeToSize<N>::value * StensorDimeToSize<N>::value, T>(
              init) {}

    template <unsigned short N, typename T>
    struct ComputeSpecialST2ST2Values;

    template <typename T>
    struct ComputeSpecialST2ST2Values<1u, T> {
      static TFEL_MATH_INLINE constexpr st2tost2<1u, T> getId() {
        return st2tost2<1u, T>{
            {T{1}, T{0}, T{0}, T{0}, T{1}, T{0}, T{0}, T{0}, T{1}}};
      }  // end of getId()
      static TFEL_MATH_INLINE constexpr st2tost2<1u, T> getIxI() {
        return st2tost2<1u, T>{
            {T{1}, T{1}, T{1}, T{1}, T{1}, T{1}, T{1}, T{1}, T{1}}};
      }  // end of getIxI()
      static TFEL_MATH_INLINE constexpr st2tost2<1u, T> getJ() {
        return st2tost2<1u, T>{{T{1} / T{3}, T{1} / T{3}, T{1} / T{3},
                                T{1} / T{3}, T{1} / T{3}, T{1} / T{3},
                                T{1} / T{3}, T{1} / T{3}, T{1} / T{3}}};
      }  // end of getJ()
      static TFEL_MATH_INLINE constexpr st2tost2<1u, T> getK() {
        return st2tost2<1u, T>{{T{2} / T{3}, -T{1} / T{3}, -T{1} / T{3},
                                -T{1} / T{3}, T{2} / T{3}, -T{1} / T{3},
                                -T{1} / T{3}, -T{1} / T{3}, T{2} / T{3}}};
      }  // end of getK()
      static TFEL_MATH_INLINE constexpr st2tost2<1u, T> getM() {
        return st2tost2<1u, T>{{T{1}, -T{1} / T{2}, -T{1} / T{2}, -T{1} / T{2},
                                T{1}, -T{1} / T{2}, -T{1} / T{2}, -T{1} / T{2},
                                T{1}}};
      }  // end of getM()
    };

    template <typename T>
    struct ComputeSpecialST2ST2Values<2u, T> {
      static TFEL_MATH_INLINE constexpr st2tost2<2u, T> getId() {
        return st2tost2<2u, T>{{T{1}, T{0}, T{0}, T{0}, T{0}, T{1}, T{0}, T{0},
                                T{0}, T{0}, T{1}, T{0}, T{0}, T{0}, T{0},
                                T{1}}};
      }  // end of getId()
      static TFEL_MATH_INLINE constexpr st2tost2<2u, T> getIxI() {
        return st2tost2<2u, T>{{T{1}, T{1}, T{1}, T{0}, T{1}, T{1}, T{1}, T{0},
                                T{1}, T{1}, T{1}, T{0}, T{0}, T{0}, T{0},
                                T{0}}};
      }  // end of getIxI()
      static TFEL_MATH_INLINE constexpr st2tost2<2u, T> getJ() {
        return st2tost2<2u, T>{{T{1} / T{3}, T{1} / T{3}, T{1} / T{3}, T{0},
                                T{1} / T{3}, T{1} / T{3}, T{1} / T{3}, T{0},
                                T{1} / T{3}, T{1} / T{3}, T{1} / T{3}, T{0},
                                T{0}, T{0}, T{0}, T{0}}};
      }  // end of getJ()
      static TFEL_MATH_INLINE constexpr st2tost2<2u, T> getK() {
        return st2tost2<2u, T>{{T{2} / T{3}, -T{1} / T{3}, -T{1} / T{3}, T{0},
                                -T{1} / T{3}, T{2} / T{3}, -T{1} / T{3}, T{0},
                                -T{1} / T{3}, -T{1} / T{3}, T{2} / T{3}, T{0},
                                T{0}, T{0}, T{0}, T{1}}};
      }  // end of getK()
      static TFEL_MATH_INLINE constexpr st2tost2<2u, T> getM() {
        return st2tost2<2u, T>{{T{1}, -T{1} / T{2}, -T{1} / T{2}, T{0},
                                -T{1} / T{2}, T{1}, -T{1} / T{2}, T{0},
                                -T{1} / T{2}, -T{1} / T{2}, T{1}, T{0}, T{0},
                                T{0}, T{0}, T{3} / T{2}}};
      }  // end of getM()
    };

    template <typename T>
    struct ComputeSpecialST2ST2Values<3u, T> {
      static TFEL_MATH_INLINE constexpr st2tost2<3u, T> getId() {
        return st2tost2<3u, T>{{T{1}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{1},
                                T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{1}, T{0},
                                T{0}, T{0}, T{0}, T{0}, T{0}, T{1}, T{0}, T{0},
                                T{0}, T{0}, T{0}, T{0}, T{1}, T{0}, T{0}, T{0},
                                T{0}, T{0}, T{0}, T{1}}};
      }  // end of getId()
      static TFEL_MATH_INLINE constexpr st2tost2<3u, T> getIxI() {
        return st2tost2<3u, T>{{T{1}, T{1}, T{1}, T{0}, T{0}, T{0}, T{1}, T{1},
                                T{1}, T{0}, T{0}, T{0}, T{1}, T{1}, T{1}, T{0},
                                T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0},
                                T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0}, T{0},
                                T{0}, T{0}, T{0}, T{0}}};
      }  // end of getIxI()
      static TFEL_MATH_INLINE constexpr st2tost2<3u, T> getJ() {
        return st2tost2<3u, T>{
            {T{1} / T{3}, T{1} / T{3}, T{1} / T{3}, T{0}, T{0}, T{0},
             T{1} / T{3}, T{1} / T{3}, T{1} / T{3}, T{0}, T{0}, T{0},
             T{1} / T{3}, T{1} / T{3}, T{1} / T{3}, T{0}, T{0}, T{0},
             T{0},        T{0},        T{0},        T{0}, T{0}, T{0},
             T{0},        T{0},        T{0},        T{0}, T{0}, T{0},
             T{0},        T{0},        T{0},        T{0}, T{0}, T{0}}};
      }  // end of getJ()
      static TFEL_MATH_INLINE constexpr st2tost2<3u, T> getK() {
        return st2tost2<3u, T>{
            {T{2} / T{3},  -T{1} / T{3}, -T{1} / T{3}, T{0}, T{0}, T{0},
             -T{1} / T{3}, T{2} / T{3},  -T{1} / T{3}, T{0}, T{0}, T{0},
             -T{1} / T{3}, -T{1} / T{3}, T{2} / T{3},  T{0}, T{0}, T{0},
             T{0},         T{0},         T{0},         T{1}, T{0}, T{0},
             T{0},         T{0},         T{0},         T{0}, T{1}, T{0},
             T{0},         T{0},         T{0},         T{0}, T{0}, T{1}}};
      }  // end of getK()
      static TFEL_MATH_INLINE constexpr st2tost2<3u, T> getM() {
        return st2tost2<3u, T>{
            {T{1},       -T{1} / T{2}, -T{1} / T{2}, T{0},         T{0},
             T{0},       -T{1} / T{2}, T{1},         -T{1} / T{2}, T{0},
             T{0},       T{0},         -T{1} / T{2}, -T{1} / T{2}, T{1},
             T{0},       T{0},         T{0},         T{0},         T{0},
             T{0},       T{3} / T{2},  T{0},         T{0},         T{0},
             T{0},       T{0},         T{0},         T{3} / T{2},  T{0},
             T{0},       T{0},         T{0},         T{0},         T{0},
             T{3} / T{2}}};
      }  // end of getM()
    };

    template <unsigned short N, typename T>
    constexpr st2tost2<N, T> st2tost2<N, T>::Id() {
      return ComputeSpecialST2ST2Values<N, T>::getId();
    }  // end of st2tost2<N,T>::Id

    template <unsigned short N, typename T>
    constexpr st2tost2<N, T> st2tost2<N, T>::IxI() {
      return ComputeSpecialST2ST2Values<N, T>::getIxI();
    }  // end of st2tost2<N,T>::Id

    template <unsigned short N, typename T>
    constexpr st2tost2<N, T> st2tost2<N, T>::K() {
      return ComputeSpecialST2ST2Values<N, T>::getK();
    }  // end of st2tost2<N,T>::K

    template <unsigned short N, typename T>
    constexpr st2tost2<N, T> st2tost2<N, T>::M() {
      return ComputeSpecialST2ST2Values<N, T>::getM();
    }  // end of st2tost2<N,T>::M

    template <unsigned short N, typename T>
    constexpr st2tost2<N, T> st2tost2<N, T>::J() {
      return ComputeSpecialST2ST2Values<N, T>::getJ();
    }  // end of st2tost2<N,T>::J

    template <unsigned short N, typename T>
    template <typename T2, typename Op>
    st2tost2<N, T>::st2tost2(const Expr<st2tost2<N, T2>, Op>& src) {
      matrix_utilities<StensorDimeToSize<N>::value, StensorDimeToSize<N>::value,
                       StensorDimeToSize<N>::value>::copy(src, *this);
    }

    template <unsigned short N, typename T>
    st2tost2<N, T>::st2tost2(const ParticularSt2toSt2 id) {
      using namespace std;
      unsigned short i, j;
      std::fill(
          this->v,
          this->v + StensorDimeToSize<N>::value * StensorDimeToSize<N>::value,
          T(0));
      if (id == ST2TOST2_IDENTITY) {
        for (i = 0; i != StensorDimeToSize<N>::value; ++i) {
          this->operator()(i, i) = T(1);
        }
      } else if (id == ST2TOST2_J) {
        for (i = 0; i != 3; ++i) {
          for (j = 0; j != 3; ++j) {
            this->operator()(i, j) = 1 / T(3);
          }
        }
      } else if (id == ST2TOST2_IxI) {
        for (i = 0; i != 3; ++i) {
          for (j = 0; j != 3; ++j) {
            this->operator()(i, j) = T(1);
          }
        }
      } else if (id == ST2TOST2_K) {
        for (i = 0; i != 3; ++i) {
          for (j = 0; j != 3; ++j) {
            if (i == j) {
              this->operator()(i, j) = 2 / T(3);
            } else {
              this->operator()(i, j) = -1 / T(3);
            }
          }
        }
        for (i = 3; i != StensorDimeToSize<N>::value; ++i) {
          this->operator()(i, i) = T(1);
        }
      }
    }  // end of st2tost2(const st2tost2<N,T>::ParticularSt2toSt2)

    template <unsigned short N, typename T>
    T& st2tost2<N, T>::operator()(const unsigned short i,
                                  const unsigned short j) {
      return this->v[StensorDimeToSize<N>::value * i + j];
    }

    template <unsigned short N, typename T>
    const T& st2tost2<N, T>::operator()(const unsigned short i,
                                        const unsigned short j) const {
      return this->v[StensorDimeToSize<N>::value * i + j];
    }

    template <unsigned short N, typename T>
    template <typename InputIterator>
    TFEL_MATH_INLINE2 void st2tost2<N, T>::copy(const InputIterator src) {
      tfel::fsalgo::copy<StensorDimeToSize<N>::value *
                         StensorDimeToSize<N>::value>::exe(src, *this);
    }

    template <unsigned short N, typename T>
    typename st2tost2<N, T>::RunTimeProperties
    st2tost2<N, T>::getRunTimeProperties() const {
      return RunTimeProperties();
    }  // end of st2tost2<N,T>::getRunTimeProperties

    template <typename ST2toST2Type>
    TFEL_MATH_INLINE2 typename std::enable_if<
        tfel::meta::Implements<ST2toST2Type, ST2toST2Concept>::cond,
        st2tost2<ST2toST2Traits<ST2toST2Type>::dime,
                 typename ComputeBinaryResult<
                     tfel::typetraits::base_type<ST2toST2NumType<ST2toST2Type>>,
                     ST2toST2NumType<ST2toST2Type>,
                     OpDiv>::Result>>::type
    invert(const ST2toST2Type& s) {
      using tfel::typetraits::BaseType;
      static constexpr unsigned short N = ST2toST2Traits<ST2toST2Type>::dime;
      static constexpr unsigned short StensorSize = StensorDimeToSize<N>::value;
      typedef ST2toST2NumType<ST2toST2Type> NumType;
      typedef typename BaseType<NumType>::type real;
      typedef
          typename ComputeBinaryResult<real, NumType, OpDiv>::Result iNumType;
      st2tost2<N, iNumType> is;
      tmatrix<StensorSize, StensorSize, real> m;
      for (unsigned short i = 0; i != StensorSize; ++i) {
        for (unsigned short j = 0; j != StensorSize; ++j) {
          m(i, j) = base_cast(s(i, j));
        }
      }
      TinyMatrixInvert<StensorSize, real>::exe(m);
      for (unsigned short i = 0; i != StensorSize; ++i) {
        for (unsigned short j = 0; j != StensorSize; ++j) {
          is(i, j) = iNumType(m(i, j));
        }
      }
      return is;
    }  // end of invert

    template <typename ST2toST2Type>
    typename std::enable_if<
        tfel::meta::Implements<ST2toST2Type, ST2toST2Concept>::cond,
        st2tost2<ST2toST2Traits<ST2toST2Type>::dime,
                 ST2toST2NumType<ST2toST2Type>>>::type
    change_basis(
        const ST2toST2Type& s,
        const rotation_matrix<ST2toST2NumType<ST2toST2Type>>& r) {
      return st2tost2_internals::ChangeBasis<
          ST2toST2Traits<ST2toST2Type>::dime>::exe(s, r);
    }

    template <typename ST2toST2Type, typename TensorType>
    typename std::enable_if<
        tfel::meta::Implements<ST2toST2Type, ST2toST2Concept>::cond &&
            tfel::meta::Implements<TensorType, TensorConcept>::cond &&
            ST2toST2Traits<ST2toST2Type>::dime ==
                TensorTraits<TensorType>::dime,
        st2tost2<ST2toST2Traits<ST2toST2Type>::dime,
                 typename ComputeBinaryResult<ST2toST2NumType<ST2toST2Type>,
                                              TensorNumType<TensorType>,
                                              OpMult>::Result>>::type
    push_forward(const ST2toST2Type& C, const TensorType& F) {
      st2tost2<ST2toST2Traits<ST2toST2Type>::dime,
               BinaryOperationResult<ST2toST2NumType<ST2toST2Type>,
                                     TensorNumType<TensorType>, OpMult>>
          r;
      push_forward(r, C, F);
      return r;
    }

    template <typename ST2toST2Type, typename TensorType>
    typename std::enable_if<
        tfel::meta::Implements<ST2toST2Type, ST2toST2Concept>::cond &&
            tfel::meta::Implements<TensorType, TensorConcept>::cond &&
            ST2toST2Traits<ST2toST2Type>::dime ==
                TensorTraits<TensorType>::dime,
        st2tost2<ST2toST2Traits<ST2toST2Type>::dime,
                 typename ComputeBinaryResult<ST2toST2NumType<ST2toST2Type>,
                                              TensorNumType<TensorType>,
                                              OpMult>::Result>>::type
    pull_back(const ST2toST2Type& C, const TensorType& F) {
      const auto iF = invert(F);
      return push_forward(C, iF);
    }

    template <typename StensorType>
    typename std::enable_if<
        tfel::meta::Implements<StensorType, StensorConcept>::cond &&
            StensorTraits<StensorType>::dime == 1u &&
            tfel::typetraits::IsScalar<StensorNumType<StensorType>>::cond,
        st2tost2<1u, StensorNumType<StensorType>>>::type
    computeDeterminantSecondDerivative(const StensorType& s) {
      using NumType = StensorNumType<StensorType>;
      constexpr const auto zero = NumType{0};
      return {zero, s[2], s[1], s[2], zero, s[0], s[1], s[0], zero};
    }  // end of computeDeterminantSecondDerivative

    template <typename StensorType>
    typename std::enable_if<
        tfel::meta::Implements<StensorType, StensorConcept>::cond &&
            StensorTraits<StensorType>::dime == 2u &&
            tfel::typetraits::IsScalar<StensorNumType<StensorType>>::cond,
        st2tost2<2u, StensorNumType<StensorType>>>::type
    computeDeterminantSecondDerivative(const StensorType& s) {
      using NumType = StensorNumType<StensorType>;
      constexpr const auto zero = NumType{0};
      return {zero, s[2], s[1], zero,  s[2], zero, s[0],  zero,
              s[1], s[0], zero, -s[3], zero, zero, -s[3], -s[2]};
    }  // end of computeDeterminantSecondDerivative

    template <typename StensorType>
    typename std::enable_if<
        tfel::meta::Implements<StensorType, StensorConcept>::cond &&
            StensorTraits<StensorType>::dime == 3u &&
            tfel::typetraits::IsScalar<StensorNumType<StensorType>>::cond,
        st2tost2<3u, StensorNumType<StensorType>>>::type
    computeDeterminantSecondDerivative(const StensorType& s) {
      using NumType = StensorNumType<StensorType>;
      constexpr const auto zero = NumType{0};
      constexpr const auto icste = Cste<NumType>::isqrt2;
      return {zero,  s[2],  s[1],  zero,         zero,         -s[5],
              s[2],  zero,  s[0],  zero,         -s[4],        zero,
              s[1],  s[0],  zero,  -s[3],        zero,         zero,
              zero,  zero,  -s[3], -s[2],        s[5] * icste, s[4] * icste,
              zero,  -s[4], zero,  s[5] * icste, -s[1],        s[3] * icste,
              -s[5], zero,  zero,  s[4] * icste, s[3] * icste, -s[0]};
    }  // end of computeDeterminantSecondDerivative

    template <typename StensorType>
    typename std::enable_if<
        tfel::meta::Implements<StensorType, StensorConcept>::cond &&
            StensorTraits<StensorType>::dime == 1u &&
            tfel::typetraits::IsScalar<StensorNumType<StensorType>>::cond,
        st2tost2<1u, StensorNumType<StensorType>>>::type
    computeDeviatorDeterminantSecondDerivative(const StensorType& s) {
      return {-(2 * s[2] + 2 * s[1] - 4 * s[0]) / 9,
              (4 * s[2] - 2 * s[1] - 2 * s[0]) / 9,
              -(2 * s[2] - 4 * s[1] + 2 * s[0]) / 9,
              (4 * s[2] - 2 * s[1] - 2 * s[0]) / 9,
              -(2 * s[2] - 4 * s[1] + 2 * s[0]) / 9,
              -(2 * s[2] + 2 * s[1] - 4 * s[0]) / 9,
              -(2 * s[2] - 4 * s[1] + 2 * s[0]) / 9,
              -(2 * s[2] + 2 * s[1] - 4 * s[0]) / 9,
              (4 * s[2] - 2 * s[1] - 2 * s[0]) / 9};
    }  // end of computeDeviatorDeterminantSecondDerivative

    template <typename StensorType>
    typename std::enable_if<
        tfel::meta::Implements<StensorType, StensorConcept>::cond &&
            StensorTraits<StensorType>::dime == 2u &&
            tfel::typetraits::IsScalar<StensorNumType<StensorType>>::cond,
        st2tost2<2u, StensorNumType<StensorType>>>::type
    computeDeviatorDeterminantSecondDerivative(const StensorType& s) {
      return {-(2 * s[2] + 2 * s[1] - 4 * s[0]) / 9,
              (4 * s[2] - 2 * s[1] - 2 * s[0]) / 9,
              -(2 * s[2] - 4 * s[1] + 2 * s[0]) / 9,
              s[3] / 3,
              (4 * s[2] - 2 * s[1] - 2 * s[0]) / 9,
              -(2 * s[2] - 4 * s[1] + 2 * s[0]) / 9,
              -(2 * s[2] + 2 * s[1] - 4 * s[0]) / 9,
              s[3] / 3,
              -(2 * s[2] - 4 * s[1] + 2 * s[0]) / 9,
              -(2 * s[2] + 2 * s[1] - 4 * s[0]) / 9,
              (4 * s[2] - 2 * s[1] - 2 * s[0]) / 9,
              (-2 * s[3]) / 3,
              s[3] / 3,
              s[3] / 3,
              (-2 * s[3]) / 3,
              -(2 * s[2] - s[1] - s[0]) / 3};
    }  // end of computeDeviatorDeterminantSecondDerivative

    template <typename StensorType>
    typename std::enable_if<
        tfel::meta::Implements<StensorType, StensorConcept>::cond &&
            StensorTraits<StensorType>::dime == 3u &&
            tfel::typetraits::IsScalar<StensorNumType<StensorType>>::cond,
        st2tost2<3u, StensorNumType<StensorType>>>::type
    computeDeviatorDeterminantSecondDerivative(const StensorType& s) {
      using NumType = StensorNumType<StensorType>;
      constexpr const auto icste = Cste<NumType>::isqrt2;
      return {-(2 * s[2] + 2 * s[1] - 4 * s[0]) / 9,
              (4 * s[2] - 2 * s[1] - 2 * s[0]) / 9,
              -(2 * s[2] - 4 * s[1] + 2 * s[0]) / 9,
              s[3] / 3,
              s[4] / 3,
              (-2 * s[5]) / 3,
              (4 * s[2] - 2 * s[1] - 2 * s[0]) / 9,
              -(2 * s[2] - 4 * s[1] + 2 * s[0]) / 9,
              -(2 * s[2] + 2 * s[1] - 4 * s[0]) / 9,
              s[3] / 3,
              (-2 * s[4]) / 3,
              s[5] / 3,
              -(2 * s[2] - 4 * s[1] + 2 * s[0]) / 9,
              -(2 * s[2] + 2 * s[1] - 4 * s[0]) / 9,
              (4 * s[2] - 2 * s[1] - 2 * s[0]) / 9,
              (-2 * s[3]) / 3,
              s[4] / 3,
              s[5] / 3,
              s[3] / 3,
              s[3] / 3,
              (-2 * s[3]) / 3,
              -(2 * s[2] - s[1] - s[0]) / 3,
              s[5] * icste,
              s[4] * icste,
              s[4] / 3,
              (-2 * s[4]) / 3,
              s[4] / 3,
              s[5] * icste,
              (s[2] - 2 * s[1] + s[0]) / 3,
              s[3] * icste,
              (-2 * s[5]) / 3,
              s[5] / 3,
              s[5] / 3,
              s[4] * icste,
              s[3] * icste,
              (s[2] + s[1] - 2 * s[0]) / 3};
    }  // end of computeDeviatorDeterminantSecondDerivative

  }  // end of namespace math

}  // end of namespace tfel

#endif /* LIB_TFEL_ST2TOST2IXX */
