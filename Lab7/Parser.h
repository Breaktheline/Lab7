#ifndef H_PARSER
#define H_PARSER

#include "MoneyBox.h"
#include <stdio.h>

struct Problem
{
	Problem()
	{
		coins = new TList<Coin>();
	}

	int weight;
	TList<Coin>* coins;
};

class Parser
{
public:
	Problem ReadFromFile(FILE* inputFile);
	void PrintResult(MinMax* result);
	void PrintError(const char* message);
};

#endif

