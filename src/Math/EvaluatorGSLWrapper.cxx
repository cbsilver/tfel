/*!
 * \file   Evaluator.cxx
 * \brief  
 * 
 * \author Helfer Thomas
 * \date   12 jan 2009
 */

#include<sstream>
#include<gsl/gsl_errno.h>
#include<gsl/gsl_sf.h>

#include"TFEL/Math/Parser/Function.hxx"
#include"TFEL/Math/Parser/EvaluatorProxy.hxx"
#include"TFEL/Math/Evaluator.hxx"
#include"TFEL/Math/Parser/EvaluatorFunction.hxx"
#include"TFEL/Math/Parser/EvaluatorGSLWrapper.hxx"

#define TFEL_MATH_PARSER_REGISTERGSLFUNCTION(X)				\
  Evaluator::getFunctionGeneratorManager().insert(#X,&EvaluatorFunctionNVGenerator<1,X>)
#define TFEL_MATH_PARSER_REGISTERGSLWRAPPERFUNCTION(X)			\
  Evaluator::getFunctionGeneratorManager().insert(#X,&EvaluatorFunctionNVGenerator<1,gsl_wrapper<X> >)
#define TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(X)			\
  Evaluator::getFunctionGeneratorManager().insert(#X,&EvaluatorFunctionNVGenerator<2,X>)
#define TFEL_MATH_PARSER_REGISTERGSLFUNCTIONNV(X,Y)		        \
  Evaluator::getFunctionGeneratorManager().insert(#Y,&EvaluatorFunctionNVGenerator<X,Y>)
#define TFEL_MATH_PARSER_REGISTERGSLWRAPPERFUNCTION2V(X)		\
  Evaluator::getFunctionGeneratorManager().insert(#X,&EvaluatorFunctionNVGenerator<2,gsl_wrapper2<X> >)
#define TFEL_MATH_PARSER_REGISTERGSLWRAPPERFUNCTION3V(X)		\
  Evaluator::getFunctionGeneratorManager().insert(#X,&EvaluatorFunctionNVGenerator<3,gsl_wrapper3<X> >)
#define TFEL_MATH_PARSER_REGISTERGSLWRAPPERFUNCTION4V(X)		\
  Evaluator::getFunctionGeneratorManager().insert(#X,&EvaluatorFunctionNVGenerator<4,gsl_wrapper4<X> >)
#define TFEL_MATH_PARSER_REGISTERGSLFUNCTION1P1V(X)			\
	Evaluator::getFunctionGeneratorManager().insert(#X,&EvaluatorFunction1P1VGenerator<X>)
#define TFEL_MATH_PARSER_REGISTERGSLFUNCTION1P2V(X)			\
	Evaluator::getFunctionGeneratorManager().insert(#X,&EvaluatorFunction1P2VGenerator<X>)
#define TFEL_MATH_PARSER_REGISTERGSLFUNCTION1PNV(X,Y)			\
  Evaluator::getFunctionGeneratorManager().insert(#Y,&EvaluatorFunction1PNVGenerator<X,Y>)
#define TFEL_MATH_PARSER_REGISTERGSLFUNCTION1UPNV(X,Y)			\
  Evaluator::getFunctionGeneratorManager().insert(#Y,&EvaluatorFunction1UPNVGenerator<X,Y>)
#define TFEL_MATH_PARSER_REGISTERGSLFUNCTION2P1V(X)			\
	Evaluator::getFunctionGeneratorManager().insert(#X,&EvaluatorFunction2P1VGenerator<X>)
#define TFEL_MATH_PARSER_REGISTERGSLFUNCTION2P2V(X)			\
	Evaluator::getFunctionGeneratorManager().insert(#X,&EvaluatorFunction2P2VGenerator<X>)
#define TFEL_MATH_PARSER_REGISTERGSLFUNCTION2PNV(X,Y)			\
  Evaluator::getFunctionGeneratorManager().insert(#Y,&EvaluatorFunction2PNVGenerator<X,Y>)
#define TFEL_MATH_PARSER_REGISTERGSLFUNCTION2UPNV(X,Y)			\
  Evaluator::getFunctionGeneratorManager().insert(#Y,&EvaluatorFunction2UPNVGenerator<X,Y>)

namespace tfel
{

  namespace math
  {

    namespace parser
    {

      GSLException::GSLException(const std::string& e)
	: std::runtime_error(e)
      {} // end of GSLException::GSLException

      gsl_mode_t&
      getGSLMode(void)
      {
	static gsl_mode_t mode(GSL_PREC_DOUBLE);
	return mode;
      } // end of getGSLMode

      void
      gslErrorHandler(const char * reason, const char * file,
		      int line, int gsl_errno)
      {
	using namespace std;
	ostringstream msg;
	msg << "gslErrorHandler : " << reason << " ('"
	    << gsl_strerror(gsl_errno)
	    << "' from file '" << file << "'"
	    << " at line " << line << ")";
	throw(GSLException(msg.str()));
      } // end of gslErrorHandler
      
      void
      registerGSLFunctions(void){
	TFEL_MATH_PARSER_REGISTERGSLWRAPPERFUNCTION(gsl_sf_airy_Ai);
	TFEL_MATH_PARSER_REGISTERGSLWRAPPERFUNCTION(gsl_sf_airy_Bi);
	TFEL_MATH_PARSER_REGISTERGSLWRAPPERFUNCTION(gsl_sf_airy_Ai_scaled);
	TFEL_MATH_PARSER_REGISTERGSLWRAPPERFUNCTION(gsl_sf_airy_Bi_scaled);
	TFEL_MATH_PARSER_REGISTERGSLWRAPPERFUNCTION(gsl_sf_airy_Ai_deriv);
	TFEL_MATH_PARSER_REGISTERGSLWRAPPERFUNCTION(gsl_sf_airy_Bi_deriv);
	TFEL_MATH_PARSER_REGISTERGSLWRAPPERFUNCTION(gsl_sf_airy_Ai_deriv_scaled);
	TFEL_MATH_PARSER_REGISTERGSLWRAPPERFUNCTION(gsl_sf_airy_Bi_deriv_scaled);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1UPNV(0,gsl_sf_airy_zero_Ai);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1UPNV(0,gsl_sf_airy_zero_Bi);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1UPNV(0,gsl_sf_airy_zero_Ai_deriv);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1UPNV(0,gsl_sf_airy_zero_Bi_deriv);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_bessel_J0);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_bessel_J1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1P1V(gsl_sf_bessel_Jn);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_bessel_Y0);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_bessel_Y1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1P1V(gsl_sf_bessel_Yn);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_bessel_I0);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_bessel_I1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1P1V(gsl_sf_bessel_In);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_bessel_I0_scaled);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_bessel_I1_scaled);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1P1V(gsl_sf_bessel_In_scaled);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_bessel_K0);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_bessel_K1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1P1V(gsl_sf_bessel_Kn);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_bessel_K0_scaled);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_bessel_K1_scaled);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1P1V(gsl_sf_bessel_Kn_scaled);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_bessel_j0);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_bessel_j1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_bessel_j2);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1P1V(gsl_sf_bessel_jl);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_bessel_y0);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_bessel_y1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_bessel_y2);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1P1V(gsl_sf_bessel_yl);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_bessel_i0_scaled);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_bessel_i1_scaled);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_bessel_i2_scaled);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1P1V(gsl_sf_bessel_il_scaled);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_bessel_k0_scaled);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_bessel_k1_scaled);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_bessel_k2_scaled);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1P1V(gsl_sf_bessel_kl_scaled);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_bessel_Jnu);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_bessel_Ynu);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_bessel_Inu);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_bessel_Inu_scaled);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_bessel_Knu);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_bessel_lnKnu);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_bessel_Knu_scaled);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1UPNV(0,gsl_sf_bessel_zero_J0);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1UPNV(0,gsl_sf_bessel_zero_J1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_clausen);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_hydrogenicR_1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2P2V(gsl_sf_hydrogenicR);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_dawson);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_debye_1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_debye_2);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_debye_3);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_debye_4);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_debye_5);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_debye_6);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_dilog);
	TFEL_MATH_PARSER_REGISTERGSLWRAPPERFUNCTION(gsl_sf_ellint_Kcomp);
	TFEL_MATH_PARSER_REGISTERGSLWRAPPERFUNCTION(gsl_sf_ellint_Ecomp);
	TFEL_MATH_PARSER_REGISTERGSLWRAPPERFUNCTION2V(gsl_sf_ellint_F);
	TFEL_MATH_PARSER_REGISTERGSLWRAPPERFUNCTION2V(gsl_sf_ellint_E);
	TFEL_MATH_PARSER_REGISTERGSLWRAPPERFUNCTION3V(gsl_sf_ellint_P);
	TFEL_MATH_PARSER_REGISTERGSLWRAPPERFUNCTION3V(gsl_sf_ellint_D);
	TFEL_MATH_PARSER_REGISTERGSLWRAPPERFUNCTION2V(gsl_sf_ellint_RC);
	TFEL_MATH_PARSER_REGISTERGSLWRAPPERFUNCTION3V(gsl_sf_ellint_RD);
	TFEL_MATH_PARSER_REGISTERGSLWRAPPERFUNCTION3V(gsl_sf_ellint_RF);
	TFEL_MATH_PARSER_REGISTERGSLWRAPPERFUNCTION4V(gsl_sf_ellint_RJ);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_erf);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_erfc);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_log_erfc);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_erf_Z);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_erf_Q);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_hazard);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_exp);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_exp_mult);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_expm1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_exprel);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_exprel_2);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1P1V(gsl_sf_exprel_n);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_expint_E1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_expint_E2);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_expint_Ei);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_Shi);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_Chi);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_expint_3);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_Si);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_Ci);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_atanint);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_fermi_dirac_m1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_fermi_dirac_0);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_fermi_dirac_1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_fermi_dirac_2);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1P1V(gsl_sf_fermi_dirac_int);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_fermi_dirac_mhalf);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_fermi_dirac_half);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_fermi_dirac_3half);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_fermi_dirac_inc_0);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_gamma);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_lngamma);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_gammastar);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_gammainv);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1UPNV(0,gsl_sf_fact);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1UPNV(0,gsl_sf_doublefact);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1UPNV(0,gsl_sf_lnfact);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1UPNV(0,gsl_sf_lndoublefact);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2UPNV(0,gsl_sf_choose);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2UPNV(0,gsl_sf_lnchoose);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1P1V(gsl_sf_taylorcoeff);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_poch);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_lnpoch);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_pochrel);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_gamma_inc);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_gamma_inc_Q);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_gamma_inc_P);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_beta);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_lnbeta);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTIONNV(3,gsl_sf_beta_inc);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_gegenpoly_1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_gegenpoly_2);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_gegenpoly_3);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1P2V(gsl_sf_gegenpoly_n);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_hyperg_0F1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2P1V(gsl_sf_hyperg_1F1_int);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTIONNV(3,gsl_sf_hyperg_1F1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2P1V(gsl_sf_hyperg_U_int);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTIONNV(3,gsl_sf_hyperg_U);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTIONNV(4,gsl_sf_hyperg_2F1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTIONNV(4,gsl_sf_hyperg_2F1_renorm);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTIONNV(3,gsl_sf_hyperg_2F0);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_laguerre_1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_laguerre_2);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_laguerre_3);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1P2V(gsl_sf_laguerre_n);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_lambert_W0);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_lambert_Wm1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_legendre_P1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_legendre_P2);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_legendre_P3);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1P1V(gsl_sf_legendre_Pl);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_legendre_Q0);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_legendre_Q1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1P1V(gsl_sf_legendre_Ql);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2P1V(gsl_sf_legendre_Plm);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2P1V(gsl_sf_legendre_sphPlm);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_conicalP_half);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_conicalP_mhalf);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_conicalP_0);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_conicalP_1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1P2V(gsl_sf_conicalP_sph_reg);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1P2V(gsl_sf_conicalP_cyl_reg);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_legendre_H3d_0);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_legendre_H3d_1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1P2V(gsl_sf_legendre_H3d);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_log);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_log_abs);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_log_1plusx);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_log_1plusx_mx);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1PNV(0,gsl_sf_psi_int);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_psi);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_psi_1piy);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_psi_1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1PNV(0,gsl_sf_psi_1_int);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1P1V(gsl_sf_psi_n);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_synchrotron_1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_synchrotron_2);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_transport_2);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_transport_3);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_transport_4);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_transport_5);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_sin);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_cos);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_hypot);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_sinc);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_lnsinh);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_lncosh);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_angle_restrict_symm);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_angle_restrict_pos);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1PNV(0,gsl_sf_zeta_int);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_zeta);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1PNV(0,gsl_sf_zetam1_int);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_zetam1);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION2V(gsl_sf_hzeta);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION1PNV(0,gsl_sf_eta_int);
	TFEL_MATH_PARSER_REGISTERGSLFUNCTION(gsl_sf_eta);
      }      

    } // end of namespace parser
    
  } // end of namespace math
  
} // end of namespace tfel

