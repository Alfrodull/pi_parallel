#include <iostream>
#include <stdlib.h> 
#include <time.h> 
#include "prob.h"
using namespace std; 



bool hitCircle(double x,double y)//计算坐标(x,y)的点是否在圆心为(1,1)半径为1的圆中
{
	double sqr_distance = (x - 1.0)*(x -  1.0) + (y - 1.0)*(y - 1.0);
	if (sqr_distance > 1.0)//距离的平方大于半径平方
	{
		return false;
	}
	else
	{
		return true;
	}
}

int main(void)
{
	unsigned seed = (unsigned)time(NULL);
	int hit = 0;
	for (int i = 0; i < numOfPoints; ++i)
	{
		double x = 2.0*rand_r(&seed)/(RAND_MAX);
		double y = 2.0*rand_r(&seed)/(RAND_MAX);
		if (hitCircle(x,y))
		{
			hit += 1;
		}
	}
	// cout << hit << "/" << numOfPoints << endl;
	cout << "Pi = " << ((double)hit)/numOfPoints*4.0 << endl;
	return 0;
}