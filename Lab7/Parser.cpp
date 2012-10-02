#include "Parser.h"

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
