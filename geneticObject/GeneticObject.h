#pragma once

#include <bitset>
#include <vector>
#include <random>
#include <stdlib.h> 
#include <time.h>
#include <math.h>

#define million 1000000

typedef void (*behaviourFunction)();

using namespace std;

class GeneticObject
{


public:
	GeneticObject();
	//~GeneticObject;
	GeneticObject(int bitsetSize, bitset<million> gene);
	
	bitset<million> run(bitset<million> input);
	
	GeneticObject breed(bitset<million> newGene);

	void addBehaviour(behaviourFunction newBehaviour);

	int fitness = 0;
	
	bitset<million> getGene()
	{
		return this->gene;
	}

private:
	int geneSize = 0;
	bitset<million> gene; // giant bit size hurray for breaking the stack :D
	bitset<million> returnBitSet;
	vector<behaviourFunction> functionList;

	bitset<million> createBehaviourSequence(bitset<million> input);

};