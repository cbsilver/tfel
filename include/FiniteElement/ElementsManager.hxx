/*!
 * \file   ElementsManager.hxx
 * \brief  
 * 
 * \author Helfer Thomas
 * \date   21 mai 2007
 */

#ifndef _LIB_TFEL_ELEMENTSMANAGER_HXX_
#define _LIB_TFEL_ELEMENTSMANAGER_HXX_ 

#include<vector>
#include<list>

#include"Metaprogramming/TypeList.hxx"
#include"Utilities/ContainerRebind.hxx"

namespace tfel{

  namespace fe{

    template<typename ElementsList,
	     typename ContainerRebind = tfel::utilities::VectorRebind>
    struct ElementsManager;

  } // end of namespace fe  

} // end of namespace tfel  

#include"FiniteElement/Element/ElementsManager.ixx"

#endif /* _LIB_TFEL_ELEMENTSMANAGER_HXX */

