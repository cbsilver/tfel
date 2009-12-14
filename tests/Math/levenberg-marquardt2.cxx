/*!
 * \file   levenberg-marquardt.cxx
 * \brief  
 * 
 * \author Helfer Thomas
 * \date   19 nov 2008
 */

#include<iostream>
#include<cstdlib>
#include<cmath>

#include<utility>
#include<vector>

#include"Math/FSLevenbergMarquardt.hxx"

std::pair<double,tfel::math::tvector<2u,double> >
test(const tfel::math::tvector<1u,double>& x,
     const tfel::math::tvector<2u,double>& p)
{
  using namespace std;
  using namespace tfel::math;
  pair<double,tvector<2u,double> > res;
  res.first = p(0) - p(1)/x(0);
  res.second(0) = 1;
  res.second(1) = -1/x(0);
  return res;
} // end of test

double
f(const double x)
{
  return 2.1033e-06*exp(-4.0302e+04/x);
}

int main(void)
{
  using namespace std;
  using namespace tfel::math;
//   cout << log(f(600)) << endl;
//   cout << log(f(700)) << endl;
//   cout << log(f(800)) << endl;

  FSLevenbergMarquardt<1u,2u> levmar(test);
  tvector<1u> x;
  tvector<2u> p;
  // data
  x(0)=600.;
  levmar.addData(x,log(f(x(0))));
  x(0)=700.;
  levmar.addData(x,log(f(x(0))));
  x(0)=800.;
  levmar.addData(x,log(f(x(0))));
  // initial guess
//   p(0)=-13.;
//   p(1)=4.e4;
  p(0)=1.;
  p(1)=1.;
  levmar.setInitialGuess(p);
  // execute
  p  = levmar.execute();
  cout << p(0) << endl;
  cout << p(1) << endl;
  return EXIT_SUCCESS;
} // end of main
