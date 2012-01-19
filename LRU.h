#pragma once
#include "amalgam.h"
class LRU :
	public amalgam
{
public:
	LRU(int bufferSize);
	~LRU(void);

	virtual bool ref(int refItem, int iter);
	virtual float retHitRatio(void);
};

