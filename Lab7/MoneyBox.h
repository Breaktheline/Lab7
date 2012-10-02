#ifndef H_MONEY_BOX
#define H_MONEY_BOX

#include "TList.h"

struct Coin
{
	Coin(int aPrice, int aWeight)
	{
		price = aPrice;
		weight = aWeight;
	}
	int price;
	int weight;
};

struct MinMax
{
	MinMax()
	{
		min = -1;
		max = -1;
	}

	MinMax(int aMin, int aMax)
	{
		min = aMin;
		max = aMax;
	}

	int min;
	int max;
};

class MoneyBox
{
public:
	MinMax FindMinMaxSum(int weight, TList<Coin>* coins);
};

#endif