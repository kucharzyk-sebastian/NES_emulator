#include "CppUnitTest.h"
#include "helpers/math.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Math_Tests
{
	/*
		If sum of two n-bit numbers in 2s complement gives result of (n+1)-bits then carry bit occurs.
	*/
	TEST_CLASS(isCarry_Tests)
	{
	public:
		TEST_METHOD(isCarry_returns_false_for_two_positives_with_sum_in_8bit_range)
		{
			int8_t val1 = 11;
			int8_t val2 = 35;
			Assert::IsFalse(helpers::math::isCarry(val1, val2));
		}

		TEST_METHOD(isCarry_returns_false_for_two_positives_with_sum_in_8bit_range_edge_case)
		{
			int8_t val1 = 127;
			int8_t val2 = 127;
			Assert::IsFalse(helpers::math::isCarry(val1, val2));
		}

		TEST_METHOD(isCarry_returns_false_for_zero_and_positive_with_sum_in_8bit_range)
		{
			int8_t val1 = 127;
			int8_t val2 = 0;
			Assert::IsFalse(helpers::math::isCarry(val1, val2));
		}


		TEST_METHOD(isCarry_returns_false_for_zero_and_negative_with_sum_in_8bit_range)
		{
			int8_t val1 = -1;
			int8_t val2 = 0;
			Assert::IsFalse(helpers::math::isCarry(val1, val2));
		}

		TEST_METHOD(isCarry_returns_true_for_two_negatives_with_sum_exceeding_8bit_range)
		{
			int8_t val1 = -5;
			int8_t val2 = -16;
			Assert::IsTrue(helpers::math::isCarry(val1, val2));
		}

		TEST_METHOD(isCarry_returns_true_for_two_negatives_with_sum_exceeding_8bit_range_edge_case)
		{
			int8_t val1 = -128;
			int8_t val2 = -128;
			Assert::IsTrue(helpers::math::isCarry(val1, val2));
		}

		TEST_METHOD(isCarry_returns_true_for_negative_and_positive_with_sum_exceeding_8bit)
		{
			int8_t val1 = 21;
			int8_t val2 = -20;
			Assert::IsTrue(helpers::math::isCarry(val1, val2));
		}

		TEST_METHOD(isCarry_returns_true_for_negative_and_positive_with_sum_exceeding_8bit_edge_case)
		{
			int8_t val1 = 1;
			int8_t val2 = -1;
			Assert::IsTrue(helpers::math::isCarry(val1, val2));

			val1 = -127;
			val2 = 127;
			Assert::IsTrue(helpers::math::isCarry(val1, val2));
		}
	};
} // eof namespace MathTests
