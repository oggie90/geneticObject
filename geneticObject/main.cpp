#include "GeneticObject.h"
#include <iostream>
#include <ctime>
#define halfmillion million/2



#define matchingNumber 1
#define genepoolsize 20;


int produceValue(bitset<million> input)
{
	int output = 0;
	for (int i = 0; i < 64; i++)
	{
		if (input[i])
		{
			//if (!(output + (1<<i) < 0))
				output += 1 << i;
		}
	}

	return output;
}

int produceFitness(int input)
{
	return abs(123456789 - input);
}

bitset<million> generateRandomGene()
{
	bitset<million> newGene;
	for (int i = 0; i < million; i++)
	{
		int x = rand() % 2;
		if (rand() % 2 == 1)
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

void doNothing(GeneticObject &This)
{
	//cout << "0";
}

void flip(GeneticObject &This)
{
	This.returnBitSet.flip();
	//cout << "1";
}

void addOne(GeneticObject &This)
{
	This.returnBitSet[0] = true;
	//cout << "2";
}

void bitShiftRight(GeneticObject &This)
{
	This.returnBitSet = This.returnBitSet >> 1;
	//cout << "3";
}

void bitShiftLeft(GeneticObject &This)
{
	This.returnBitSet = This.returnBitSet << 1;
	//cout << "4";
}


/*
	see which one gets closer to the number 123456789
	via genetics
*/
void main()
{
	srand(time(NULL));

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
		genePool[i].addBehaviour(doNothing);
		genePool[i].addBehaviour(flip);
		genePool[i].addBehaviour(addOne);
		genePool[i].addBehaviour(bitShiftRight);
		genePool[i].addBehaviour(bitShiftLeft);
	}
	int x = 1;
	int distance = -999;
	clock_t startTime = clock();
	cout << "start time: " << clock() << endl;
	while (distance != 0)
	{
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
		distance = genePool[0].fitness;
		// debug write fitness values
		
		cout << x << " - " << genePool[0].fitness << endl;

		/*
		cout << "-----------\n" << "FITNESS VALUES\n" << "-----------\n";
		
		for (int i = genePool.size()-1; i >= 0; i--)
		{
			cout << genePool[i].fitness << "\n";
		}
		
		*/

		// breed according to fitness

		vector<GeneticObject> buffer;
		int breedLimit = 700;
		for (int i = 0; i < genePool.size(); i++)
		{
			for (int j = 0; j < genePool.size() && breedLimit >= 0; j++)
			{
				buffer.push_back(genePool[i].breed(genePool[j].getGene()));
				breedLimit--;
			}
		}
		genePool = buffer;

		for (int i = 0; i < genePool.size(); i++)
		{
			genePool[i].addBehaviour(doNothing);
			genePool[i].addBehaviour(flip);
			genePool[i].addBehaviour(addOne);
			genePool[i].addBehaviour(bitShiftRight);
			genePool[i].addBehaviour(bitShiftLeft);
		}

		x++;
		if (distance < 5)
		{
			cout << "-----\nTime Difference: " << clock() - startTime << "\n-------" << endl;
			distance = -999;
			for (int i = 0; i < million; i++)
			{
				if (rand() & 1 == 1)
				{
					stimulusInput[i] = true;
				}
			}
		}

	}
	

}

