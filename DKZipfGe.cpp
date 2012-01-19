#include <iostream>
#include <cmath>
#include "DKZipfGe.h"


void DKZipfGenerator::DKZipfInit(int pop, double th )
{
	int i;
	population=pop;
	theta=th;

	probs = new double[population];
	for (i=0; i<population; ++i)
	{
		probs[i]=0.0;
	}

	double *temp = new double[population];
	for(i=0; i<population; ++i)
	{
		temp[i] = pow(((double)1)/(i+1), theta);
	}

	double sum = 0.0;
	for(i=0; i<population; ++i)
	{
		sum += temp[i];
	}

	for(i=0; i<population; ++i)
	{
		probs[i] = temp[i]/sum;
	}

	delete [] temp;
}


DKZipfGenerator::DKZipfGenerator()
{
	DKZipfInit(100, (float)0.5);
}


DKZipfGenerator::DKZipfGenerator(int pop, double th)
{
	DKZipfInit(pop, th);
}


DKZipfGenerator::~DKZipfGenerator()
{
	delete[] probs;
}


int DKZipfGenerator::retZipfian()
{
	double tmp= ((double)rand()/RAND_MAX);
	if (tmp == 1.0)
	{
		tmp = 0.0;
	}

	int pos=0;

	double curSum = probs[0];
	while ( tmp>curSum )
	{
		curSum += probs[pos++];
	}

	return pos;
}