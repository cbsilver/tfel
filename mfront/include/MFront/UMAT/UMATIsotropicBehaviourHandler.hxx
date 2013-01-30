/*! 
 * \file  UMATIsotropicBehaviourHandler.hxx
 * \brief
 * \author Helfer Thomas
 * \brief 30 janv. 2013
 */

#ifndef _LIB_MFRONT_UMAT_UMATISOTROPICBEHAVIOURHANDLER_H_
#define _LIB_MFRONT_UMAT_UMATISOTROPICBEHAVIOURHANDLER_H_ 

#ifndef _LIB_MFRONT_UMAT_UMATBEHAVIOURHANDLER_H_
#error "This header shall not be called directly"
#endif

namespace umat
{

  template<unsigned short N,
	   template<unsigned short,typename,bool> class Behaviour>
  struct TFEL_VISIBILITY_LOCAL UMATIsotropicBehaviourHandler
    : public UMATBehaviourHandler<N,Behaviour>
  {
    TFEL_UMAT_INLINE static
      void exe(const UMATReal *const DTIME ,
	       const UMATReal *const,
	       const UMATReal *const DDSOE,
	       const UMATReal *const STRAN ,
	       const UMATReal *const DSTRAN,
	       const UMATReal *const TEMP  ,
	       const UMATReal *const DTEMP,
	       const UMATReal *const PROPS ,
	       const UMATInt  *const NPROPS,
	       const UMATReal *const PREDEF,
	       const UMATReal *const DPRED,
	       UMATReal *const STATEV,
	       const UMATInt  *const NSTATV,
	       UMATReal *const STRESS,
	       const UMATInt  *const NDI) 
    {
      using namespace tfel::meta;
      using namespace tfel::material;
      typedef MechanicalBehaviourTraits<Behaviour<N,UMATReal,false> > MTraits;
      typedef UMATTraits<Behaviour<N,UMATReal,false> > Traits;
      typedef UMATBehaviourHandler<N,Behaviour> UMATBehaviourHandler;
      const bool is_defined_ = MTraits::is_defined;
      const bool bs = Traits::requiresStiffnessTensor;
      const bool ba = Traits::requiresThermalExpansionTensor;
      typedef typename IF<
	is_defined_,
	typename IF<
	  Traits::useTimeSubStepping,
	  typename UMATBehaviourHandler::template IntegratorWithTimeStepping<bs,ba>,
	  typename UMATBehaviourHandler::template Integrator<bs,ba>
	  >::type,
	typename UMATBehaviourHandler::Error>::type Handler;
      UMATBehaviourHandler::checkNPROPS(*NPROPS);
      UMATBehaviourHandler::checkNSTATV(*NSTATV);
      Handler handler(DTIME,DDSOE,STRAN,
		      DSTRAN,TEMP,DTEMP,PROPS,
		      PREDEF,DPRED,STATEV,STRESS,
		      NDI);
      handler.exe(STRESS,STATEV);
    } // end of UMATIsotropicBehaviourHandler::exe

  }; // end of struct UMATIsotropicBehaviourHandler

}

#endif /* _LIB_MFRONT_UMAT_UMATISOTROPICBEHAVIOURHANDLER_H */

