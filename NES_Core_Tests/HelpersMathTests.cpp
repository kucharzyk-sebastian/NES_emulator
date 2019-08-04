#include "pch.h"
#include "helpers/math.h"

/*
If sum of two positive numbers gives the negative value or sum of two negative gives the positive value then overflow occurs.
*/
TEST(MathHelpers_, isOverflow_returns_false_for_two_positives_with_sum_in_range_of_int8t)
{
	int8_t val1 = 3;
	int8_t val2 = 25;
	int8_t res = val1 + val2;
	EXPECT_FALSE(helpers::math::isOverflow(val1, val2, res));
}

TEST(MathHelpers_, isOverflow_returns_false_for_two_positives_with_sum_in_range_of_int8t_edge_case)
{
	int8_t val1 = 10;
	int8_t val2 = 117;
	int8_t res = val1 + val2;
	EXPECT_FALSE(helpers::math::isOverflow(val1, val2, res));
}

TEST(MathHelpers_, isOverflow_returns_false_for_two_negatives_with_sum_in_range_of_int8t)
{
	int8_t val1 = -51;
	int8_t val2 = -13;
	int8_t res = val1 + val2;
	EXPECT_FALSE(helpers::math::isOverflow(val1, val2, res));
}

TEST(MathHelpers_, isOverflow_returns_false_for_two_negatives_with_sum_in_range_of_int8t_edge_case)
{
	int8_t val1 = -10;
	int8_t val2 = -118;
	int8_t res = val1 + val2;
	EXPECT_FALSE(helpers::math::isOverflow(val1, val2, res));
}

TEST(MathHelpers_, isOverflow_returns_false_for_negative_and_positive_with_sum_in_range_of_int8t)
{
	int8_t val1 = -8;
	int8_t val2 = 65;
	int8_t res = val1 + val2;
	EXPECT_FALSE(helpers::math::isOverflow(val1, val2, res));
}

TEST(MathHelpers_, isOverflow_returns_true_for_two_positives_with_sum_out_of_range_of_int8t)
{
	int8_t val1 = 120;
	int8_t val2 = 25;
	int8_t res = val1 + val2;
	EXPECT_TRUE(helpers::math::isOverflow(val1, val2, res));
}

TEST(MathHelpers_, isOverflow_returns_true_for_two_positives_with_sum_out_of_range_of_int8t_edge_case)
{
	int8_t val1 = 120;
	int8_t val2 = 18;
	int8_t res = val1 + val2;
	EXPECT_TRUE(helpers::math::isOverflow(val1, val2, res));
}

TEST(MathHelpers_, isOverflow_returns_true_for_two_negatives_with_sum_out_of_range_of_int8t)
{
	int8_t val1 = -55;
	int8_t val2 = -100;
	int8_t res = val1 + val2;
	EXPECT_TRUE(helpers::math::isOverflow(val1, val2, res));
}

TEST(MathHelpers_, isOverflow_returns_true_for_two_negatives_with_sum_out_of_range_of_int8t_edge_case)
{
	int8_t val1 = -29;
	int8_t val2 = -100;
	int8_t res = val1 + val2;
	EXPECT_TRUE(helpers::math::isOverflow(val1, val2, res));
}


/*
If sum of two n-bit numbers in 2s complement gives result of (n+1)-bits then carry bit occurs.
*/
TEST(MathHelpers_, isCarry_returns_false_for_two_positives_with_sum_in_8bit_range)
{
	int8_t val1 = 11;
	int8_t val2 = 35;
	EXPECT_FALSE(helpers::math::isCarry(val1, val2));
}

TEST(MathHelpers_, isCarry_returns_false_for_two_positives_with_sum_in_8bit_range_edge_case)
{
	int8_t val1 = 127;
	int8_t val2 = 127;
	EXPECT_FALSE(helpers::math::isCarry(val1, val2));
}

TEST(MathHelpers_, isCarry_returns_false_for_zero_and_positive_with_sum_in_8bit_range)
{
	int8_t val1 = 127;
	int8_t val2 = 0;
	EXPECT_FALSE(helpers::math::isCarry(val1, val2));
}


TEST(MathHelpers_, isCarry_returns_false_for_zero_and_negative_with_sum_in_8bit_range)
{
	int8_t val1 = -1;
	int8_t val2 = 0;
	EXPECT_FALSE(helpers::math::isCarry(val1, val2));
}

TEST(MathHelpers_, isCarry_returns_true_for_two_negatives_with_sum_exceeding_8bit_range)
{
	int8_t val1 = -5;
	int8_t val2 = -16;
	EXPECT_TRUE(helpers::math::isCarry(val1, val2));
}

TEST(MathHelpers_, isCarry_returns_true_for_two_negatives_with_sum_exceeding_8bit_range_edge_case)
{
	int8_t val1 = -128;
	int8_t val2 = -128;
	EXPECT_TRUE(helpers::math::isCarry(val1, val2));
}

TEST(MathHelpers_, isCarry_returns_true_for_negative_and_positive_with_sum_exceeding_8bit)
{
	int8_t val1 = 21;
	int8_t val2 = -20;
	EXPECT_TRUE(helpers::math::isCarry(val1, val2));
}

TEST(MathHelpers_, isCarry_returns_true_for_negative_and_positive_with_sum_exceeding_8bit_edge_case)
{
	int8_t val1 = 1;
	int8_t val2 = -1;
	EXPECT_TRUE(helpers::math::isCarry(val1, val2));

	val1 = -127;
	val2 = 127;
	EXPECT_TRUE(helpers::math::isCarry(val1, val2));
}
