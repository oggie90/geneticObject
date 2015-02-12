#include "GeneticObject.h"
#include <iostream>
#define halfmillion 500000

#define matchingNumber 123456789
#define genepoolsize 20;


int produceValue(bitset<million> input)
{
	int output = 0;
	for (int i = 0; i < 64; i++)
	{
		if (input[i])
			output += 1 << i;
	}
	return output;
}

int produceFitness(int input)
{
	return 123456789 - input;
}

bitset<million> generateRandomGene()
{
	bitset<million> newGene;
	for (int i = 0; i < million; i++)
	{
		if (rand() % 1 == 1)
			newGene[i] = true;
	}
	return newGene;
}
/*
functions

flip
add 1 - ie first index = true
bit shift right
bit shift left

*/

void flip()
{
	
}

void addOne()
{

}

void bitShiftRight()
{

}

void bitShiftLeft()
{

}


/*
	see which one gets closer to the number 123456789
	via genetics
*/
void main()
{
	// create the random input
	bitset<million> stimulusInput;
	for (int i = 0; i < million; i++)
	{
		if (rand() & 1 == 1)
		{
			stimulusInput[i] = true;
		}
	}


	vector<GeneticObject> genePool;
	for (int i = 0; i < 20; i++)
	{
		genePool.push_back(GeneticObject(halfmillion, generateRandomGene()));
		genePool[i].addBehaviour(flip);
		genePool[i].addBehaviour(addOne);
		genePool[i].addBehaviour(bitShiftRight);
		genePool[i].addBehaviour(bitShiftLeft);
	}


	// run each and get fitness
	for (int i = 0; i < genePool.size(); i++)
	{
		genePool[i].fitness = produceFitness(produceValue(genePool[i].run(stimulusInput)));

	}
	// sort by fitness value higher = better // using a horrible horrible bubble sort because i cba with optimisation atm
	// bubble sort

	for (int i = 0; i < genePool.size(); i++)
	{
		for (int j = 0; j < genePool.size() - 1; j++)
		{
			if (genePool[j].fitness > genePool[j + 1].fitness)
			{
				GeneticObject buffer = genePool[j + 1];
				genePool[j + 1] = genePool[j];
				genePool[j] = buffer;
			}
		}
	}
	// debug write fitness values

	cout << "-----------\n" << "FITNESS VALUES\N" << "-----------\n";
	for (int i = 0; i < genePool.size(); i++)
	{
		cout << genePool[i].fitness << "\n";
	}

	// breed according to fitness
	
	int breedLimit = 100;
	for (int i = 0; i < genePool.size(); i++)
	{
		for (int j = 0; j < genePool.size() && breedLimit >= 0; j++)
		{
			genePool[i].breed(genePool[j].getGene());
		}
	}

	//GeneticObject test = GeneticObject(halfmillion);


}

