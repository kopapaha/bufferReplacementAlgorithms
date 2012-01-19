#pragma once
#include "abstractbuffer.h"

class amalgam :
	public AbstractBuffer
{

protected:
	struct list **history; //metadata
	void historyRef(int refTime, int pos); //pros8hkh sthn katalhlh 8esh ths listas tou pinaka history
	int bufReplace(void); //epistrofh 8eshs tou stoixeiou pou 8a ekdiwx8ei sto buffer
	void historyDel(int delpos); //diagrafei apo tn pinaka history th lista sth 8esh delPos

public:
	amalgam(int bufferSize);
	~amalgam(void);

	virtual bool ref(int refItem, int iter);
	virtual float retHitRatio(void);


	void test();
};

