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
			int8_t res = val1 + val2;
			Assert::IsFalse(helpers::math::isOverflow(val1, val2, res));
		}

		TEST_METHOD(isOverflow_returns_false_for_two_positives_with_sum_in_range_of_int8t_edge_case)
		{
			int8_t val1 = 10;
			int8_t val2 = 117;
			int8_t res = val1 + val2;
			Assert::IsFalse(helpers::math::isOverflow(val1, val2, res));
		}

		TEST_METHOD(isOverflow_returns_false_for_two_negatives_with_sum_in_range_of_int8t)
		{
			int8_t val1 = -51;
			int8_t val2 = -13;
			int8_t res = val1 + val2;
			Assert::IsFalse(helpers::math::isOverflow(val1, val2, res));
		}

		TEST_METHOD(isOverflow_returns_false_for_two_negatives_with_sum_in_range_of_int8t_edge_case)
		{
			int8_t val1 = -10;
			int8_t val2 = -118;
			int8_t res = val1 + val2;
			Assert::IsFalse(helpers::math::isOverflow(val1, val2, res));
		}

		TEST_METHOD(isOverflow_returns_false_for_negative_and_positive_with_sum_in_range_of_int8t)
		{
			int8_t val1 = -8;
			int8_t val2 = 65;
			int8_t res = val1 + val2;
			Assert::IsFalse(helpers::math::isOverflow(val1, val2, res));
		}

		TEST_METHOD(isOverflow_returns_true_for_two_positives_with_sum_out_of_range_of_int8t)
		{
			int8_t val1 = 120;
			int8_t val2 = 25;
			int8_t res = val1 + val2;
			Assert::IsTrue(helpers::math::isOverflow(val1, val2, res));
		}

		TEST_METHOD(isOverflow_returns_true_for_two_positives_with_sum_out_of_range_of_int8t_edge_case)
		{
			int8_t val1 = 120;
			int8_t val2 = 18;
			int8_t res = val1 + val2;
			Assert::IsTrue(helpers::math::isOverflow(val1, val2, res));
		}

		TEST_METHOD(isOverflow_returns_true_for_two_negatives_with_sum_out_of_range_of_int8t)
		{
			int8_t val1 = -55;
			int8_t val2 = -100;
			int8_t res = val1 + val2;
			Assert::IsTrue(helpers::math::isOverflow(val1, val2, res));
		}

		TEST_METHOD(isOverflow_returns_true_for_two_negatives_with_sum_out_of_range_of_int8t_edge_case)
		{
			int8_t val1 = -29;
			int8_t val2 = -100;
			int8_t res = val1 + val2;
			Assert::IsTrue(helpers::math::isOverflow(val1, val2, res));
		}

		TEST_METHOD(isOverflow_returns_false_for_two_positives_with_difference_in_range_of_int8t)
		{
			int8_t val1 = 7;
			int8_t val2 = 12;
			int8_t res = val1 - val2;
			Assert::IsFalse(helpers::math::isOverflow(val1, val2, res, true));
		}

		TEST_METHOD(isOverflow_returns_false_for_two_negatives_with_difference_in_range_of_int8t)
		{
			int8_t val1 = -43;
			int8_t val2 = -22;
			int8_t res = val1 - val2;
			Assert::IsFalse(helpers::math::isOverflow(val1, val2, res, true));
		}

		TEST_METHOD(isOverflow_returns_false_for_negative_and_positive_with_difference_in_range_of_int8t)
		{
			int8_t val1 = -9;
			int8_t val2 = 17;
			int8_t res = val1 - val2;
			Assert::IsFalse(helpers::math::isOverflow(val1, val2, res, true));
		}

		TEST_METHOD(isOverflow_returns_false_for_negative_and_positive_with_difference_in_range_of_int8t_edge_case)
		{
			int8_t val1 = -8;
			int8_t val2 = 120;
			int8_t res = val1 - val2;
			Assert::IsFalse(helpers::math::isOverflow(val1, val2, res, true));
		}

		TEST_METHOD(isOverflow_returns_true_for_negative_and_positive_with_difference_out_of_range_of_int8t)
		{
			int8_t val1 = -100;
			int8_t val2 = 50;
			int8_t res = val1 - val2;
			Assert::IsTrue(helpers::math::isOverflow(val1, val2, res, true));
		}

		TEST_METHOD(isOverflow_returns_true_for_negative_and_positive_with_difference_out_of_range_of_int8t_edge_case)
		{
			int8_t val1 = -120;
			int8_t val2 = 19;
			int8_t res = val1 - val2;
			Assert::IsTrue(helpers::math::isOverflow(val1, val2, res, true));
		}

		TEST_METHOD(isOverflow_returns_true_for_positive_and_negative_with_difference_out_of_range_of_int8t)
		{
			int8_t val1 = 110;
			int8_t val2 = -60;
			int8_t res = val1 - val2;
			Assert::IsTrue(helpers::math::isOverflow(val1, val2, res, true));
		}

		TEST_METHOD(isOverflow_returns_true_for_positive_and_negative_with_difference_out_of_range_of_int8t_edge_case)
		{
			int8_t val1 = 120;
			int8_t val2 = -28;
			int8_t res = val1 - val2;
			Assert::IsTrue(helpers::math::isOverflow(val1, val2, res, true));
		}
	};
}
