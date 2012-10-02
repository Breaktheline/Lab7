#include "gtest/gtest.h"
#include "TList.h"
#include "MoneyBox.h"

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