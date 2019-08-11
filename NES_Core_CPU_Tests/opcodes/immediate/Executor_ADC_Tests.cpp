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
			ie_.LDA(0);
		}

		TEST_METHOD(ADC_adds_value_in_boundaries)
		{
			int8_t val = 5;

			ie_.ADC(val);

			Assert::AreEqual(reg_.A, val);
		}

		TEST_METHOD(ADC_sets_overflow_flag_with_positive_sum_out_of_range_of_int8t)
		{
			ie_.LDA(int8_t(127));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			ie_.ADC(int8_t(1));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(ADC_resets_overflow_flag_with_positive_sum_in_range_of_int8)
		{
			ie_.LDA(int8_t(127));
			ie_.ADC(int8_t(1));
			ie_.LDA(int8_t(0));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			ie_.ADC(int8_t(18));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(ADC_sets_overflow_flag_with_negative_sum_out_of_range_of_int8t)
		{
			ie_.LDA(int8_t(-128));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			ie_.ADC(int8_t(-1));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(ADC_resets_overflow_flag_with_negative_sum_in_range_of_int8t)
		{
			ie_.LDA(int8_t(-128));
			ie_.ADC(int8_t(-1));
			ie_.LDA(int8_t(0));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			ie_.ADC(int8_t(-5));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(ADC_sets_carry_flag_with_any_sum_of_negatives)
		{
			ie_.LDA(int8_t(-5));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			ie_.ADC(int8_t(-6));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(ADC_resets_carry_flag_with_any_sum_of_positives)
		{
			ie_.LDA(int8_t(-128));
			ie_.ADC(int8_t(-127));
			ie_.LDA(int8_t(127));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			ie_.ADC(int8_t(126));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		//TODO sk: think of placing proper description instead of "condition met"
		TEST_METHOD(ADC_sets_carry_flag_with_sum_of_positive_and_negative_when_condition_met)
		{
			ie_.LDA(int8_t(7));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			ie_.ADC(int8_t(-6));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(ADC_resets_carry_flag_with_sum_of_positive_and_negative_when_condition_not_met)
		{
			ie_.LDA(int8_t(7));
			ie_.ADC(int8_t(-6));
			ie_.LDA(int8_t(3));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			ie_.ADC(int8_t(-5));
			
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(ADC_sets_negative_flag_for_negative_result)
		{
			ie_.LDA(int8_t(5));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.ADC(int8_t(-10));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(ADC_resets_negative_flag_for_positive_result)
		{
			ie_.LDA(int8_t(-4));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.ADC(int8_t(5));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(ADC_resets_negative_flag_for_zero_result)
		{
			ie_.LDA(int8_t(-5));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.ADC(int8_t(5));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}


		TEST_METHOD(ADC_sets_zero_flag_for_zero_result)
		{
			ie_.LDA(int8_t(3));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.ADC(int8_t(-3));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(ADC_resets_zero_flag_for_positive_result)
		{
			ie_.LDA(int8_t(0));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.ADC(int8_t(8));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(ADC_resets_zero_flag_for_negative_result)
		{
			ie_.LDA(int8_t(0));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.ADC(int8_t(-3));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}
	};
}
