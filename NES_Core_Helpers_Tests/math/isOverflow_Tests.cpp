#include "CppUnitTest.h"
#include "helpers/math.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Math_Tests
{
	/*
		If sum of two positive numbers gives the negative value
		OR
		sum of two negative gives the positive value
		OR
		difference of negative and positive where |negative| > positve gives the positive value 
		OR
		difference of negative and positive where |negative| < positve gives the negative value
		THEN
		overflow occurs
	*/
	TEST_CLASS(isOverflow_Tests)
	{
	public:
		TEST_METHOD(isOverflow_returns_false_for_two_positives_with_sum_in_range_of_int8t)
		{
			int8_t val1 = 3;
			int8_t val2 = 25;
			Assert::IsFalse(helpers::math::isOverflow(val1, val2));
		}

		TEST_METHOD(isOverflow_returns_false_for_two_positives_with_sum_in_range_of_int8t_edge_case)
		{
			int8_t val1 = 10;
			int8_t val2 = 117;
			Assert::IsFalse(helpers::math::isOverflow(val1, val2));
		}

		TEST_METHOD(isOverflow_returns_false_for_two_negatives_with_sum_in_range_of_int8t)
		{
			int8_t val1 = -51;
			int8_t val2 = -13;
			Assert::IsFalse(helpers::math::isOverflow(val1, val2));
		}

		TEST_METHOD(isOverflow_returns_false_for_two_negatives_with_sum_in_range_of_int8t_edge_case)
		{
			int8_t val1 = -10;
			int8_t val2 = -118;
			Assert::IsFalse(helpers::math::isOverflow(val1, val2));
		}

		TEST_METHOD(isOverflow_returns_false_for_negative_and_positive_with_sum_in_range_of_int8t)
		{
			int8_t val1 = -8;
			int8_t val2 = 65;
			Assert::IsFalse(helpers::math::isOverflow(val1, val2));
		}

		TEST_METHOD(isOverflow_returns_true_for_two_positives_with_sum_out_of_range_of_int8t)
		{
			int8_t val1 = 120;
			int8_t val2 = 25;
			Assert::IsTrue(helpers::math::isOverflow(val1, val2));
		}

		TEST_METHOD(isOverflow_returns_true_for_two_positives_with_sum_out_of_range_of_int8t_edge_case)
		{
			int8_t val1 = 120;
			int8_t val2 = 18;
			Assert::IsTrue(helpers::math::isOverflow(val1, val2));
		}

		TEST_METHOD(isOverflow_returns_true_for_two_negatives_with_sum_out_of_range_of_int8t)
		{
			int8_t val1 = -55;
			int8_t val2 = -100;
			Assert::IsTrue(helpers::math::isOverflow(val1, val2));
		}

		TEST_METHOD(isOverflow_returns_true_for_two_negatives_with_sum_out_of_range_of_int8t_edge_case)
		{
			int8_t val1 = -29;
			int8_t val2 = -100;
			Assert::IsTrue(helpers::math::isOverflow(val1, val2));
		}
	};
}
