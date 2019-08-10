#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/cpu/opcodes/immediate/executor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_Immediate_Executor
{
	TEST_CLASS(ADC_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::cpu::opcodes::immediate::Executor ie_;


		ADC_Tests() :
			reg_(),
			ie_(reg_)
		{
		}

		// TODO sk: possibly refactor all doubled ADC once Load instruction is implemented and tested
		TEST_METHOD(ADC_adds_positive_in_boundaries)
		{
			int8_t val = 5;
			ie_.ADC(val);
			Assert::AreEqual(reg_.A, val);
		}

		TEST_METHOD(ADC_adds_negative_in_boundaries)
		{
			int8_t val = -2;
			ie_.ADC(int8_t(val));
			Assert::AreEqual(reg_.A, val);
		}

		TEST_METHOD(ADC_does_not_set_overflow_flag_with_positives_sum_in_range_of_int8)
		{
			ie_.ADC(int8_t(17));
			ie_.ADC(int8_t(1));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(ADC_sets_overflow_flag_with_positives_sum_out_of_range_of_int8t)
		{
			ie_.ADC(int8_t(127));
			ie_.ADC(int8_t(1));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(ADC_sets_overflow_flag_with_negatives_sum_out_of_range_of_int8t)
		{
			ie_.ADC(int8_t(-128));
			ie_.ADC(int8_t(-1));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(ADC_resets_overflow_flag_on_second_try_when_sum_in_range_of_int8)
		{
			ie_.ADC(int8_t(-128));
			ie_.ADC(int8_t(-1));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
			ie_.ADC(int8_t(-1));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(ADC_sets_carry_flag_with_any_sum_of_negatives)
		{
			ie_.ADC(int8_t(-128));
			ie_.ADC(int8_t(-127));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(ADC_does_not_set_carry_flag_with_any_sum_of_positives)
		{
			ie_.ADC(int8_t(127));
			ie_.ADC(int8_t(126));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(ADC_sets_carry_flag_with_sum_of_positive_and_negative_when_condition_met)
		{
			ie_.ADC(int8_t(-4));
			ie_.ADC(int8_t(5));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(ADC_does_not_set_carry_flag_with_sum_of_positive_and_negative_when_condition_not_met)
		{
			ie_.ADC(int8_t(-4));
			ie_.ADC(int8_t(3));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(ADC_resets_carry_flag_on_second_try_when_condition_not_met)
		{
			ie_.ADC(int8_t(-4));
			ie_.ADC(int8_t(5));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
			ie_.ADC(int8_t(2));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(ADC_does_not_set_negative_flag_for_positive_result)
		{
			ie_.ADC(int8_t(5));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(ADC_does_sets_negative_flag_for_negative_result)
		{
			ie_.ADC(int8_t(-10));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(ADC_does_not_set_zero_flag_for_non_zero_results)
		{
			ie_.ADC(int8_t(2));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(ADC_sets_zero_flag_for_zero_results)
		{
			ie_.ADC(int8_t(3));
			ie_.ADC(int8_t(-3));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(ADC_resets_zero_flag_on_second_try)
		{
			ie_.ADC(int8_t(3));
			ie_.ADC(int8_t(-3));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
			ie_.ADC(int8_t(1));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

	};
}
