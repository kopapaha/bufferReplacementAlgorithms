#include "amalgam.h"
#include <iostream>

amalgam::amalgam(int bufferSize)
{
	int i;
	bufSize=bufferSize;
	history = NULL;
	cacheHitCount=0;

	buffer = new int[bufSize];
	//init buffer
	for( i=0; i<bufSize; i++)
	{
		buffer[i]=-1;
	}

	
	history = new struct list*[bufSize];
	//init metadata
	for (i=0; i<bufSize; i++)
	{
		history[i]=NULL;
	}
}


amalgam::~amalgam(void)
{
}


void amalgam::historyRef(int iter, int pos)
{
	struct list *l;

	l = new struct list;
	
	l->ID=buffer[pos];
	l->ref=iter;
	if ( history[pos]==NULL )
	{
		history[pos]=l;
		l->nxt=NULL;
	}
	else
	{
		l->nxt = history[pos];
		history[pos]=l;
	}

}



int amalgam::bufReplace(void)
{
	int i;
	struct list *l;
	float *val,min;
	int retPos;
	float lamda=1.0, sumVal,x;

	val = new float[bufSize];
	for(i=0; i<bufSize; i++)
	{
		sumVal=0.0;
		for(l=history[i]; l!=NULL; l=l->nxt)
		{
			x = simTime - l->ref;
			sumVal += pow(((float)1/(float)2),(lamda*x));
		}
		val[i]=sumVal;
	}

	min=val[0];
	retPos=0;
	for(i=1; i<bufSize; i++)
	{
		if (val[i]<min) 
		{
			min=val[i];
			retPos=i;
		}
	}
	
	delete[] val;
	return retPos;
}




void amalgam::historyDel(int delPos)
{
	struct list *l,*l1;
	for(l=history[delPos]; l!=NULL; )
	{
		l1=l;
		l=l->nxt;
		delete l1;
	}
	history[delPos]=NULL;
}




bool amalgam::ref(int refItem, int iter)
{
	int i;

	simTime=iter;
	//elegxos gia to an yparxei sto buffer
	for (i=0; i<bufSize; i++)
	{
		if (refItem==buffer[i])
		{
			//pros8hkh anaforas sthn antistoixh 8esh tou pinaka apo listes history
			historyRef(iter,i);
			cacheHitCount++;
			return true; //cache hit!
		}
	}

	//elegxos gia to an xwraei sto buffer
	for (i=0; i<bufSize; i++)
	{
		if (buffer[i]<0)
		{
			//yparxei elef8erh 8esh
			buffer[i]=refItem;
			historyRef(iter,i);
			return false; //cache miss
		}
	}

	//de xwraei sto buffer ara:
	//evresh tou stoixeiou pou 8a diwksoume apo to buffer
	int delPos = bufReplace();
	//std::cout << "watch ->"<< delPos << std::endl;
	buffer[delPos]=refItem;
	historyDel(delPos);
	historyRef(iter,delPos);
	
	return false; //cache replacement


}


float amalgam::retHitRatio(void)
{
	return (float)cacheHitCount/(float)simTime;
}


void amalgam::test(){
	struct list *l;
	int i;
	for(i=0; i<bufSize; i++)
	{
		for (l = history[i]; l!=NULL; l=l->nxt)
		{
			std::cout << "ID: " << l->ID << " timeRef " << l->ref << std::endl;
		}
	}

	std::cout << "\nbuffer:\n" ;
	for (int i=0; i<bufSize; i++)
	{
		std::cout << " " << buffer[i];
	}
	std::cout << "\n" ;
}