#include <iostream>
#include <stdlib.h> 
#include <time.h> 
#include <pthread.h>
#include "prob.h"
using namespace std; 

const int numOfThreads = 3;

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

void* makePoits(void* arg)//参数是要产生的点的数量，返回值是在圆内的点的数量
{
	int num = *((int*)arg);
	int hit = 0;
	unsigned seed = (unsigned)time(NULL) + (unsigned)pthread_self();
	for (int i = 0; i < num; ++i)
	{
		double x = 2.0*rand_r(&seed)/(RAND_MAX);
		double y = 2.0*rand_r(&seed)/(RAND_MAX);
		if (hitCircle(x,y))
		{
			hit += 1;
		}
	}
	return (void*) hit;
}

int main(void)
{
	pthread_t tHandles[numOfThreads];
	int *pArray = (int*)malloc( numOfThreads*sizeof(int) ); //用于保存每个线程处理的点的数量
	int *threadRe = (int*)malloc( numOfThreads*sizeof(int) ); //用于保存每个线程返回值
	int hit = 0;
	int pAlloted = 0;//已经被分配的点的数量
	for (int i = 0; i < numOfThreads; ++i)
	{
		pArray[i] = numOfPoints/numOfThreads;
		if (i == numOfThreads - 1)
		{
			pArray[i] = numOfPoints - pAlloted;
		}
		pAlloted += pArray[i];
		pthread_create(&tHandles[i],NULL,makePoits,(void*)&pArray[i]);
	}

	for (int i = 0; i < numOfThreads; ++i)
	{
		pthread_join(tHandles[i],(void**) &threadRe[i]);
	}
	for (int i = 0; i < numOfThreads; ++i)
	{
		hit+=threadRe[i];
	}

	cout << "Pi = " << ((double)hit)/numOfPoints*4.0 << endl;
	free(pArray);
	free(threadRe);
	return 0;
}