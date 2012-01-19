#ifndef _AbstractBuffer
#define _AbstractBuffer

class AbstractBuffer
{
protected:
	int *buffer; //periexei ta ID twn blocks pou einai sto buffer
	int bufSize; //mege8os buffer
	struct list
	{
		int ID; 
		int ref; //ari8mos anaforwn[LFUs] h' xronos anaforas [Amalgam/LRU]
		struct list *nxt;
	};
	int simTime; //simulation time
	int cacheHitCount; //gia ton ypologismo tou hit-ratio

	//void add2list(); //pros8hkh sthn arxh ths listas
	//void delFromList(struct list *l);
public:
	virtual bool ref(int refItem, int i)=0;
	virtual float retHitRatio(void)=0;
};

#endif