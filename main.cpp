#include <iostream>
#include "DKZipfGe.h"
#include "LFU_Full_History.h"
#include "LFU_In_Buffer_History.h"
#include "amalgam.h"
#include "LRU.h"

using namespace std;

/*
main gia elegxo ths DKZipfGenerator
*/
//int main ()
//{0
//	DKZipfGenerator zgen(10, 1.0);
//
//	for(int i=0; i<100; ++i)
//	{
//		cout << zgen.retZipfian() << endl;
//	}
//	cout.flush();
//
//}



int main ()
{
	int max_simulation_time=2000;
	int n_items=100;
	int buffer_size=4;

	DKZipfGenerator zgen(n_items, 0.7);

	LFU_Full_History lfu(buffer_size);
	lfu.ref(111,1);
	lfu.ref(112,1);
	lfu.ref(113,1);
	lfu.ref(113,1);
	lfu.ref(112,1);
	lfu.ref(112,1);
	lfu.ref(112,1);
	lfu.ref(111,1);
	lfu.ref(9,1);
	lfu.ref(100,1);
	lfu.ref(100,1);
	lfu.ref(100,1);
	lfu.ref(33,1);
	lfu.ref(34,1);
	lfu.ref(34,1);
	lfu.ref(34,1);
	lfu.ref(34,1);
	lfu.ref(20,1);
	cout << "LFU_Full\n";
	lfu.test();
	cout << "Hit ratio: " << lfu.retHitRatio()<< endl;

	LFU_In_Buffer_History lfuIn(buffer_size);

	lfuIn.ref(200,1);
	lfuIn.ref(201,2);
	lfuIn.ref(202,3);
	lfuIn.ref(203,4);
	lfuIn.ref(200,5);
	lfuIn.ref(70,6);
	lfuIn.ref(71,7);
	lfuIn.ref(71,8);
	lfuIn.ref(60,9);
	lfuIn.ref(60,10);
	lfuIn.ref(61,11);
	cout << "\nLFU_In_buffer\n";
	lfuIn.test();
	cout << "Hit ratio: " << lfuIn.retHitRatio() << endl;
	

	amalgam am(buffer_size);

	am.ref(500,1);
	//am.ref(500,2);
	am.ref(501,2);
	am.ref(502,3);
	am.ref(503,4);
	//am.ref(500,6);
	am.ref(503,5);
	am.ref(503,6);
	am.ref(500,7);
	am.ref(501,8);
	am.ref(502,9);

	am.ref(504,10);
	am.ref(566,11);
	cout << "\nAmalgam\n";
	am.test();
	cout << "Hit ratio: " << am.retHitRatio() << endl;
	

	LRU lr(buffer_size);

	lr.ref(900,1);
	lr.ref(901,2);
	lr.ref(902,3);
	lr.ref(903,4);
	lr.ref(900,5);
	lr.ref(903,6);
	lr.ref(901,7);
	//lr.ref(902,8);

	lr.ref(999,9);

	cout << "\LRU\n";
	lr.test();

	cout << "Hit ratio: " << lr.retHitRatio() << endl;
}