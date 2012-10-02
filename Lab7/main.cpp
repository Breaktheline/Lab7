//#include "gtest/gtest.h"

#include "Parser.h"
#include "MoneyBox.h"

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
	//catch (std::bad_alloc& e)
	//{
	//	parser.PrintError(ErrorMessages::MEMORY_ERROR);
	//}
}

int main(int argc, char** argv)
{
	//testing::InitGoogleTest(&argc, argv);
	//RUN_ALL_TESTS();
	//getchar();

	Execute();
}


