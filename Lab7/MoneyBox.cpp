#include "MoneyBox.h"

MinMax MoneyBox::FindMinMaxSum(int weight, TList<Coin>* coins)
{
	int count = coins->GetCount();
	MinMax* sumArray = new MinMax[weight+1];
	sumArray[0] = MinMax(0, 0);

	//for each weight from 1 till weight find min and max sums
	for(int i = 1; i <= weight; i++)
	{
		MinMax currentMinMax;
		for(int j = 0; j < count; j++)
		{
			//Find index of sum without this coin
			Coin coin = coins->GetElement(j);
			int prevSumIndex = i - coin.weight;
			//If can add coin to money box
			if (prevSumIndex >= 0 && sumArray[prevSumIndex].min != -1 && sumArray[prevSumIndex].max != -1)
			{
				//Update current min
				int minPrice = sumArray[prevSumIndex].min + coin.price;
				if (currentMinMax.min == -1 || minPrice < currentMinMax.min)
				{
					currentMinMax.min = minPrice;
				}

				//Update current max
				int maxPrice = sumArray[prevSumIndex].max + coin.price;
				if (maxPrice > currentMinMax.max)
				{
					currentMinMax.max = maxPrice;
				}
			}
		}

		sumArray[i] = currentMinMax;
	}

	MinMax resultSum = sumArray[weight];
	delete sumArray;

	return resultSum;
}
