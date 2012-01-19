#ifndef _DKZIPFGEN
#define _DKZIPFGEN

class DKZipfGenerator
{
private:
	double *probs;
	double theta;
	int population;
	void DKZipfInit(int pop, double th);

public:
	DKZipfGenerator();
	DKZipfGenerator(int pop, double th);
	virtual ~DKZipfGenerator();

	int retPopulation();
	int retZipfian();

};

#endif