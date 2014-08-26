/*! 
 * \file  MFrontBehaviourProfiler.cxx
 * \brief
 * \author Helfer Thomas
 * \brief 15 mai 2014
 */

#include<time.h>
#include<string>
#include<iterator>
#include <iomanip>
#include<iostream>
#include<algorithm>
#include<stdexcept>

#include "MFront/MFrontBehaviourProfiler.hxx"

namespace mfront
{

#if !(defined _WIN32 || defined _WIN64 ||defined __CYGWIN__)
  /*!
   * add a new measure
   * t     : measure to which the new measure is added
   * start : start of the measure
   * end   : end of the measure
   */
  static inline void
  add_measure(std::atomic<intmax_t>& t,
	      const timespec& start,
	      const timespec& end)
  {
    /* http://www.guyrutenberg.com/2007/09/22/profiling-code-using-clock_gettime */
    timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
      temp.tv_sec = end.tv_sec-start.tv_sec-1;
      temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
      temp.tv_sec = end.tv_sec-start.tv_sec;
      temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    t += 1000000000*temp.tv_sec+temp.tv_nsec;
  } // end of add_measure
#endif

  /*!
   * print a time to the specified stream
   */
  static void print_time(std::ostream& os,
			 const intmax_t time)
  {
    constexpr intmax_t musec_d = 1000;
    constexpr intmax_t msec_d  = 1000*musec_d;
    constexpr intmax_t sec_d   = msec_d*1000;
    constexpr intmax_t min_d   = sec_d*60;
    constexpr intmax_t hour_d  = min_d*60;
    constexpr intmax_t days_d  = hour_d*24;
    intmax_t t = time;
    const intmax_t ndays  = t/days_d;
    t -= ndays*days_d;
    const intmax_t nhours = t/hour_d;
    t -= nhours*hour_d;
    const intmax_t nmins  = t/min_d;
    t -= nmins*min_d;
    const intmax_t nsecs   = t/sec_d;
    t -= nsecs*sec_d;
    const intmax_t nmsecs   = t/msec_d;
    t -= nmsecs*msec_d;
    const intmax_t nmusecs   = t/musec_d;
    t -= nmusecs*musec_d;
    if(ndays>0){
      os << ndays << "days ";
    }
    if(nhours>0){
      os << nhours << "hours ";
    }
    if(nmins>0){
      os << nmins << "mins ";
    }
    if(nsecs>0){
      os << nsecs << "secs ";
    }
    if(nmsecs>0){
      os << nmsecs << "msecs ";
    }
    if(nmusecs>0){
      os << nmusecs << "musecs ";
    }
    os << t << "nsecs";
  } // end pf print

  static std::string
  getCodeBlockName(const unsigned short c)
  {
    using namespace std;
    string n;
    switch(c){
    case MFrontBehaviourProfiler::FLOWRULE:
      n = "FlowRule";
      break;
    case MFrontBehaviourProfiler::BEFOREINITIALIZELOCALVARIABLES:
      n = "Init::BeforeInitializeLocalVariables";
      break;
    case MFrontBehaviourProfiler::INITIALIZELOCALVARIABLES:
      n = "Init::InitializeLocalVariables";
      break;
    case MFrontBehaviourProfiler::AFTERINITIALIZELOCALVARIABLES:
      n = "Init::AfterInitializeLocalVariables";
      break;
    case MFrontBehaviourProfiler::COMPUTEPREDICTOR:
      n = "Init::ComputePredictor";
      break;
    case MFrontBehaviourProfiler::INITIALIZEJACOBIAN:
      n = "Init::InitializeJacobian";
      break;
    case MFrontBehaviourProfiler::COMPUTEPREDICTIONOPERATOR:
      n = "ComputePredictionOperator";
      break;
    case MFrontBehaviourProfiler::INTEGRATOR:
      n = "Integrator";
      break;
    case MFrontBehaviourProfiler::COMPUTESTRESS:
      n = "Integrator::ComputeStress";
      break;
    case MFrontBehaviourProfiler::COMPUTEDERIVATIVE:
      n = "Integrator::ComputeDerivative";
      break;
    case MFrontBehaviourProfiler::COMPUTEFDF:
      n = "Integrator::ComputeFdF";
      break;
    case MFrontBehaviourProfiler::TINYMATRIXSOLVE:
      n = "Integrator::TinyMatrixSolve";
      break;
    case MFrontBehaviourProfiler::COMPUTEFINALSTRESS:
      n = "ComputeFinalStress";
      break;
    case MFrontBehaviourProfiler::COMPUTETANGENTOPERATOR:
      n = "ComputeTangentOperator";
      break;
    case MFrontBehaviourProfiler::UPDATEAUXILIARYSTATEVARIABLES:
      n = "UpdateAuxiliaryStateVariables";
      break;
    case MFrontBehaviourProfiler::FINITESTRAINPREPROCESSING:
      n = "FiniteStrainPreProcessing";
      break;
    case MFrontBehaviourProfiler::FINITESTRAINPOSTPROCESSING:
      n = "FiniteStrainPostProcessing";
      break;
    case MFrontBehaviourProfiler::USERDEFINEDCODE1:
      n = "UserDefinedCode-1";
      break;
    case MFrontBehaviourProfiler::USERDEFINEDCODE2:
      n = "UserDefinedCode-2";
      break;
    case MFrontBehaviourProfiler::TOTALTIME:
      n = "TotalTime";
      break;
    default:
      string msg("getCodeBlockName : no name associated with the given code block");
      throw(runtime_error(msg));
    }
    return n;
  }
  
  MFrontBehaviourProfiler::Timer::Timer(MFrontBehaviourProfiler& t,
					const unsigned short cn)
    : gtimer(t),
      c(cn)
  {
#if !(defined _WIN32 || defined _WIN64 ||defined __CYGWIN__)
    ::clock_gettime(CLOCK_THREAD_CPUTIME_ID,&(this->start));
#endif
  } // end of MFrontBehaviourProfiler::Timer

  MFrontBehaviourProfiler::Timer::~Timer()
  {
#if !(defined _WIN32 || defined _WIN64 ||defined __CYGWIN__)
    ::clock_gettime(CLOCK_THREAD_CPUTIME_ID,&(this->end));
    add_measure(this->gtimer.measures[this->c],this->start,this->end);
#endif    
  } // end of MFrontBehaviourProfiler::~Timer

  MFrontBehaviourProfiler::MFrontBehaviourProfiler(const std::string& n)
    : name(n)
  {
    using namespace std;
    fill(begin(measures),end(measures),0);
  } // end of MFrontBehaviourProfiler::MFrontBehaviourProfiler

  MFrontBehaviourProfiler::~MFrontBehaviourProfiler()
  {
    using namespace std;
    cout << "\nResults of " << this->name << " profiling : ";
    print_time(cout,measures.back());
    cout << endl;
    string::size_type w{0};
    for(array<atomic<intmax_t>,21>::size_type i=0;i+1!=measures.size();++i){
      if(measures[i]!=0){
	w = max(w,getCodeBlockName(i).size());
      }
    }
    for(array<atomic<intmax_t>,21>::size_type i=0;i+1!=measures.size();++i){
      if(measures[i]!=0){
	cout << "- " << setw(w) << left << getCodeBlockName(i) << " : ";
	print_time(cout,measures[i]);
	cout << " (" << measures[i] << " ns)" << endl;
      }
    }
    cout << endl;
  } // end of MFrontBehaviourProfiler::~MFrontBehaviourProfiler
  
} // end of namespace mfront