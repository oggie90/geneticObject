#include "GeneticObject.h"

behaviourFunction function1()
{

}



GeneticObject::GeneticObject() // do not use this constructor please
{
	srand(time(NULL));
}

GeneticObject::GeneticObject(int bitsetSize, bitset<million> gene)
{
	srand(time(NULL));
	this->geneSize = bitsetSize;
}

bitset<million> GeneticObject::run(bitset<million> input)
{
	bitset<million> behaviourSequence = this->createBehaviourSequence(input);

	int behaviourBitSectionLength = (int)(log2(this->functionList.size()) + 1.0f);

	int iterator = 0;
	int behaviour = 0;
	for (int i = 0; i < behaviourSequence.size(); i++)
	{
		iterator++;
		if (behaviourSequence[i])
		{
			behaviour += 1 << iterator;
		}
		if (iterator >= behaviourBitSectionLength)
		{
			this->functionList[behaviour]();
		}
	}

	return this->returnBitSet;
}

bitset<million> GeneticObject::createBehaviourSequence(bitset<million> input)
{
	bitset<million> output;

	/*
	
	OR/AND write 1 to output
	OR/AND write 0 to output
	OR/AND 	
	
	*/
	int outputIndex = 0;
	int inputIndex = 0;

	int tripletValue = 0;
	// run through gene
	for (int i = 0; i < geneSize-1; i++)
	{
		if (gene[i])
		{
			tripletValue += (1 << i);
		}

		if (i % 3 == 0)
		{
			i++;
			switch (tripletValue)
			{
			case 0: 
				// do nothing
				break;
			case 1:
				// AND write 1 to output
				if (input[inputIndex] && gene[i])
				{
					output[outputIndex] = true;
				}
				break;
			case 2:
				// OR write 1 to output
				if (input[inputIndex] || gene[i])
				{
					output[outputIndex] = true;
				}
				break;
			case 3:
				// AND write 0 to output
				if (input[inputIndex] && gene[i])
				{
					output[outputIndex] = false;
				}
				break;
			case 4:
				// OR write 0 to output
				if (input[inputIndex] || gene[i])
				{
					output[outputIndex] = false;
				}
				break;
			case 5:
				// flip output
				if (outputIndex - 1 > 0)
					output[outputIndex - 1] = !(output[outputIndex - 1]);
				break;
			case 6:
				// copy from input
				output[outputIndex] = input[inputIndex];
				break;
			case 7:
				// copy from input
				output[outputIndex] = gene[i];
				break;
			default:
				break;
			}
			outputIndex ++;
			inputIndex ++;


			tripletValue = 0; // reset value
		}
	}


	return output;
}

GeneticObject GeneticObject::breed(bitset<million> input)
{
	bitset<million> newGene = this->gene;
	int i = 0;
	if (rand() % 1 == 1)
	{
		// set start point to mid
		i = (int)(this->geneSize / 2);
	}

	for (i; i < i + (int)(this->geneSize/2); i++)
	{
		newGene[i] = input[i];
	}

	return GeneticObject(this->geneSize, newGene);

}

void GeneticObject::addBehaviour(behaviourFunction newBehaviour)
{
	this->functionList.push_back(newBehaviour);
}

int geneSize = 0;
bitset<million> gene; // giant bit size hurray for breaking the stack :D
vector<behaviourFunction> functionList;


