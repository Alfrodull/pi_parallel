#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include "integral.h"
using namespace std; 

const int numOfThreads = 3;

double piSum[numOfThreads];

struct mathdata
{
	double piPiece;
	int start;
	int end;
};

inline double integrand(double x) //求圆周率的被积函数选用的是4/(1+x^2)
{
	return 4.0 / (1.0 + x*x);
}

void* integral(void *arg)
{
	struct mathdata *data = (struct mathdata *) arg;
	data->piPiece = 0;
	double sum = 0;
	for (int i = data->start; i < data->end; ++i)
	{
		double x = 1.0*i/numOfParts;
		sum += integrand(x);
	}
	data->piPiece = sum/numOfParts;
	return NULL;
}

int main(int argc, char const *argv[])
{
	pthread_t tHandles[numOfThreads];
	mathdata *dataArray = (mathdata*) malloc(numOfThreads*sizeof(mathdata));
	for (int i = 0; i < numOfThreads; ++i)
	{
		dataArray[i].start = (numOfParts/numOfThreads)*i;
		dataArray[i].end = (numOfParts/numOfThreads)*(i+1);
		if(i == numOfThreads - 1)
		{
			dataArray[i].end = numOfParts;
		}
		pthread_create(&tHandles[i],NULL,integral,(void*)&dataArray[i]);
	}

	double pi = 0;
	for (int i = 0; i < numOfThreads; ++i)
	{
		pthread_join(tHandles[i],NULL);
		pi += dataArray[i].piPiece;
	}
	cout << "Pi = " << pi << endl;
	free(dataArray);
	return 0;
}