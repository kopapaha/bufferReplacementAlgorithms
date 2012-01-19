#pragma once
#include "lfu_full_history.h"
class LFU_In_Buffer_History :public LFU_Full_History
{
private:
	void delFromHistory(int ID); //diagrafei to stoixeio ID apo th lista

public:
	LFU_In_Buffer_History(int bufferSize);
	~LFU_In_Buffer_History(void);

	virtual bool ref(int refItem, int i); 
	virtual float retHitRatio(void);
};

