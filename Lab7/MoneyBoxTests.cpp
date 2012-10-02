#include "gtest/gtest.h"
#include "TList.h"
#include "MoneyBox.h"
#include "Parser.h"

TEST(MoneyBoxTest, ShouldFindMinMaxIfWeightIsZero)
{
	TList<Coin> coins;
	coins.Add(Coin(1, 1));
	coins.Add(Coin(5, 2));

	MoneyBox moneyBox;
	MinMax result = moneyBox.FindMinMaxSum(0, &coins);

	ASSERT_EQ(0, result.min);
	ASSERT_EQ(0, result.max);
}

TEST(MoneyBoxTest, ShouldFindMinMaxIfHasOneGoodCoin)
{
	TList<Coin> coins;
	coins.Add(Coin(3, 1));

	MoneyBox moneyBox;
	MinMax result = moneyBox.FindMinMaxSum(1, &coins);

	ASSERT_EQ(3, result.min);
	ASSERT_EQ(3, result.max);
}

TEST(MoneyBoxTest, ShouldFindMinMaxIfHasOneGoodCoin2)
{
	TList<Coin> coins;
	coins.Add(Coin(3, 2));

	MoneyBox moneyBox;
	MinMax result = moneyBox.FindMinMaxSum(10, &coins);

	ASSERT_EQ(15, result.min);
	ASSERT_EQ(15, result.max);
}

TEST(MoneyBoxTest, ShouldNotFindMinMaxIfHasOneBadCoin)
{
	TList<Coin> coins;
	coins.Add(Coin(3, 2));

	MoneyBox moneyBox;
	MinMax result = moneyBox.FindMinMaxSum(9, &coins);

	ASSERT_EQ(-1, result.min);
	ASSERT_EQ(-1, result.max);
}

TEST(MoneyBoxTest, ShouldFindMinMaxIfHasSeveralCoins)
{
	TList<Coin> coins;
	coins.Add(Coin(1, 1));
	coins.Add(Coin(5, 2));
	coins.Add(Coin(8, 4));

	MoneyBox moneyBox;
	MinMax result = moneyBox.FindMinMaxSum(100, &coins);

	ASSERT_EQ(100, result.min);
	ASSERT_EQ(250, result.max);
}

TEST(MoneyBoxTest, ShouldFindMinMaxMixIfCoinsInResult)
{
	TList<Coin> coins;
	coins.Add(Coin(5, 1));
	coins.Add(Coin(7, 2));
	coins.Add(Coin(16, 3));
	coins.Add(Coin(2, 4));

	MoneyBox moneyBox;
	MinMax result = moneyBox.FindMinMaxSum(10, &coins);

	ASSERT_EQ(11, result.min);
	ASSERT_EQ(53, result.max);
}

TEST(MoneyBoxTest, ShouldFindMinMaxIfBigWeight)
{
	TList<Coin> coins;
	coins.Add(Coin(5, 1));
	coins.Add(Coin(7, 2));
	coins.Add(Coin(16, 3));
	coins.Add(Coin(2, 4));

	MoneyBox moneyBox;
	MinMax result = moneyBox.FindMinMaxSum(9999, &coins);

	ASSERT_EQ(5010, result.min);
	ASSERT_EQ(53328, result.max);
}

TEST(ParserTest, ShouldReadInfoFromFile)
{
	FILE* input = fopen("Tests/in", "w");
	fprintf(input, "%d %d\n", 1000, 7000);
	fprintf(input, "%d\n", 4);
	fprintf(input, "%d %d\n", 10, 70);
	fprintf(input, "%d %d\n", 23, 12);
	fprintf(input, "%d %d\n", 55, 12);
	fprintf(input, "%d %d\n", 2, 3);
	fclose(input);

	input = fopen("Tests/in", "r");
	Parser parser;
	Problem problem = parser.ReadFromFile(input);

	ASSERT_EQ(6000, problem.weight);
	ASSERT_EQ(4, problem.coins->GetCount());
	ASSERT_EQ(10, problem.coins->GetElement(0).price);
	ASSERT_EQ(70, problem.coins->GetElement(0).weight);
	ASSERT_EQ(23, problem.coins->GetElement(1).price);
	ASSERT_EQ(12, problem.coins->GetElement(1).weight);
	ASSERT_EQ(55, problem.coins->GetElement(2).price);
	ASSERT_EQ(12, problem.coins->GetElement(2).weight);
	ASSERT_EQ(2, problem.coins->GetElement(3).price);
	ASSERT_EQ(3, problem.coins->GetElement(3).weight);

	fclose(input);
}