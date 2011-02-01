/*!
 * \file   TypeList.ixx
 * 
 * \brief    
 * \author Helfer Thomas
 * \date   07 Aug 2006
 */

#ifndef _LIB_TFEL_TYPELIST_I_
#define _LIB_TFEL_TYPELIST_I_ 

#include<string>

#include"TFEL/Utilities/Name.hxx"
#include"TFEL/Metaprogramming/IF.hxx"
#include"TFEL/Metaprogramming/StaticAssert.hxx"
#include"TFEL/Metaprogramming/IsSubClassOf.hxx"
#include"TFEL/TypeTraits/IsInvalid.hxx"

namespace tfel{
  
  namespace meta{

    /*!
     * Node of TypeList
     * \param T : current type
     * \param U : next type
     */
    template<typename T, typename U>
    struct TFEL_VISIBILITY_LOCAL TLNode
      : public TL
    {
      TFEL_STATIC_ASSERT((IsSubClassOf<U,TL>::cond));
      /*!
       * Return the Name of the TL beginning with this Node.
       * \param void.
       * \return std::string, the Name of the TL.
       */
      static std::string
      getName(void){
	using namespace std;
	using namespace tfel::utilities;
	return string("TLNode<")
	  +Name<T>::getName()+string(",")
	  +Name<U>::getName()+string(">");
      }
      /*!
       * Current element.
       */
      typedef T Current;
      /*!
       * Next Node.
       */
      typedef U Next;
    };
    
    /*!
     * A special type to represent the end of a typelist
     * \param T : current type
     * \param U : next type
     */
    struct TFEL_VISIBILITY_LOCAL TLE
      : public TL
    {
      /*
       * Return the Name of this class.
       * \param void.
       * \return std::string, the Name.
       */
      static std::string
      getName(void){
	return std::string("TLE");
      }
    };

    namespace internals {

      template<typename List>
      class TFEL_VISIBILITY_LOCAL TLGetNames_
      {
	typedef typename List::Current Current;
	typedef typename List::Next Next;
      public:
	static std::string exe(void)
	{
	  using namespace std;
	  using namespace tfel::utilities;
	  return string(",")+Name<Current>::getName()
	    +tfel::meta::internals::TLGetNames_<Next>::exe();
	}
      };

      template<>
      struct TFEL_VISIBILITY_LOCAL TLGetNames_<TLE>
      {
	static std::string exe(void)
	{
	  return "}";
	}
      };

    } // end of namespace internals

    template<typename List>
    class TFEL_VISIBILITY_LOCAL TLGetNames
    {
      typedef typename List::Current Current;
      typedef typename List::Next Next;
    public:
      static std::string exe(void)
      {
	using namespace std;
	using namespace tfel::utilities;
	return string("{")+Name<Current>::getName()
	  +tfel::meta::internals::TLGetNames_<Next>::exe();
      }
    };

    template<>
    struct TFEL_VISIBILITY_LOCAL TLGetNames<TLE>
    {
      static std::string
      exe(void)
      {
	return "{}";
      }
    };

    template<typename Tlist, template<typename> class Transform>
    struct TFEL_VISIBILITY_LOCAL TLTransform
    {
      TFEL_STATIC_ASSERT((IsSubClassOf<Tlist,TL>::cond));
      typedef TLNode<typename Transform<typename Tlist::Current>::type,
			   typename TLTransform<typename Tlist::Next,Transform>::type> type;
    };
    
    /*!
     * Partial Specialisation to end the recursion.
     * \author Helfer Thomas
     * \date   30 August 2006
     */
    template<template<typename> class Transform>
    struct TFEL_VISIBILITY_LOCAL TLTransform<TLE,Transform>
    {
      typedef TLE type;
    };
    
    template<typename T>
    struct TFEL_VISIBILITY_LOCAL TLSize{
      static const unsigned int value = 1+TLSize<typename T::Next>::value;
    };

    /*!
     * Partial Specialisation to end the recursion.
     * \author Helfer Thomas
     * \date   30 August 2006
     */
    template<>
    struct TFEL_VISIBILITY_LOCAL TLSize<TLE>{
      static const unsigned int value = 0;
    };
    
    /*!
     * Partial Specialisation to end the recursion.
     * \author Helfer Thomas
     * \date   30 August 2006
     */
    template<typename T>
    struct TFEL_VISIBILITY_LOCAL TLCountNbrOfT<T,TLE>
    {
      static const unsigned int value  = 0;
    };
    
    template<typename T, typename U>
    struct TFEL_VISIBILITY_LOCAL TLCountNbrOfT
    {
      static const unsigned int value  = (IsSameType<T,typename U::Current>::cond ? 1 : 0) +  TLCountNbrOfT<T,typename U::Next>::value;
    };

    namespace internals{

      /*!
       * \brief  An helper class for the TLFindEltPos metafunction.
       * \author Helfer Thomas
       * \date   30 August 2006
       */
      template<typename T, typename List>
      struct TFEL_VISIBILITY_LOCAL TLFindEltPos_
      {
	static const unsigned int value = (TLCountNbrOfT<T,typename List::Next>::value==1) ? 1+ TLFindEltPos_<T,typename List::Next>::value : 0u; 
      };
      
      /*!
       * Partial Specialisation to end the recursion.
       * \author Helfer Thomas
       * \date   30 August 2006
       */
      template<typename T>
      struct TFEL_VISIBILITY_LOCAL TLFindEltPos_<T,TLE>
      {
	static const unsigned int value = 0u;
      };
    
    } // end of namespace internals

    template<typename T, typename List>
    struct TFEL_VISIBILITY_LOCAL TLFindEltPos
    {    
      TFEL_STATIC_ASSERT((IsSubClassOf<List,TL>::cond));
      TFEL_STATIC_ASSERT((TLCountNbrOfT<T,List>::value==1));
      /*!
       * The result of the metafunction. 
       */
      static const unsigned int value = tfel::meta::internals::TLFindEltPos_<T,List>::value;
    };

    template<unsigned int N>
    struct TFEL_VISIBILITY_LOCAL TLRemoveNthFirstElt<TLE,N>
    {
      typedef TLE type;
    };

    template<typename List>
    struct TFEL_VISIBILITY_LOCAL TLRemoveNthFirstElt<List,0u>
    {
      TFEL_STATIC_ASSERT((IsSubClassOf<List,TL>::cond));
      typedef List type;
    };

    template<>
    struct TFEL_VISIBILITY_LOCAL TLRemoveNthFirstElt<TLE,0u>
    {
      typedef TLE type;
    };

    template<typename List,unsigned int N>
    struct TFEL_VISIBILITY_LOCAL TLRemoveNthFirstElt
    {
      TFEL_STATIC_ASSERT((IsSubClassOf<List,TL>::cond));
      typedef typename 
      TLRemoveNthFirstElt<typename List::Next,N-1>::type type;
    };

    /*!
     * Partial specialisation of TLFindNthElt to end the recursion
     */
    template<unsigned int N>
    struct TFEL_VISIBILITY_LOCAL TLFindNthElt<TLE,N>{
      /*!
       * The result of the metafunction.
       */
      typedef TLE type;
    };

    /*!
     * Partial specialisation of TLFindNthElt to end the recursion
     */
    template<typename T>
    struct TFEL_VISIBILITY_LOCAL TLFindNthElt<T,0u>{
      TFEL_STATIC_ASSERT((IsSubClassOf<T,TL>::cond));
      /*!
       * The result of the metafunction.
       */
      typedef typename T::Current type;
    };

    /*!
     * Partial specialisation of TLFindNthElt to end the recursion
     */
    template<>
    struct TFEL_VISIBILITY_LOCAL TLFindNthElt<TLE,0u>{
      /*!
       * The result of the metafunction.
       */
      typedef TLE type;
    };
    
    template<typename T,unsigned int N>
    struct TFEL_VISIBILITY_LOCAL TLFindNthElt{
      TFEL_STATIC_ASSERT((IsSubClassOf<T,TL>::cond));
      /*!
       * The result of the metafunction. Return the Nth element of the T or TLE if T contains less than N elements.
       */
      typedef typename TLFindNthElt<typename T::Next,N-1>::type type;
    };
    
    template<typename T,typename U>
    struct TFEL_VISIBILITY_LOCAL TLElementIsUnique {
      /*!
       * The result of the metafunction. True if T is unique in U.
       */
      static const bool cond = TLCountNbrOfT<T,U>::value==1;
    };
    
    namespace internals{

      /*!
       * \brief  An helper class for the TLElementsAreUnique metafunction.
       * \author Helfer Thomas
       * \date   30 August 2006
       */
      template<typename T,typename U>
      struct TFEL_VISIBILITY_LOCAL TLElementsAreUniqueImpl{
	static const bool c1 = tfel::meta::TLElementIsUnique<typename T::Current,U>::cond;
	static const bool c2 = TLElementsAreUniqueImpl<typename T::Next,U>::cond;
	static const bool cond = c1 && c2;
      };
      
      /*!
       * \brief Partial specialisation of TLElementsAreUniqueImpl
       */
      template<typename U>
      struct TFEL_VISIBILITY_LOCAL TLElementsAreUniqueImpl<TLE,U>{
	static const bool cond = true;
      };
      
    } // end of namespace internals

    template<typename T>
    struct TFEL_VISIBILITY_LOCAL TLElementsAreUnique {
      /*!
       * The result of the metafunction. True if all elements in T are unique.
       */
      static const bool cond = tfel::meta::internals::TLElementsAreUniqueImpl<T,T>::cond;
    };

    template<typename List,typename T>
    struct TFEL_VISIBILITY_LOCAL TLPrepend
    {
      TFEL_STATIC_ASSERT((IsSubClassOf<List,TL>::cond));
      /*!
       * The result of the metafunction. 
       */
      typedef TLNode<T,List> type;
    };

    template<typename T>
    struct TFEL_VISIBILITY_LOCAL TLAppend<TLE,T>
    {
      /*!
       * The result of the metafunction. 
       */
      typedef TLNode<T,TLE> type;
    };

    template<typename List,typename T>
    struct TFEL_VISIBILITY_LOCAL TLAppend
    {
      TFEL_STATIC_ASSERT((IsSubClassOf<List,TL>::cond));
      /*!
       * The result of the metafunction. 
       */
      typedef TLNode<typename List::Current,
			   typename TLAppend<typename List::Next,T>::type> type;
    };

    template<typename Second>
    struct TFEL_VISIBILITY_LOCAL TLConcatenate<TLE,Second>
    {
      TFEL_STATIC_ASSERT((IsSubClassOf<Second,TL>::cond));
      /*!
       * The result of the metafunction. 
       */
      typedef Second type;
    };    

    template<typename First,typename Second>
    class TLConcatenate
    {
      typedef typename TLConcatenate<typename First::Next,Second>::type N_;
    public:
      TFEL_STATIC_ASSERT((IsSubClassOf<First,TL>::cond));
      TFEL_STATIC_ASSERT((IsSubClassOf<Second,TL>::cond));
      /*!
       * The result of the metafunction. 
       */
      typedef TLNode<typename First::Current,N_> type;
    };    

    template<typename BaseType>
    struct TFEL_VISIBILITY_LOCAL TLExtractSubClassesOf<TLE,BaseType>
    {
      /*!
       * The result of the metafunction. 
       */
      typedef TLE type;
    };

    template<typename List,typename BaseType>
    struct TFEL_VISIBILITY_LOCAL TLExtractSubClassesOf
    {
      TFEL_STATIC_ASSERT((IsSubClassOf<List,TL>::cond));
      /*!
       * The result of the metafunction. 
       */
      typedef typename IF<IsSubClassOf<typename List::Current,BaseType>::cond,TLNode<typename List::Current,typename TLExtractSubClassesOf<typename List::Next,BaseType>::type>,typename TLExtractSubClassesOf<typename List::Next,BaseType>::type>::type type;
    };

    template<>
    struct TFEL_VISIBILITY_LOCAL TLUnique<TLE>
    {
      /*!
       * The result of the metafunction. 
       */
      typedef TLE type;
    };

    template<typename List>
    class TLUnique
    {
      typedef typename List::Next    Next;
      typedef typename List::Current Current;
      typedef typename TLUnique<Next>::type UniqueNext;
      typedef typename TLPrepend<UniqueNext,Current>::type Choice;
      static const bool unique = TLElementIsUnique<Current,List>::cond;
    public:
      /*!
       * The result of the metafunction. 
       */
      typedef typename IF<unique,Choice,UniqueNext>::type type;
    };

    template<>
    struct TFEL_VISIBILITY_LOCAL TLContainsInvalidType<TLE>
    {
      /*!
       * The result of the metafunction. 
       */
      static const bool cond  = false;
    };
    
    template<typename TList>
    class TLContainsInvalidType
    {
      //! a simple alias.
      typedef typename TList::Current Current;
      //! a simple alias.
      typedef typename TList::Next Next;
      //! check if the current type is invalid.
      static const bool cond1 = tfel::typetraits::IsInvalid<Current>::cond;
      //! check if all the next types in the TypeLis are invalid.
      static const bool cond2 = TLContainsInvalidType<Next>::cond;
    public:
      //! the result.
      static const bool cond  = cond1 || cond2 ;
    };
    
    template<typename List> 
    class TLMaxSize
    {
      //! a simple alias
      typedef typename List::Current Current;
      //! a simple alias
      typedef typename List::Next Next;
      //! the result of the algorithm for the next types of the TL.
      static const size_t nextValue = TLMaxSize<Next>::value;
    public:
      //! the result of the algorithm.
      static const size_t value = sizeof(Current) > nextValue ? sizeof(Current) : nextValue;
    }; // end of struct TLMaxSize
    
    //! Partial specialisation to end the recursion.
    /*
     * \return cons size_t value, the result.
     */
    template<> 
    struct TFEL_VISIBILITY_LOCAL TLMaxSize<TLE>
    {
      //! the result
      static const size_t value =  1;
    }; // end of struct TLMaxSize
    
    template<typename List,size_t size>
    class TLComputeAlignBound
    {
      //! a simple alias
      typedef typename List::Current Current;
      //! a simple alias
      typedef typename List::Next Next;
      //! the result of the algorithm for next types of the TL.
      typedef typename TLComputeAlignBound<Next,size>::type TailResult;
    public:
      //! the result.
      typedef typename IF<(sizeof(Current) <= size),
	TLNode<Current, TailResult>,
	TailResult>::type type;
    };
    
    //! Partial specialisation to end the recursion.
    /*
     * \return type, the result.
     */
    template<size_t size>
    struct TFEL_VISIBILITY_LOCAL TLComputeAlignBound<TLE, size>
    {
      //! the result.
      typedef TLE type;
    };

    namespace internals{

      template<unsigned short N>
      struct TFEL_VISIBILITY_LOCAL IntegerValue
      {
	static const unsigned short value = N;
      }; // end of struct IntegerValue
      
      template<unsigned short N,
	       typename T,
	       typename List>
      struct TFEL_VISIBILITY_LOCAL TLPosition
      {
	typedef typename tfel::meta::IF<tfel::meta::IsSameType<T,typename List::Current>::cond,
					IntegerValue<N>,
					TLPosition<N+1,T,typename List::Next> >::type Select;
      static const unsigned short value = Select::value;
      private:
	TFEL_STATIC_ASSERT((IsSubClassOf<List,TL>::cond));
      }; // end of TLPosition

      template<unsigned short N,
	       typename T>
      struct TLPosition<N,T,TLE>
      {
	static const unsigned short value = N;
      }; // end of TLPosition


    } // end of namespace internals

    template<typename T,
	     typename List>
    struct TFEL_VISIBILITY_LOCAL TLPosition
    {
      static const unsigned short value = tfel::meta::internals::TLPosition<0u,T,List>::value;
    private:
      TFEL_STATIC_ASSERT((IsSubClassOf<List,TL>::cond));
    };
    
  } // end of namespace meta

} // end of namespace tfel

#endif /* _LIB_TFEL_TYPELIST_I_ */
