/*! 
 * \file  lu.cxx
 * \brief
 * \author Helfer Thomas
 * \brief 14 avr 2009
 */

#ifdef NDEBUG
#undef NDEBUG
#endif /* NDEBUG */

#include<cmath>
#include<cassert>
#include<cstdlib>
#include<limits>

#include"TFEL/Tests/Test.hxx"
#include"TFEL/Tests/TestManager.hxx"
#include"TFEL/Tests/TestFunctionWrapper.hxx"

#include"TFEL/Math/tvector.hxx"
#include"TFEL/Math/tmatrix.hxx"
#include"TFEL/Math/TinyMatrixSolve.hxx"

template<typename T>
bool TinyMatrixSolveTest()
{
  using namespace std;
  using namespace tfel::math;
  using tfel::math::vector;
  tmatrix<3,3,T> m;
  tvector<3,T> b;

  m(0,0)=0.;
  m(0,1)=2.;
  m(0,2)=1.;
  m(1,0)=1.;
  m(1,1)=0.;
  m(1,2)=0.;
  m(2,0)=3.;
  m(2,1)=0.;
  m(2,2)=1.;

  b(0) = 5;
  b(1) = -1;
  b(2) = -2;

  TinyMatrixSolve<3u,T>::exe(m,b);
  return ((abs(b(0)+1)<10*numeric_limits<T>::epsilon())&&
	  (abs(b(1)-2)<10*numeric_limits<T>::epsilon())&&
	  (abs(b(2)-1)<10*numeric_limits<T>::epsilon()));

} // end of TinyMatrixSolveTest

template<typename T>
bool TinyMatrixSolveTest2()
{
  using namespace std;
  using namespace tfel::math;
  using tfel::math::vector;
  tmatrix<3,3,T> m;
  tvector<3,T> b;

  m(0,0)=3.;
  m(0,1)=-1.;
  m(0,2)=2.;
  m(1,0)=1.;
  m(1,1)=2.;
  m(1,2)=3.;
  m(2,0)=2.;
  m(2,1)=-2.;
  m(2,2)=-1.;

  b(0) = 12;
  b(1) = 11;
  b(2) = 2;

  TinyMatrixSolve<3u,T>::exe(m,b);
  return ((abs(b(0)-3)<10*numeric_limits<T>::epsilon())&&
	  (abs(b(1)-1)<10*numeric_limits<T>::epsilon())&&
	  (abs(b(2)-2)<10*numeric_limits<T>::epsilon()));

}

int main(void)
{
  using namespace std;
  using namespace tfel::tests;
  using namespace tfel::utilities;
  typedef TestFunctionWrapper<TinyMatrixSolveTest<long double> >  Wrapper1;
  typedef TestFunctionWrapper<TinyMatrixSolveTest<double> >       Wrapper2;
  typedef TestFunctionWrapper<TinyMatrixSolveTest<float> >        Wrapper3;
  typedef TestFunctionWrapper<TinyMatrixSolveTest2<long double> > Wrapper4;
  typedef TestFunctionWrapper<TinyMatrixSolveTest2<double> >      Wrapper5;
  typedef TestFunctionWrapper<TinyMatrixSolveTest2<float> >       Wrapper6;
  //  typedef TestFunctionWrapper<test2> Wrapper2;
  TestManager& manager = TestManager::getTestManager();
  manager.addTestOutput(cout);
  manager.addXMLTestOutput("lu2.xml");
  manager.addTest("TinyMatrixSolve",shared_ptr<Test>(new Wrapper1("TinyMatrixSolveTest<long double>")));
  manager.addTest("TinyMatrixSolve",shared_ptr<Test>(new Wrapper2("TinyMatrixSolveTest<double>")));
  manager.addTest("TinyMatrixSolve",shared_ptr<Test>(new Wrapper3("TinyMatrixSolveTest<float>")));
  manager.addTest("TinyMatrixSolve - 2",shared_ptr<Test>(new Wrapper4("TinyMatrixSolveTest2<long double>")));
  manager.addTest("TinyMatrixSolve - 2",shared_ptr<Test>(new Wrapper5("TinyMatrixSolveTest2<double>")));
  manager.addTest("TinyMatrixSolve - 2",shared_ptr<Test>(new Wrapper6("TinyMatrixSolveTest2<float>")));
  TestResult r = manager.execute();
  if(!r.success()){
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
} // end of main