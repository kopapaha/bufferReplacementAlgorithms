#include "LFU_In_Buffer_History.h"
#include <iostream>


LFU_In_Buffer_History::LFU_In_Buffer_History(int bufferSize)
	:LFU_Full_History(bufferSize)
{
}


LFU_In_Buffer_History::~LFU_In_Buffer_History(void)
{
}




void LFU_In_Buffer_History::delFromHistory(int ID)
{
	struct list *l,*l1;
	for(l=history,l1=history; l!=NULL; l1=l,l=l->nxt)
	{
		if (l->ID==ID)
		{
			if (l==history&&l1==history)
			{
				//free history
				history=l->nxt;
				break;
			}
			else
			{
				l1->nxt=l->nxt;
				//free l
				break;
			}
			
		}
	}
}




bool LFU_In_Buffer_History::ref(int refItem, int iter)
{
	int i;

	simTime=iter;
	//elegxos gia to an yparxei sto buffer
	for (i=0; i<bufSize; i++)
	{
		if (refItem==buffer[i])
		{
			historyRef(refItem);
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
			historyRef(refItem);
			return false; //cache miss
		}
	}	
	
	//de xwraei sto buffer ara:
	//evresh tou stoixeiou pou 8a diwksoume apo to buffer
	int delPos=bufReplace();
	delFromHistory(buffer[delPos]); //kratame mono tou buffer
	buffer[delPos]=refItem;
	
	historyRef(refItem);
	return false; //cache replacement

}


float LFU_In_Buffer_History::retHitRatio(void)
{
	return (float)cacheHitCount/(float)simTime;
}