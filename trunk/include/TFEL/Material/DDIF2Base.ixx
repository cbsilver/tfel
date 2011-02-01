/*! 
 * \file  DDIF2Base.ixx
 * \brief
 * \author Helfer Thomas
 * \brief 12 mar 2010
 */

#ifndef _LIB_TFEL_MATERIAL_DDIF2BASE_I_
#define _LIB_TFEL_MATERIAL_DDIF2BASE_I_ 

#include<cmath>
#include<algorithm>

namespace tfel
{

  namespace material
  {
    
    template<typename Stensor2Type1,
	     typename Stensor,
	     typename real>
    void
    DDIF2Base::treatFracture(Stensor2Type1& dfe_ddeel,
			     real& dfe_dde,
			     real& fe,
			     const real em_1,
			     const real e,
			     const real de,
			     const Stensor& sig,
			     const Stensor& n,
			     const real sigr,
			     const real Rp,
			     const real young,
			     const real lambda,
			     const real mu,
			     const unsigned short i)
    {
      using namespace std;
      const real em   = max(em_1,e+de); 
      const real sigm = max(sigr+Rp*em,0.); 
      // loading surface
      const real r = (sig(i)-sigm)/young;
      if (((r>DDIF2Base::eps)||(e+de>em_1))&&(e+de>=0.)){
	// damage increase
	fe        = r;
	if(sigr+Rp*em>0.){
	  dfe_dde   = -Rp/young;
	} else {
	  dfe_dde   = 0;
	}
	dfe_ddeel = (lambda*Stensor::Id()+2*mu*n)/young;
      } else {
	// no damage increase
	if(e+de<0){
	    fe      += e;
	} else {
	  if(em>DDIF2Base::emin1){
	    // material previously damage increase
	    if((e+de>DDIF2Base::emin1)||(sig(i)>=0)){
	      const real Ef  = sigm/em;
	      fe             = (sig(i)-Ef*(e+de))/young;
	      dfe_ddeel      = (lambda*Stensor::Id()+2*mu*n)/young;
	      dfe_dde        = -Ef/young;
	    } else {
	      fe      += e;
	    }
	  } else {
	    fe      += e;
	  }
	}
      }  
    } // end of DDIF2Base::treatFacture

    template<typename real>
    void
    DDIF2Base::cart2cyl(tfel::math::stensor<1u,real>&,
			const real)
    {} // end of DDIF2Base::cart2cyl
    
    template<typename real>
    void
    DDIF2Base::cart2cyl(tfel::math::stensor<2u,real>& s,
			const real theta)
    {
      using namespace std;
      const real a[4]  = {s(0),s(1),s(2),s(3)*M_SQRT1_2};
      const real cost  = cos(theta);
      const real sint  = sin(theta);
      const real alpha = cost*a[0]+sint*a[3];
      const real beta  = cost*a[3]+sint*a[1];
      s(0) = cost*alpha+sint*beta;
      s(1) = sint*(sint*a[0]-cost*a[3])+cost*(cost*a[1]-sint*a[3]);
      s(2) = a[2];
      s(3) = (cost*beta-sint*alpha)*M_SQRT2;
    } // end of DDIF2Base::cart2cyl
      
    template<typename real>
    void
    DDIF2Base::cart2cyl(tfel::math::stensor<3u,real>& s,
			const real theta)
    {
      using namespace std;
      const real a[6]  = {s(0),s(1),s(2),s(3)*M_SQRT1_2,
			  s(4)*M_SQRT1_2,s(5)*M_SQRT1_2};
      const real cost  = cos(theta);
      const real sint  = sin(theta);
      const real alpha = cost*a[0]+sint*a[3];
      const real beta  = cost*a[3]+sint*a[1];
      s(0) = cost*alpha+sint*beta;
      s(1) = sint*(sint*a[0]-cost*a[3])+cost*(cost*a[1]-sint*a[3]);
      s(2) = a[2];
      s(3) = (cost*beta-sint*alpha)*M_SQRT2;
      s(4) = (cost*a[4]+sint*a[5])*M_SQRT2;
      s(5) = (cost*a[5]-sint*a[4])*M_SQRT2;
    } // end of DDIF2Base::cart2cyl

    template<typename real>
    void
    DDIF2Base::cyl2cart(tfel::math::stensor<1u,real>&,
			const real)
    {} // end of DDIF2Base::cyl2cart
    
    template<typename real>
    void
    DDIF2Base::cyl2cart(tfel::math::stensor<2u,real>& s,
			const real theta)
    {
      using namespace std;
      const real a[4]  = {s(0),s(1),s(2),s(3)*M_SQRT1_2};
      const real cost  = cos(theta);
      const real sint  = sin(theta);
      const real alpha = cost*a[0]-sint*a[3];
      const real beta  = cost*a[3]-sint*a[1];
      s(0) = cost*alpha-sint*beta;
      s(1) = sint*(sint*a[0]+cost*a[3])+cost*(sint*a[3]+cost*a[1]);
      s(2) = a[2];
      s(3) = (sint*alpha+cost*beta)*M_SQRT2;
    } // end of DDIF2Base::cyl2cart
      
    template<typename real>
    void
    DDIF2Base::cyl2cart(tfel::math::stensor<3u,real>& s,
			const real theta)
    {
      using namespace std;
      using namespace std;
      const real a[6]  = {s(0),s(1),s(2),s(3)*M_SQRT1_2,
			  s(4)*M_SQRT1_2,s(5)*M_SQRT1_2};
      const real cost  = cos(theta);
      const real sint  = sin(theta);
      const real alpha = cost*a[0]-sint*a[3];
      const real beta  = cost*a[3]-sint*a[1];
      s(0) = cost*alpha-sint*beta;
      s(1) = sint*(sint*a[0]+cost*a[3])+cost*(sint*a[3]+cost*a[1]);
      s(2) = a[2];
      s(3) = (sint*alpha+cost*beta)*M_SQRT2;
      s(4) = (cost*a[4]-sint*a[5])*M_SQRT2;
      s(5) = (sint*a[4]+cost*a[5])*M_SQRT2;
    } // end of DDIF2Base::cyl2cart

    template<typename real>
    void
    DDIF2Base::rk(tfel::math::tmatrix<3,3,real>& m,
		  tfel::math::tvector<3,real>& v,
		  real& Hr,
		  const real s,
		  const real dse, // elastic stress estimation
		  const real e,
		  const real X,
		  const real young,
		  const real lambda,
		  const real mu,
		  const unsigned short i,
		  const unsigned short i1,
		  const unsigned short i2)
    {
      using namespace std;
      m(i,i1) = m(i,i2) = 0.;
      m(i,i)  = 1.;
      v(i)    = 0.;
      real r = (s-X);
      if((r>0)&&(e>-DDIF2Base::emin_rk1)){
        if (X<0){
	   Hr=0.;
	}
	m(i,i1) = m(i,i2) = lambda;
	m(i,i)  = lambda+2*mu+Hr;
	v(i)    = dse;
      } 
      if((r<0)&&(e>DDIF2Base::emin_rk1)){
	Hr=0.;
  	real Ef  = s/e;
	m(i,i1) = m(i,i2) = lambda;
	m(i,i)  = lambda+2*mu+Ef;
	v(i)	= dse;
      }
    }

    template<typename real>
    void
    DDIF2Base::invmat(tfel::math::tmatrix<3,3,real>& m,
                      tfel::math::tmatrix<3,3,real>& mi,
		      tfel::math::tvector<3,real>& v)
    {
      using namespace std;
      const real Y = m(0,0)*m(1,1)*m(2,2)+m(0,1)*m(1,2)*m(2,0)
	+m(1,0)*m(2,1)*m(0,2)-m(2,0)*m(1,1)*m(0,2)
	-m(1,0)*m(0,1)*m(2,2)-m(0,0)*m(2,1)*m(1,2); 
      mi(0,0)= (m(1,1)*m(2,2)-m(1,2)*m(2,1))/Y;
      mi(0,1)= -(m(0,1)*m(2,2)-m(0,2)*m(2,1))/Y;
      mi(0,2)= (m(0,1)*m(1,2)-m(0,2)*m(1,1))/Y;
      mi(1,0)= -(m(1,0)*m(2,2)-m(1,2)*m(2,0))/Y;
      mi(1,1)= (m(0,0)*m(2,2)-m(0,2)*m(2,0))/Y;
      mi(1,2)= -(m(0,0)*m(1,2)-m(0,2)*m(1,0))/Y;
      mi(2,0)= (m(1,0)*m(2,1)-m(1,1)*m(2,0))/Y;
      mi(2,1)= -(m(0,0)*m(2,1)-m(0,1)*m(2,0))/Y;
      mi(2,2)= (m(0,0)*m(1,1)-m(0,1)*m(1,0))/Y;
      real v0 = mi(0,0)*v(0)+mi(0,1)*v(1)+mi(0,2)*v(2);
      real v1 = mi(1,0)*v(0)+mi(1,1)*v(1)+mi(1,2)*v(2);
      real v2 = mi(2,0)*v(0)+mi(2,1)*v(1)+mi(2,2)*v(2);
      v(0) = v0;
      v(1) = v1;
      v(2) = v2;
    }
    
  } // end of namespace material
    
} // end of namespace tfel

#endif /* _LIB_TFEL_MATERIAL_DDIF2BASE_I */
