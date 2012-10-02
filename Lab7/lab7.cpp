#include <stdio.h>
#include <stdlib.h>

struct ErrorMessages
{
	static const char* ERROR;
	static const char* MEMORY_ERROR;
	static const char* FILE_OPEN_ERROR;
	static const char* WRONG_INPUT_ERROR;
};

const char* ErrorMessages::MEMORY_ERROR = "Can't allocate memory";
const char* ErrorMessages::FILE_OPEN_ERROR = "Can't open file";
const char* ErrorMessages::WRONG_INPUT_ERROR = "Wrong input format.";
const char* ErrorMessages::ERROR = "Error";

class AppException 
{
public:
	AppException(const char* message)
	{
		_message = message;
	}
	const char* GetMessage()
	{
		return _message;
	}
private:
	const char* _message;
};

template <class T> class TList
{
public:
	TList()
	{
		_count = 0;
		_capacity = 0;
		_elements = NULL;
	};

	TList(T* elements, int length)
	{
		_count = length;
		_capacity = length;
		_elements = elements;
	};

	~TList()
	{
		if (_elements != NULL)
		{
			free(_elements);
		}
	};

	void Clear()
	{
		if (_elements != NULL)
		{
			free(_elements);
		}
		_count = 0;
		_capacity = 0;
	};

	void Add(T element)
	{
		if (_elements == NULL)
		{
			_elements = (T*) malloc(sizeof(T));
			_capacity = 1;
		}
		else if (_count == _capacity)
		{
			_capacity *= 2;
			_elements = (T*) realloc(_elements, _capacity * sizeof(T));
		}

		if (_elements == NULL)
		{
			throw AppException(ErrorMessages::MEMORY_ERROR);
		}

		_elements[_count] = element;
		_count++;
	};

	void TrimExcess()
	{
		if (_count != _capacity)
		{
			_elements = (T*) realloc(_elements, _count * sizeof(T));
			if (_elements == NULL)
			{
				throw AppException(ErrorMessages::MEMORY_ERROR);
			}
			_capacity = _count;
		}
	};

	int GetCount()
	{
		return _count;
	};

	T GetElement(int i)
	{
		return _elements[i];
	};

private:
	T* _elements;
	int _count;
	int _capacity;
};

struct Coin
{
	Coin()
	{
		price = 0;
		weight = 0;
	}

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

struct Problem
{
	Problem()
	{
		coins = new TList<Coin>();
	}

	~Problem()
	{
		delete coins;
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

void Parser::PrintError(const char* message) 
{
	printf("%s\n", message);
}

Problem Parser::ReadFromFile(FILE* inputFile)
{
	if (inputFile == NULL)
	{
		throw AppException(ErrorMessages::FILE_OPEN_ERROR);
	}

	Problem problem;
	int firstWeight, secondWeight;
	fscanf(inputFile, "%d", &firstWeight);
	fscanf(inputFile, "%d", &secondWeight);

	if (secondWeight - firstWeight >= 0)
	{
		problem.weight = secondWeight - firstWeight;
	}
	else
	{
		throw AppException(ErrorMessages::WRONG_INPUT_ERROR);
	}

	int count;
	fscanf(inputFile, "%d", &count);
	for(int i = 0; i < count; i++)
	{
		Coin coin;
		fscanf(inputFile, "%d", &coin.price);
		fscanf(inputFile, "%d", &coin.weight);
		problem.coins->Add(coin);
	}

	fclose(inputFile);

	return problem;
}

void Parser::PrintResult(MinMax* result)
{
	if (result->min == -1 || result->max == -1)
	{
		printf("Impossible\n");
	}
	else
	{
		printf("%d %d\n", result->min, result->max);
	}
}

void Execute()
{
	Parser parser;
	MoneyBox monebox;
	try
	{
		Problem problem = parser.ReadFromFile(stdin);
		MinMax result = monebox.FindMinMaxSum(problem.weight, problem.coins);
		parser.PrintResult(&result);
	}
	catch (AppException e)
	{
		parser.PrintError(e.GetMessage());
	}
}

int main(int argc, char** argv)
{
	Execute();
}

