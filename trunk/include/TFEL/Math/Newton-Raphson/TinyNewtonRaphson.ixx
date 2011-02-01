/*!
 * \file   TinyNewtonRaphson.ixx
 * \brief  This file implements the TinyNewtonMatrix
 * \author Helfer Thomas
 * \date   09 Aug 2006
 */

#ifndef _LIB_TFEL_TINYNEWTONRAPHSON_I_
#define _LIB_TFEL_TINYNEWTONRAPHSON_I_ 

#include<cmath>
#include<limits>

namespace tfel{

  namespace math{

    /*!
     * \class TinyNewtonRaphson
     * \brief Implements the Newton-Raphson algorithm when the size N of the problem is 
     * known at compile-time.
     * One wish to solve the problem:
     * \f[\vec{f}\left(\vec{x}\right)=\vec{0}\f]
     * where \f$\displaystyle\vec{f}:R^{N}\rightarrow R^{N}\f$. 
     * if \f$\displaystyle\vec{x}^{n}\f$ is an estimation of the solution, 
     * \f$\displaystyle\vec{x}^{n+1}\f$ will be given by:
     * \f[\displaystyle\vec{x}^{n+1}=\vec{x}^{n}-J^{-1}\vec{f}\left(\vec{x}^{n}\right)\f]
     * where \f$ J \f$ is the jacobien matrix of \f$ f \f$ at 
     * \f$\left(\displaystyle\vec{x}^{n}\right)\f$ defined by 
     * \f$ J_{ij} = \displaystyle\frac{\displaystyle\partial f_{i}}{\displaystyle\partial x_{j}}\f$
     * \param unsigned short N, dimension of the problem.
     * \param typename T, numerical type.
     * \param typename F, class to which the newton raphson is applied.
     * \pre   F must have a computeFdF method.
     */
    template<unsigned short N,typename T,typename F >
    class TinyNewtonRaphson
    {

      T epsilon;
      unsigned short iter_max;
      unsigned short iter;
      bool convergence;

      TinyNewtonRaphson(const TinyNewtonRaphson&);
      TinyNewtonRaphson& operator=(const TinyNewtonRaphson&);

    protected:
      /*
       * Jacobian matrix
       */
      tmatrix<N,N,T> J;
      /*
       * Residual vector
       */
      tvector<N,T> f;
      /*
       * 
       */
      tvector<N,T> x;

    public:

      static const std::string getName(void)
      {
	return std::string("TinyNewtonRaphson<")+tfel::utilities::ToString(N)+std::string(",")+tfel::utilities::Name<F>::getName()+std::string(">");
      }
      
      TinyNewtonRaphson()
	: convergence(false)
      {}

      void setInitialGuess(const T* const init)
      {
	tfel::fsalgo::copy<N>::exe(init,x.begin());
      }
      
      void setInitialGuess(const tvector<N,T>& init)
      {
	x = init;
      }
      
      void setPrecision(const T e)
      {
	this->epsilon = e;
      }

      void setMaximumIteration(const unsigned short n)
      {
	this->iter_max = n;
      }

      void exe(void)
      {
	iter = 0;	
	while((iter<iter_max) && (convergence==false)){
	  static_cast<F&>(*this).computeFdF();
	  if(norm(f)<=epsilon){
	    convergence = true;
	  } else {
	    TinyMatrixSolve<N,T>::exe(J,f);
	    x-=f;
	    ++(iter);
	  }
	  if(iter==iter_max){
	    throw(MathDivergenceException("Maximum number of iterations reached"));
	  }
	}
      }
      
      tvector<N,T> getX(void) const
      {
	return this->x;
      }

      unsigned short getIter(void) const
      {
	return this->iter;
      }

    };

    /*
     * \brief Partial Specialisation in 1D
     * \param typename T, numerical type
     * \param typename F, class to which the newton raphson is applied.
     * \pre   F must have a computeFdF method.
     */
    template<typename T,typename F>
    class TinyNewtonRaphson<1u,T,F>
    {

      unsigned short iter_max;
      unsigned short iter;
      bool convergence;

      TinyNewtonRaphson(const TinyNewtonRaphson&);
      TinyNewtonRaphson& operator=(const TinyNewtonRaphson&);

    protected:

      T J;
      T f;
      T x;
      T epsilon;

    public:

      static const std::string getName(void)
      {
	using namespace std;
	using namespace tfel::utilities;
	return string("TinyNewtonRaphson<1u")+string(",")
	  +Name<F>::getName()+string(">");
      }
      
      TinyNewtonRaphson()
	: convergence(false)
      {}

      void setInitialGuess(const T init)
      {
	this->x=init;
      }
      
      void setPrecision(const T e)
      {
	this->epsilon = e;
      }

      void setMaximumIteration(const unsigned short n)
      {
	this->iter_max = n;
      }

      void exe(void)
      {
	iter = 0;	
	while((iter<iter_max) && (convergence==false)){
	  static_cast<F&>(*this).computeFdF();
	  if(std::abs(f)<=epsilon){
	    convergence = true;
	  } else {
	    if(std::abs(J)<100*std::numeric_limits<T>::min()){
	      throw(MathDivergenceException("Derivative is too small"));
	    }
	    f/=J;
	    x-=f;
	    ++(iter);
	  }
	  if(iter==iter_max){
	    throw(MathDivergenceException("Maximum number of iterations reached"));
	  }
	}
      }

      T getX(void) const
      {
	return this->x;
      }

      unsigned short getIter(void) const
      {
	return this->iter;
      }
    
    };


  } // end of namespace math

} // end of namespace tfel

#endif /* _LIB_TFEL_TINYNEWTONRAPHSON_I_ */
