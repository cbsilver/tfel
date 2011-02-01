/*!
 * \file   EvaluatorFunction.ixx
 * \brief  
 * 
 * \author Helfer Thomas
 * \date   15 jan 2009
 */

#ifndef _LIB_TFEL_MATH_EVALUATORFUNCTION_IXX_
#define _LIB_TFEL_MATH_EVALUATORFUNCTION_IXX_ 

namespace tfel
{

  namespace math
  {

    namespace parser
    {

      template<EvaluatorProxyFunctionPtr1P1V f>
      tfel::utilities::shared_ptr<tfel::math::parser::Expr>
      EvaluatorFunction1P1VGenerator(const std::vector<std::string>& params,
				     std::vector<tfel::utilities::shared_ptr<tfel::math::parser::Expr> >& args)
      {
	using namespace std;
	using namespace tfel::utilities;
	using namespace tfel::math;
	using namespace tfel::math::parser;
	int nbr;
	Evaluator::checkParameterNumber(1,params.size());
	Evaluator::checkVariableNumber(1,args.size());
	nbr = Evaluator::convertToInt("EvaluatorFunction1P1VGenerator",params[0]);
	return shared_ptr<Expr>(new EvaluatorFunction1P1V(f,nbr,args[0]));
      } // end of EvaluatorFunction1P1VGenerator

      template<EvaluatorProxyFunctionPtr2P1V f>
      tfel::utilities::shared_ptr<tfel::math::parser::Expr>
      EvaluatorFunction2P1VGenerator(const std::vector<std::string>& params,
				     std::vector<tfel::utilities::shared_ptr<tfel::math::parser::Expr> >& args)
      {
	using namespace std;
	using namespace tfel::utilities;
	using namespace tfel::math;
	using namespace tfel::math::parser;
	int nbr;
	int nbr2;
	Evaluator::checkParameterNumber(2,params.size());
	Evaluator::checkVariableNumber(1,args.size());
	nbr  = Evaluator::convertToInt("EvaluatorFunction2P1VGenerator",params[0]);
	nbr2 = Evaluator::convertToInt("EvaluatorFunction2P1VGenerator",params[1]);
	return shared_ptr<Expr>(new EvaluatorFunction2P1V(f,nbr,nbr2,args[0]));
      } // end of EvaluatorFunction2P1VGenerator

      template<EvaluatorProxyFunctionPtr1P2V f>
      tfel::utilities::shared_ptr<tfel::math::parser::Expr>
      EvaluatorFunction1P2VGenerator(const std::vector<std::string>& params,
				     std::vector<tfel::utilities::shared_ptr<tfel::math::parser::Expr> >& args)
      {
	using namespace std;
	using namespace tfel::utilities;
	using namespace tfel::math;
	using namespace tfel::math::parser;
	int nbr;
	Evaluator::checkParameterNumber(1,params.size());
	Evaluator::checkVariableNumber(2,args.size());
	nbr = Evaluator::convertToInt("EvaluatorFunction1P2VGenerator",params[0]);
	return shared_ptr<Expr>(new EvaluatorFunction1P2V(f,nbr,args[0],args[1]));
      } // end of EvaluatorFunction1P2VGenerator

      template<EvaluatorProxyFunctionPtr2P2V f>
      tfel::utilities::shared_ptr<tfel::math::parser::Expr>
      EvaluatorFunction2P2VGenerator(const std::vector<std::string>& params,
				     std::vector<tfel::utilities::shared_ptr<tfel::math::parser::Expr> >& args)
      {
	using namespace std;
	using namespace tfel::utilities;
	using namespace tfel::math;
	using namespace tfel::math::parser;
	int nbr;
	int nbr2;
	Evaluator::checkParameterNumber(2,params.size());
	Evaluator::checkVariableNumber(2,args.size());
	nbr  = Evaluator::convertToInt("EvaluatorFunction2P2VGenerator",params[0]);
	nbr2 = Evaluator::convertToInt("EvaluatorFunction2P2VGenerator",params[1]);
	return shared_ptr<Expr>(new EvaluatorFunction2P2V(f,nbr,nbr2,args[0],args[1]));
      } // end of EvaluatorFunction2P2VGenerator

#ifdef __SUNPRO_CC
	extern "C" {
#endif /* __SUNPRO_CC */
	typedef double (* EvaluatorFunctionWrapper0_type)();
	typedef double (* EvaluatorFunctionWrapper0_type1P)(int);
	typedef double (* EvaluatorFunctionWrapper0_type2P)(int,int);
	typedef double (* EvaluatorFunctionWrapper0_type1UP)(unsigned int);
	typedef double (* EvaluatorFunctionWrapper0_type2UP)(unsigned int,
							     unsigned int);

	typedef double (* EvaluatorFunctionWrapper1_type)(double);
	typedef double (* EvaluatorFunctionWrapper1_type1P)(int,double);
	typedef double (* EvaluatorFunctionWrapper1_type2P)(int,int,double);
	typedef double (* EvaluatorFunctionWrapper1_type1UP)(unsigned int,double);
	typedef double (* EvaluatorFunctionWrapper1_type2UP)(unsigned int,
							     unsigned int,
							     double);

	typedef double (* EvaluatorFunctionWrapper2_type)(double,double);
	typedef double (* EvaluatorFunctionWrapper2_type1P)(int,double,double);
	typedef double (* EvaluatorFunctionWrapper2_type2P)(int,int,double,double);
	typedef double (* EvaluatorFunctionWrapper2_type1UP)(unsigned int,double,double);
	typedef double (* EvaluatorFunctionWrapper2_type2UP)(unsigned int,
							     unsigned int,
							     double,double);

	typedef double (* EvaluatorFunctionWrapper3_type)(double,double,double);
	typedef double (* EvaluatorFunctionWrapper3_type1P)(int,double,double,double);
	typedef double (* EvaluatorFunctionWrapper3_type2P)(int,int,double,double,double);
	typedef double (* EvaluatorFunctionWrapper3_type1UP)(unsigned int,double,double,double);
	typedef double (* EvaluatorFunctionWrapper3_type2UP)(unsigned int,
							     unsigned int,
							     double,double,double);

	typedef double (* EvaluatorFunctionWrapper4_type)(double,double,double,double);
	typedef double (* EvaluatorFunctionWrapper4_type1P)(int,double,double,double,double);
	typedef double (* EvaluatorFunctionWrapper4_type2P)(int,int,double,double,double,double);
	typedef double (* EvaluatorFunctionWrapper4_type1UP)(unsigned int,double,double,double,double);
	typedef double (* EvaluatorFunctionWrapper4_type2UP)(unsigned int,
							     unsigned int,
							     double,double,double,double);

	typedef double (* EvaluatorFunctionWrapper5_type)(double,double,double,
							  double,double);
	typedef double (* EvaluatorFunctionWrapper5_type1P)(int,double,double,double,
							    double,double);
	typedef double (* EvaluatorFunctionWrapper5_type2P)(int,int,double,double,double,
							    double,double);
	typedef double (* EvaluatorFunctionWrapper5_type1UP)(unsigned int,double,double,double,
							     double,double);
	typedef double (* EvaluatorFunctionWrapper5_type2UP)(unsigned int,
							     unsigned int,
							     double,double,double,
							     double,double);

	typedef double (* EvaluatorFunctionWrapper6_type)(double,double,double,
							  double,double,double);
	typedef double (* EvaluatorFunctionWrapper6_type1P)(int,double,double,double,
							    double,double,double);
	typedef double (* EvaluatorFunctionWrapper6_type2P)(int,int,double,double,double,
							    double,double,double);
	typedef double (* EvaluatorFunctionWrapper6_type1UP)(unsigned int,double,double,double,
							     double,double,double);
	typedef double (* EvaluatorFunctionWrapper6_type2UP)(unsigned int,
							     unsigned int,
							     double,double,double,
							     double,double,double);

	typedef double (* EvaluatorFunctionWrapper7_type)(double,double,double,
							  double,double,double,double);
	typedef double (* EvaluatorFunctionWrapper7_type1P)(int,double,double,double,
							    double,double,double,double);
	typedef double (* EvaluatorFunctionWrapper7_type2P)(int,int,double,double,double,
							    double,double,double,double);
	typedef double (* EvaluatorFunctionWrapper7_type1UP)(unsigned int,double,double,double,
							     double,double,double,double);
	typedef double (* EvaluatorFunctionWrapper7_type2UP)(unsigned int,
							     unsigned int,
							     double,double,double,
							     double,double,double,double);

	typedef double (* EvaluatorFunctionWrapper8_type)(double,double,double,
							  double,double,double,double,double);
	typedef double (* EvaluatorFunctionWrapper8_type1P)(int,double,double,double,
							    double,double,double,double,double);
	typedef double (* EvaluatorFunctionWrapper8_type2P)(int,int,double,double,double,
							    double,double,double,double,double);
	typedef double (* EvaluatorFunctionWrapper8_type1UP)(unsigned int,double,double,double,
							     double,double,double,double,double);
	typedef double (* EvaluatorFunctionWrapper8_type2UP)(unsigned int,
							     unsigned int,
							     double,double,double,
							     double,double,double,double,double);

	typedef double (* EvaluatorFunctionWrapper9_type)(double,double,double,
							  double,double,double,double,
							  double,double);
	typedef double (* EvaluatorFunctionWrapper9_type1P)(int,double,double,double,
							    double,double,double,double,
							    double,double);
	typedef double (* EvaluatorFunctionWrapper9_type2P)(int,int,double,double,double,
							    double,double,double,double,
							    double,double);
	typedef double (* EvaluatorFunctionWrapper9_type1UP)(unsigned int,double,double,double,
							     double,double,double,double,
							     double,double);
	typedef double (* EvaluatorFunctionWrapper9_type2UP)(unsigned int,
							     unsigned int,
							     double,double,double,
							     double,double,double,double,
							     double,double);

	typedef double (* EvaluatorFunctionWrapper10_type)(double,double,double,
							   double,double,double,double,
							   double,double,double);
	typedef double (* EvaluatorFunctionWrapper10_type1P)(int,double,double,double,
							     double,double,double,double,
							     double,double,double);
	typedef double (* EvaluatorFunctionWrapper10_type2P)(int,int,double,double,double,
							     double,double,double,double,
							     double,double,double);
	typedef double (* EvaluatorFunctionWrapper10_type1UP)(unsigned int,double,double,double,
							      double,double,double,double,
							      double,double,double);
	typedef double (* EvaluatorFunctionWrapper10_type2UP)(unsigned int,
							      unsigned int,
							      double,double,double,
							      double,double,double,double,
							      double,double,double);

#ifdef __SUNPRO_CC
     }
#endif /* __SUNPRO_CC */

      template<>
      struct TFEL_VISIBILITY_LOCAL EvaluatorFunctionWrapper<0u>
      {

	typedef EvaluatorFunctionWrapper0_type    type;
	typedef EvaluatorFunctionWrapper0_type1P  type1P;
	typedef EvaluatorFunctionWrapper0_type2P  type2P;
	typedef EvaluatorFunctionWrapper0_type1UP type1UP; 
	typedef EvaluatorFunctionWrapper0_type2UP type2UP;

	static double
	apply(const type,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type1P,int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type2P,int,int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type1UP,unsigned int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type2UP,unsigned int,unsigned int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
      }; // end of EvaluatorFunctionWrapper<1u>

      template<>
      struct TFEL_VISIBILITY_LOCAL EvaluatorFunctionWrapper<1u>
      {
	typedef EvaluatorFunctionWrapper1_type    type;
	typedef EvaluatorFunctionWrapper1_type1P  type1P;
	typedef EvaluatorFunctionWrapper1_type2P  type2P;
	typedef EvaluatorFunctionWrapper1_type1UP type1UP; 
	typedef EvaluatorFunctionWrapper1_type2UP type2UP;

	static double
	apply(const type,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type1P,int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type2P,int,int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type1UP,unsigned int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type2UP,unsigned int,unsigned int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
      }; // end of EvaluatorFunctionWrapper<1u>

      template<>
      struct TFEL_VISIBILITY_LOCAL EvaluatorFunctionWrapper<2u>
      {
	typedef EvaluatorFunctionWrapper2_type    type;
	typedef EvaluatorFunctionWrapper2_type1P  type1P;
	typedef EvaluatorFunctionWrapper2_type2P  type2P;
	typedef EvaluatorFunctionWrapper2_type1UP type1UP; 
	typedef EvaluatorFunctionWrapper2_type2UP type2UP;

	static double
	apply(const type,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type1P,int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type2P,int,int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type1UP,unsigned int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type2UP,unsigned int,unsigned int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
      }; // end of EvaluatorFunctionWrapper<2u>

      template<>
      struct TFEL_VISIBILITY_LOCAL EvaluatorFunctionWrapper<3u>
      {
	typedef EvaluatorFunctionWrapper3_type    type;
	typedef EvaluatorFunctionWrapper3_type1P  type1P;
	typedef EvaluatorFunctionWrapper3_type2P  type2P;
	typedef EvaluatorFunctionWrapper3_type1UP type1UP; 
	typedef EvaluatorFunctionWrapper3_type2UP type2UP;

	static double
	apply(const type,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type1P,int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type2P,int,int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type1UP,unsigned int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type2UP,unsigned int,unsigned int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
      }; // end of EvaluatorFunctionWrapper<3u>

      template<>
      struct TFEL_VISIBILITY_LOCAL EvaluatorFunctionWrapper<4u>
      {
	typedef EvaluatorFunctionWrapper4_type    type;
	typedef EvaluatorFunctionWrapper4_type1P  type1P;
	typedef EvaluatorFunctionWrapper4_type2P  type2P;
	typedef EvaluatorFunctionWrapper4_type1UP type1UP; 
	typedef EvaluatorFunctionWrapper4_type2UP type2UP;

	static double
	apply(const type,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type1P,int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type2P,int,int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type1UP,unsigned int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type2UP,unsigned int,unsigned int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
      }; // end of EvaluatorFunctionWrapper<4u>

      template<>
      struct TFEL_VISIBILITY_LOCAL EvaluatorFunctionWrapper<5u>
      {
	typedef EvaluatorFunctionWrapper5_type    type;
	typedef EvaluatorFunctionWrapper5_type1P  type1P;
	typedef EvaluatorFunctionWrapper5_type2P  type2P;
	typedef EvaluatorFunctionWrapper5_type1UP type1UP; 
	typedef EvaluatorFunctionWrapper5_type2UP type2UP;

	static double
	apply(const type,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type1P,int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type2P,int,int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type1UP,unsigned int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type2UP,unsigned int,unsigned int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
      }; // end of EvaluatorFunctionWrapper<5u>

      template<>
      struct TFEL_VISIBILITY_LOCAL EvaluatorFunctionWrapper<6u>
      {
	typedef EvaluatorFunctionWrapper6_type    type;
	typedef EvaluatorFunctionWrapper6_type1P  type1P;
	typedef EvaluatorFunctionWrapper6_type2P  type2P;
	typedef EvaluatorFunctionWrapper6_type1UP type1UP; 
	typedef EvaluatorFunctionWrapper6_type2UP type2UP;

	static double
	apply(const type,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type1P,int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type2P,int,int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type1UP,unsigned int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type2UP,unsigned int,unsigned int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
      }; // end of EvaluatorFunctionWrapper<6u>

      template<>
      struct TFEL_VISIBILITY_LOCAL EvaluatorFunctionWrapper<7u>
      {
	typedef EvaluatorFunctionWrapper7_type    type;
	typedef EvaluatorFunctionWrapper7_type1P  type1P;
	typedef EvaluatorFunctionWrapper7_type2P  type2P;
	typedef EvaluatorFunctionWrapper7_type1UP type1UP; 
	typedef EvaluatorFunctionWrapper7_type2UP type2UP;

	static double
	apply(const type,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type1P,int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type2P,int,int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type1UP,unsigned int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type2UP,unsigned int,unsigned int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
      }; // end of EvaluatorFunctionWrapper<7u>

      template<>
      struct TFEL_VISIBILITY_LOCAL EvaluatorFunctionWrapper<8u>
      {
	typedef EvaluatorFunctionWrapper8_type    type;
	typedef EvaluatorFunctionWrapper8_type1P  type1P;
	typedef EvaluatorFunctionWrapper8_type2P  type2P;
	typedef EvaluatorFunctionWrapper8_type1UP type1UP; 
	typedef EvaluatorFunctionWrapper8_type2UP type2UP;
	static double
	apply(const type,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type1P,int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type2P,int,int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type1UP,unsigned int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type2UP,unsigned int,unsigned int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
      }; // end of EvaluatorFunctionWrapper<8u>

      template<>
      struct TFEL_VISIBILITY_LOCAL EvaluatorFunctionWrapper<9u>
      {
	typedef EvaluatorFunctionWrapper9_type    type;
	typedef EvaluatorFunctionWrapper9_type1P  type1P;
	typedef EvaluatorFunctionWrapper9_type2P  type2P;
	typedef EvaluatorFunctionWrapper9_type1UP type1UP; 
	typedef EvaluatorFunctionWrapper9_type2UP type2UP;
	static double
	apply(const type,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type1P,int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type2P,int,int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type1UP,unsigned int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type2UP,unsigned int,unsigned int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
      }; // end of EvaluatorFunctionWrapper<9u>

      template<>
      struct TFEL_VISIBILITY_LOCAL EvaluatorFunctionWrapper<10u>
      {
	typedef EvaluatorFunctionWrapper10_type    type;
	typedef EvaluatorFunctionWrapper10_type1P  type1P;
	typedef EvaluatorFunctionWrapper10_type2P  type2P;
	typedef EvaluatorFunctionWrapper10_type1UP type1UP; 
	typedef EvaluatorFunctionWrapper10_type2UP type2UP;
	static double
	apply(const type,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type1P,int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type2P,int,int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type1UP,unsigned int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
	static double
	apply(const type2UP,unsigned int,unsigned int,
	      const std::vector<tfel::utilities::shared_ptr<Expr> >&);
      }; // end of EvaluatorFunctionWrapper<10u>

      template<unsigned short N>
      EvaluatorFunctionNV<N>::EvaluatorFunctionNV(typename EvaluatorFunctionWrapper<N>::type f_,
						  const std::vector<tfel::utilities::shared_ptr<Expr> >& args_)
	: f(f_),
	  args(args_)
      {} // end of EvaluatorFunctionNV<N>::EvaluatorFunctionNV

      template<unsigned short N>
      double
      EvaluatorFunctionNV<N>::getValue(void) const
      {
	return EvaluatorFunctionWrapper<N>::apply(f,args);
      } // end of EvaluatorFunctionNV<N>::getValue(void) const

      template<unsigned short N>
      void
      EvaluatorFunctionNV<N>::getParametersNames(std::set<std::string>& p) const
      {
	using namespace std;
	using namespace tfel::utilities;
        vector<shared_ptr<Expr> >::const_iterator pa;
        for(pa=this->args.begin();pa!=this->args.end();++pa){
	  (*pa)->getParametersNames(p);
	}
      } // end of EvaluatorFunctionNV<N>::getParametersNames

      template<unsigned short N>
      tfel::utilities::shared_ptr<Expr>
      EvaluatorFunctionNV<N>::resolveDependencies(const std::vector<double>& v) const
      {
	using namespace std;
	using namespace tfel::utilities;
	vector<shared_ptr<Expr> > nargs(this->args.size());
        vector<shared_ptr<Expr> >::const_iterator p;
        vector<shared_ptr<Expr> >::size_type i;
        for(p=this->args.begin(),i=0;p!=this->args.end();++p,++i){
	  nargs[i]=(*p)->resolveDependencies(v);
        }
        return shared_ptr<Expr>(new EvaluatorFunctionNV<N>(this->f,nargs));
      } // end of EvaluatorFunctionNV<N>::resolveDependencies const

      template<unsigned short N>
      tfel::utilities::shared_ptr<Expr>
      EvaluatorFunctionNV<N>::clone(const std::vector<double>& v) const
      {
	using namespace std;
	using namespace tfel::utilities;
	vector<shared_ptr<Expr> > nargs(this->args.size());
        vector<shared_ptr<Expr> >::const_iterator p;
        vector<shared_ptr<Expr> >::size_type i;
        for(p=this->args.begin(),i=0;p!=this->args.end();++p,++i){
	  nargs[i]=(*p)->clone(v);
        }
        return shared_ptr<Expr>(new EvaluatorFunctionNV<N>(this->f,nargs));
      } // end of EvaluatorFunctionNV<N>::resolveDependencies const

      template<unsigned short N>
      tfel::utilities::shared_ptr<Expr>
      EvaluatorFunctionNV<N>::createFunctionByChangingParametersIntoVariables(const std::vector<double>& v,
									      const std::vector<std::string>& params,
									      const std::map<std::string,
									      std::vector<double>::size_type>& pos) const
      {
	using namespace std;
	using namespace tfel::utilities;
	vector<shared_ptr<Expr> > nargs(this->args.size());
        vector<shared_ptr<Expr> >::const_iterator p;
        vector<shared_ptr<Expr> >::size_type i;
        for(p=this->args.begin(),i=0;p!=this->args.end();++p,++i){
	  nargs[i]=(*p)->createFunctionByChangingParametersIntoVariables(v,params,pos);
        }
        return shared_ptr<Expr>(new EvaluatorFunctionNV<N>(this->f,nargs));
      } // end of EvaluatorFunctionNV<N>::createFunctionByChangingParametersIntoVariables

      template<unsigned short N>
      void
      EvaluatorFunctionNV<N>::checkCyclicDependency(std::vector<std::string>& names) const
      {
	using namespace std;
	using namespace tfel::utilities;
        vector<shared_ptr<Expr> >::const_iterator p;
        for(p=this->args.begin();p!=this->args.end();++p){
	  vector<string> n;
	  (*p)->checkCyclicDependency(n);
	  mergeVariablesNames(names,n);
	}
      } // end of EvaluatorFunctionNV<N>::checkCyclicDependency

      template<unsigned short N>
      EvaluatorFunctionNV<N>::~EvaluatorFunctionNV()
      {} // end of EvaluatorFunctionNV<N>::~EvaluatorFunctionNV()

      template<unsigned short N>
      EvaluatorFunction1PNV<N>::EvaluatorFunction1PNV(typename EvaluatorFunctionWrapper<N>::type1P f_,
						      const int n_,
						      const std::vector<tfel::utilities::shared_ptr<Expr> >& args_)
	: f(f_),
	  n(n_),
	  args(args_)
      {} // end of EvaluatorFunction1PNV<N>::EvaluatorFunction1PNV

      template<unsigned short N>
      double
      EvaluatorFunction1PNV<N>::getValue(void) const
      {
	return EvaluatorFunctionWrapper<N>::apply(this->f,this->n,this->args);
      } // end of EvaluatorFunction1PNV<N>::getValue(void) const

      template<unsigned short N>
      tfel::utilities::shared_ptr<Expr>
      EvaluatorFunction1PNV<N>::resolveDependencies(const std::vector<double>& v) const
      {
	using namespace std;
	using namespace tfel::utilities;
	vector<shared_ptr<Expr> > nargs(this->args.size());
        vector<shared_ptr<Expr> >::const_iterator p;
        vector<shared_ptr<Expr> >::size_type i;
        for(p=this->args.begin(),i=0;p!=this->args.end();++p,++i){
	  nargs[i]=(*p)->resolveDependencies(v);
        }
        return shared_ptr<Expr>(new EvaluatorFunction1PNV<N>(this->f,this->n,nargs));
      } // end of EvaluatorFunction1PNV<N>::resolveDependencies const

      template<unsigned short N>
      void
      EvaluatorFunction1PNV<N>::getParametersNames(std::set<std::string>& p) const
      {
	using namespace std;
	using namespace tfel::utilities;
        typename vector<shared_ptr<Expr> >::const_iterator pa;
        for(pa=this->args.begin();pa!=this->args.end();++pa){
	  (*pa)->getParametersNames(p);
        }
      } // end of EvaluatorFunction1PNV<N>::getParametersNames

      template<unsigned short N>
      tfel::utilities::shared_ptr<Expr>
      EvaluatorFunction1PNV<N>::clone(const std::vector<double>& v) const
      {
	using namespace std;
	using namespace tfel::utilities;
	vector<shared_ptr<Expr> > nargs(this->args.size());
        vector<shared_ptr<Expr> >::const_iterator p;
        vector<shared_ptr<Expr> >::size_type i;
        for(p=this->args.begin(),i=0;p!=this->args.end();++p,++i){
	  nargs[i]=(*p)->clone(v);
        }
        return shared_ptr<Expr>(new EvaluatorFunction1PNV<N>(this->f,this->n,nargs));
      } // end of EvaluatorFunction1PNV<N>::clone

      template<unsigned short N>
      tfel::utilities::shared_ptr<Expr>
      EvaluatorFunction1PNV<N>::createFunctionByChangingParametersIntoVariables(const std::vector<double>& v,
										const std::vector<std::string>& params,
										const std::map<std::string,
										std::vector<double>::size_type>& pos) const
      {
	using namespace std;
	using namespace tfel::utilities;
	vector<shared_ptr<Expr> > nargs(this->args.size());
        vector<shared_ptr<Expr> >::const_iterator p;
        vector<shared_ptr<Expr> >::size_type i;
        for(p=this->args.begin(),i=0;p!=this->args.end();++p,++i){
	  nargs[i]=(*p)->createFunctionByChangingParametersIntoVariables(v,params,pos);
        }
        return shared_ptr<Expr>(new EvaluatorFunction1PNV<N>(this->f,this->n,nargs));
      } // end of EvaluatorFunction1PNV<N>::resolveDependencies const

      template<unsigned short N>
      void
      EvaluatorFunction1PNV<N>::checkCyclicDependency(std::vector<std::string>& names) const
      {
	using namespace std;
	using namespace tfel::utilities;
        vector<shared_ptr<Expr> >::const_iterator p;
        for(p=this->args.begin();p!=this->args.end();++p){
	  vector<string> vn;
	  (*p)->checkCyclicDependency(vn);
	  mergeVariablesNames(names,vn);
        }
      } // end of EvaluatorFunction1PNV<N>::checkCyclicDependency

      template<unsigned short N>
      EvaluatorFunction1PNV<N>::~EvaluatorFunction1PNV()
      {} // end of EvaluatorFunction1PNV<N>::~EvaluatorFunction1PNV()

      template<unsigned short N>
      EvaluatorFunction2PNV<N>::EvaluatorFunction2PNV(typename EvaluatorFunctionWrapper<N>::type2P f_,
						      const int n_,
						      const int m_,
						      const std::vector<tfel::utilities::shared_ptr<Expr> >& args_)
	: f(f_),
	  n(n_),
	  m(m_),
	  args(args_)
      {} // end of EvaluatorFunction2PNV<N>::EvaluatorFunction2PNV

      template<unsigned short N>
      double
      EvaluatorFunction2PNV<N>::getValue(void) const
      {
	return EvaluatorFunctionWrapper<N>::apply(this->f,this->n,this->m,this->args);
      } // end of EvaluatorFunction2PNV<N>::getValue(void) const

      template<unsigned short N>
      tfel::utilities::shared_ptr<Expr>
      EvaluatorFunction2PNV<N>::resolveDependencies(const std::vector<double>& v) const
      {
	using namespace std;
	using namespace tfel::utilities;
	vector<shared_ptr<Expr> > nargs(this->args.size());
        vector<shared_ptr<Expr> >::const_iterator p;
        vector<shared_ptr<Expr> >::size_type i;
        for(p=this->args.begin(),i=0;p!=this->args.end();++p,++i){
	  nargs[i]=(*p)->resolveDependencies(v);
        }
        return shared_ptr<Expr>(new EvaluatorFunction2PNV<N>(this->f,this->n,this->m,nargs));
      } // end of EvaluatorFunction2PNV<N>::resolveDependencies const

      template<unsigned short N>
      tfel::utilities::shared_ptr<Expr>
      EvaluatorFunction2PNV<N>::clone(const std::vector<double>& v) const
      {
	using namespace std;
	using namespace tfel::utilities;
	vector<shared_ptr<Expr> > nargs(this->args.size());
        vector<shared_ptr<Expr> >::const_iterator p;
        vector<shared_ptr<Expr> >::size_type i;
        for(p=this->args.begin(),i=0;p!=this->args.end();++p,++i){
	  nargs[i]=(*p)->clone(v);
        }
        return shared_ptr<Expr>(new EvaluatorFunction2PNV<N>(this->f,this->n,this->m,nargs));
      } // end of EvaluatorFunction2PNV<N>::clone

      template<unsigned short N>
      tfel::utilities::shared_ptr<Expr>
      EvaluatorFunction2PNV<N>::createFunctionByChangingParametersIntoVariables(const std::vector<double>& v,
										const std::vector<std::string>& params,
										const std::map<std::string,
										std::vector<double>::size_type>& pos) const
      {
	using namespace std;
	using namespace tfel::utilities;
	vector<shared_ptr<Expr> > nargs(this->args.size());
        vector<shared_ptr<Expr> >::const_iterator p;
        vector<shared_ptr<Expr> >::size_type i;
        for(p=this->args.begin(),i=0;p!=this->args.end();++p,++i){
	  nargs[i]=(*p)->createFunctionByChangingParametersIntoVariables(v,params,pos);
        }
        return shared_ptr<Expr>(new EvaluatorFunction2PNV<N>(this->f,this->n,this->m,nargs));
      } // end of EvaluatorFunction2PNV<N>::createFunctionByChangingParametersIntoVariables

      template<unsigned short N>
      void
      EvaluatorFunction2PNV<N>::checkCyclicDependency(std::vector<std::string>& names) const
      {
	using namespace std;
	using namespace tfel::utilities;
        vector<shared_ptr<Expr> >::const_iterator p;
        for(p=this->args.begin();p!=this->args.end();++p){
	  vector<string> vn;
	  (*p)->checkCyclicDependency(vn);
	  mergeVariablesNames(names,vn);
        }
      } // end of EvaluatorFunction2PNV<N>::checkCyclicDependency

      template<unsigned short N>
      EvaluatorFunction2PNV<N>::~EvaluatorFunction2PNV()
      {} // end of EvaluatorFunction2PNV<N>::~EvaluatorFunctionNV()

      template<unsigned short N>
      EvaluatorFunction1UPNV<N>::EvaluatorFunction1UPNV(typename EvaluatorFunctionWrapper<N>::type1UP f_,
							const unsigned int n_,
							const std::vector<tfel::utilities::shared_ptr<Expr> >& args_)
	: f(f_),
	  n(n_),
	  args(args_)
      {} // end of EvaluatorFunction1UPNV<N>::EvaluatorFunction1UPNV

      template<unsigned short N>
      double
      EvaluatorFunction1UPNV<N>::getValue(void) const
      {
	return EvaluatorFunctionWrapper<N>::apply(this->f,this->n,this->args);
      } // end of EvaluatorFunction1UPNV<N>::getValue(void) const

      template<unsigned short N>
      tfel::utilities::shared_ptr<Expr>
      EvaluatorFunction1UPNV<N>::resolveDependencies(const std::vector<double>& v) const
      {
	using namespace std;
	using namespace tfel::utilities;
	vector<shared_ptr<Expr> > nargs(this->args.size());
        vector<shared_ptr<Expr> >::const_iterator p;
        vector<shared_ptr<Expr> >::size_type i;
        for(p=this->args.begin(),i=0;p!=this->args.end();++p,++i){
	  nargs[i]=(*p)->resolveDependencies(v);
        }
        return shared_ptr<Expr>(new EvaluatorFunction1UPNV<N>(this->f,this->n,nargs));
      } // end of EvaluatorFunction1UPNV<N>::resolveDependencies const

      template<unsigned short N>
      void
      EvaluatorFunction1UPNV<N>::getParametersNames(std::set<std::string>& p) const
      {
	using namespace std;
	using namespace tfel::utilities;
        typename vector<shared_ptr<Expr> >::const_iterator pa;
        for(pa=this->args.begin();pa!=this->args.end();++pa){
	  (*pa)->getParametersNames(p);
        }
      } // end of EvaluatorFunction1UPNV<N>::getParametersNames

      template<unsigned short N>
      tfel::utilities::shared_ptr<Expr>
      EvaluatorFunction1UPNV<N>::clone(const std::vector<double>& v) const
      {
	using namespace std;
	using namespace tfel::utilities;
	vector<shared_ptr<Expr> > nargs(this->args.size());
        vector<shared_ptr<Expr> >::const_iterator p;
        vector<shared_ptr<Expr> >::size_type i;
        for(p=this->args.begin(),i=0;p!=this->args.end();++p,++i){
	  nargs[i]=(*p)->clone(v);
        }
        return shared_ptr<Expr>(new EvaluatorFunction1UPNV<N>(this->f,this->n,nargs));
      } // end of EvaluatorFunction1UPNV<N>::clone

      template<unsigned short N>
      tfel::utilities::shared_ptr<Expr>
      EvaluatorFunction1UPNV<N>::createFunctionByChangingParametersIntoVariables(const std::vector<double>& v,
										 const std::vector<std::string>& params,
										 const std::map<std::string,
										 std::vector<double>::size_type>& pos) const
      {
	using namespace std;
	using namespace tfel::utilities;
	vector<shared_ptr<Expr> > nargs(this->args.size());
        vector<shared_ptr<Expr> >::const_iterator p;
        vector<shared_ptr<Expr> >::size_type i;
        for(p=this->args.begin(),i=0;p!=this->args.end();++p,++i){
	  nargs[i]=(*p)->createFunctionByChangingParametersIntoVariables(v,params,pos);
        }
        return shared_ptr<Expr>(new EvaluatorFunction1UPNV<N>(this->f,this->n,nargs));
      } // end of EvaluatorFunction1UPNV<N>::clone

      template<unsigned short N>
      void
      EvaluatorFunction1UPNV<N>::checkCyclicDependency(std::vector<std::string>& names) const
      {
	using namespace std;
	using namespace tfel::utilities;
        vector<shared_ptr<Expr> >::const_iterator p;
        for(p=this->args.begin();p!=this->args.end();++p){
	  vector<string> vn;
	  (*p)->checkCyclicDependency(vn);
	  mergeVariablesNames(names,vn);
        }
      } // end of EvaluatorFunction1UPNV<N>::checkCyclicDependency

      template<unsigned short N>
      EvaluatorFunction1UPNV<N>::~EvaluatorFunction1UPNV()
      {} // end of EvaluatorFunction1UPNV<N>::~EvaluatorFunction1UPNV()

      template<unsigned short N>
      EvaluatorFunction2UPNV<N>::EvaluatorFunction2UPNV(typename EvaluatorFunctionWrapper<N>::type2UP f_,
							const unsigned int n_,
							const unsigned int m_,
							const std::vector<tfel::utilities::shared_ptr<Expr> >& args_)
	: f(f_),
	  n(n_),
	  m(m_),
	  args(args_)
      {} // end of EvaluatorFunction2UPNV<N>::EvaluatorFunction2UPNV

      template<unsigned short N>
      double
      EvaluatorFunction2UPNV<N>::getValue(void) const
      {
	return EvaluatorFunctionWrapper<N>::apply(this->f,this->n,this->m,this->args);
      } // end of EvaluatorFunction2UPNV<N>::getValue(void) const

      template<unsigned short N>
      tfel::utilities::shared_ptr<Expr>
      EvaluatorFunction2UPNV<N>::resolveDependencies(const std::vector<double>& v) const
      {
	using namespace std;
	using namespace tfel::utilities;
	vector<shared_ptr<Expr> > nargs(this->args.size());
        vector<shared_ptr<Expr> >::const_iterator p;
        vector<shared_ptr<Expr> >::size_type i;
        for(p=this->args.begin(),i=0;p!=this->args.end();++p,++i){
	  nargs[i]=(*p)->resolveDependencies(v);
        }
        return shared_ptr<Expr>(new EvaluatorFunction2UPNV<N>(this->f,this->n,this->m,nargs));
      } // end of EvaluatorFunction2UPNV<N>::resolveDependencies const

      template<unsigned short N>
      tfel::utilities::shared_ptr<Expr>
      EvaluatorFunction2UPNV<N>::clone(const std::vector<double>& v) const
      {
	using namespace std;
	using namespace tfel::utilities;
	vector<shared_ptr<Expr> > nargs(this->args.size());
        vector<shared_ptr<Expr> >::const_iterator p;
        vector<shared_ptr<Expr> >::size_type i;
        for(p=this->args.begin(),i=0;p!=this->args.end();++p,++i){
	  nargs[i]=(*p)->clone(v);
        }
        return shared_ptr<Expr>(new EvaluatorFunction2UPNV<N>(this->f,this->n,this->m,nargs));
      } // end of EvaluatorFunction2UPNV<N>::clone

      template<unsigned short N>
      tfel::utilities::shared_ptr<Expr>
      EvaluatorFunction2UPNV<N>::createFunctionByChangingParametersIntoVariables(const std::vector<double>& v,
										 const std::vector<std::string>& params,
										 const std::map<std::string,
										 std::vector<double>::size_type>& pos) const
      {
	using namespace std;
	using namespace tfel::utilities;
	vector<shared_ptr<Expr> > nargs(this->args.size());
        vector<shared_ptr<Expr> >::const_iterator p;
        vector<shared_ptr<Expr> >::size_type i;
        for(p=this->args.begin(),i=0;p!=this->args.end();++p,++i){
	  nargs[i]=(*p)->createFunctionByChangingParametersIntoVariables(v,params,pos);
        }
        return shared_ptr<Expr>(new EvaluatorFunction2UPNV<N>(this->f,this->n,this->m,nargs));
      } // end of EvaluatorFunction2UPNV<N>::clone

      template<unsigned short N>
      void
      EvaluatorFunction2UPNV<N>::getParametersNames(std::set<std::string>& p) const
      {
	using namespace std;
	using namespace tfel::utilities;
        typename vector<shared_ptr<Expr> >::const_iterator pa;
        for(pa=this->args.begin();pa!=this->args.end();++pa){
	  (*pa)->getParametersNames(p);
        }
      } // end of EvaluatorFunction2UPNV<N>::getParametersNames

      template<unsigned short N>
      void
      EvaluatorFunction2UPNV<N>::checkCyclicDependency(std::vector<std::string>& names) const
      {
	using namespace std;
	using namespace tfel::utilities;
        vector<shared_ptr<Expr> >::const_iterator p;
        for(p=this->args.begin();p!=this->args.end();++p){
	  vector<string> vn;
	  (*p)->checkCyclicDependency(vn);
	  mergeVariablesNames(names,vn);
        }
      } // end of EvaluatorFunction2UPNV<N>::checkCyclicDependency

      template<unsigned short N>
      EvaluatorFunction2UPNV<N>::~EvaluatorFunction2UPNV()
      {} // end of EvaluatorFunction2UPNV<N>::~EvaluatorFunctionNV()

      template<unsigned short N,
	       typename EvaluatorFunctionWrapper<N>::type f>
      tfel::utilities::shared_ptr<tfel::math::parser::Expr>
      EvaluatorFunctionNVGenerator(const std::vector<std::string>& params,
				   std::vector<tfel::utilities::shared_ptr<tfel::math::parser::Expr> >& args)
      {
	using namespace std;
	using namespace tfel::utilities;
	using namespace tfel::math;
	using namespace tfel::math::parser;
	Evaluator::checkParameterNumber(0,params.size());
	Evaluator::checkVariableNumber(N,args.size());
	return shared_ptr<Expr>(new EvaluatorFunctionNV<N>(f,args));
      } // end of EvaluatorFunctionNVGenerator

      template<unsigned short N,
	       typename EvaluatorFunctionWrapper<N>::type1P f>
      tfel::utilities::shared_ptr<tfel::math::parser::Expr>
      EvaluatorFunction1PNVGenerator(const std::vector<std::string>& params,
				     std::vector<tfel::utilities::shared_ptr<tfel::math::parser::Expr> >& args)
      {
	using namespace std;
	using namespace tfel::utilities;
	using namespace tfel::math;
	using namespace tfel::math::parser;
	int nbr;
	Evaluator::checkParameterNumber(1,params.size());
	Evaluator::checkVariableNumber(N,args.size());
	nbr  = Evaluator::convertToInt("EvaluatorFunction1PNVGenerator",params[0]);
	return shared_ptr<Expr>(new EvaluatorFunction1PNV<N>(f,nbr,args));
      } // end of EvaluatorFunction1PNVGenerator

      template<unsigned short N,
	       typename EvaluatorFunctionWrapper<N>::type2P f>
      tfel::utilities::shared_ptr<tfel::math::parser::Expr>
      EvaluatorFunction2PNVGenerator(const std::vector<std::string>& params,
				     std::vector<tfel::utilities::shared_ptr<tfel::math::parser::Expr> >& args)
      {
	using namespace std;
	using namespace tfel::utilities;
	using namespace tfel::math;
	using namespace tfel::math::parser;
	int nbr;
	int nbr2;
	Evaluator::checkParameterNumber(2,params.size());
	Evaluator::checkVariableNumber(N,args.size());
	nbr  = Evaluator::convertToInt("EvaluatorFunction2PNVGenerator",params[0]);
	nbr2 = Evaluator::convertToInt("EvaluatorFunction2PNVGenerator",params[1]);
	return shared_ptr<Expr>(new EvaluatorFunction2PNV<N>(f,nbr,nbr2,args));
      } // end of EvaluatorFunction1PNVGenerator

      template<unsigned short N,
	       typename EvaluatorFunctionWrapper<N>::type1UP f>
      tfel::utilities::shared_ptr<tfel::math::parser::Expr>
      EvaluatorFunction1UPNVGenerator(const std::vector<std::string>& params,
				      std::vector<tfel::utilities::shared_ptr<tfel::math::parser::Expr> >& args)
      {
	using namespace std;
	using namespace tfel::utilities;
	using namespace tfel::math;
	using namespace tfel::math::parser;
	unsigned int nbr;
	Evaluator::checkParameterNumber(1,params.size());
	Evaluator::checkVariableNumber(N,args.size());
	nbr  = Evaluator::convertToUnsignedInt("EvaluatorFunction1UPNVGenerator",params[0]);
	return shared_ptr<Expr>(new EvaluatorFunction1UPNV<N>(f,nbr,args));
      } // end of EvaluatorFunction1UPNVGenerator

      template<unsigned short N,
	       typename EvaluatorFunctionWrapper<N>::type2UP f>
      tfel::utilities::shared_ptr<tfel::math::parser::Expr>
      EvaluatorFunction2UPNVGenerator(const std::vector<std::string>& params,
				      std::vector<tfel::utilities::shared_ptr<tfel::math::parser::Expr> >& args)
      {
	using namespace std;
	using namespace tfel::utilities;
	using namespace tfel::math;
	using namespace tfel::math::parser;
	unsigned int nbr;
	unsigned int nbr2;
	Evaluator::checkParameterNumber(2,params.size());
	Evaluator::checkVariableNumber(N,args.size());
	nbr  = Evaluator::convertToUnsignedInt("EvaluatorFunction2UPNVGenerator",params[0]);
	nbr2 = Evaluator::convertToUnsignedInt("EvaluatorFunction2UPNVGenerator",params[1]);
	return shared_ptr<Expr>(new EvaluatorFunction2UPNV<N>(f,nbr,nbr2,args));
      } // end of EvaluatorFunction1UPNVGenerator

    } // end of namespace parser

  } // end of namespace math

} // end of namespace tfel

#endif /* _LIB_TFEL_MATH_EVALUATORPROXY_IXX_ */