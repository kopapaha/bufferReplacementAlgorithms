#pragma once
#include "AbstractBuffer.h"

class LFU_Full_History :public AbstractBuffer
{

private:
	
protected:
	void historyRef(int refItem); //energeies anaforas antikeimenou
	struct list *history; //full history reference list
	void add2list(int refItem); //pros8hkh sthn arxh ths listas
	int bufReplace(void); //epistrefei th 8esh tou stoixeiou pou 8a ginei replace sto buffer

public:
	LFU_Full_History(int bufferSize);
	~LFU_Full_History(void);

	virtual bool ref(int refItem, int iter);
	virtual float retHitRatio(void);


	void test();

};
