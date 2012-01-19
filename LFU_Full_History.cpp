#include "LFU_Full_History.h"
#include <iostream>

LFU_Full_History::LFU_Full_History(int bufferSize)
{
	bufSize=bufferSize;
	history = NULL;
	cacheHitCount=0;

	buffer = new int[bufSize];
	//init buffer
	for(int i=0; i<bufSize; i++)
	{
		buffer[i]=-1;
	}
}


LFU_Full_History::~LFU_Full_History(void)
{
}


void LFU_Full_History::add2list(int refItem)
{
	struct list *n;

	n = new struct list;
	n->ID = refItem;
	n->ref=1;
	if (history==NULL)
	{
		history=n;
		n->nxt=NULL;
	}
	else
	{
		n->nxt=history;
		history=n;
	}


}


void LFU_Full_History::historyRef(int refItem)
{
	struct list *l;


	if (history==NULL)
	{
		add2list(refItem);
	}
	else
	{
		/*psakse gia to an to stoixeio to exw ksanazhthsei ara
		yparxei sth lista*/
		for(l=history;l!=NULL;l=l->nxt)
		{
			if (l->ID==refItem)
			{
				//yparxei, aplh afkshsh tou ari8mou anaforas
				l->ref++;
				break;
			}
		}

		//dietrekse olh th lista kai dn vrhke to stoixeio
		if (l==NULL)
		{
			//pros8hkh sthn arxh
			add2list(refItem);
		}
	}

}




int LFU_Full_History::bufReplace(void)
{
	int i, min=-1;
	int delPos;
	struct list *l;
	 
	for (i=0; i<bufSize; i++)
	{
		//gia ka8e stoixeio tou buffer
		for(l=history; l!=NULL; l=l->nxt)
		{
			//psakse sth lista na vreis thn anafora tou
			if (buffer[i]==l->ID)
			{
				if (min==-1)
				{
					//arxikopoihsh
					min=l->ref;
					delPos=i; 
				}
				if (l->ref < min)
				{
					min = l->ref;
					delPos = i;
				}
			}
		}
	}

	//epistrofh ths 8eshs me to mikrotero ari8mo anaforwn
	return delPos;
}



bool LFU_Full_History::ref(int refItem, int iter)
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
	buffer[bufReplace()]=refItem;
	historyRef(refItem);
	return false; //cache replacement

}




float LFU_Full_History::retHitRatio(void)
{
	return (float)cacheHitCount/(float)simTime;
}


void LFU_Full_History::test(){
	struct list *lw;
	for (lw = history;lw!=NULL; lw=lw->nxt)
	{
		std::cout << "ID: " << lw->ID << " Ref " << lw->ref << std::endl;
	}

	std::cout << "\nbuffer:\n" ;
	for (int i=0; i<bufSize; i++)
	{
		std::cout << " " << buffer[i];
	}
	std::cout << "\n" ;
}