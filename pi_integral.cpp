#include <iostream>
#include "integral.h"
using namespace std; 

inline double integrand(double x) //求圆周率的被积函数选用的是4/(1+x^2)
{
	return 4.0 / (1.0 + x*x);
}

int main(void)
{
	//求被积函数在[0,1]的定积分，所得结果即为圆周率
	double pi = 0;
	for (int i = 0; i < numOfParts; ++i)
	{
		double x = 1.0*i/numOfParts;
		pi += integrand(x);
	}
	pi /= numOfParts;
	cout << "Pi = " << pi << endl; 
	return 0;
} 
