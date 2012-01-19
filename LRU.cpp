#include "LRU.h"


LRU::LRU(int bufferSize):amalgam(bufferSize)
{
}


LRU::~LRU(void)
{
}



bool LRU::ref(int refItem, int iter)
{
	int i;

	simTime=iter;
	//elegxos gia to an yparxei sto buffer
	for (i=0; i<bufSize; i++)
	{
		if (refItem==buffer[i])
		{
			//pros8hkh anaforas sthn antistoixh 8esh tou pinaka apo listes history
			historyDel(i);
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
	buffer[delPos]=refItem;
	historyDel(delPos);
	historyRef(iter,delPos);
	
	return false; //cache replacement


}



float LRU::retHitRatio(void)
{
	return (float)cacheHitCount/(float)simTime;
}