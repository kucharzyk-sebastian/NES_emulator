#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodes/basicExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_BasicExecutor
{
	TEST_CLASS(ADC_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::opcodes::BasicExecutor be_;


		ADC_Tests() :
			reg_(),
			be_(reg_, mem_)
		{
			reg_.A = 0;
		}

		TEST_METHOD(ADC_adds_value_in_boundaries)
		{
			int8_t val = 5;

			be_.ADC(val);

			Assert::AreEqual(val, reg_.A);
		}

		TEST_METHOD(ADC_sets_overflow_flag_with_positive_sum_out_of_range_of_int8t)
		{
			reg_.A = int8_t(127);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			be_.ADC(int8_t(1));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(ADC_resets_overflow_flag_with_positive_sum_in_range_of_int8)
		{
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			be_.ADC(int8_t(18));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(ADC_sets_overflow_flag_with_negative_sum_out_of_range_of_int8t)
		{
			reg_.A = int8_t(-128);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			be_.ADC(int8_t(-1));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(ADC_resets_overflow_flag_with_negative_sum_in_range_of_int8t)
		{
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			be_.ADC(int8_t(-5));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(ADC_sets_carry_flag_with_any_sum_of_negatives)
		{
			reg_.A = int8_t(-5);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			be_.ADC(int8_t(-6));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(ADC_resets_carry_flag_with_any_sum_of_positives)
		{
			reg_.A = int8_t(127);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			be_.ADC(int8_t(126));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		//TODO sk: think of placing proper description instead of "condition met"
		TEST_METHOD(ADC_sets_carry_flag_with_sum_of_positive_and_negative_when_condition_met)
		{
			reg_.A = int8_t(7);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			be_.ADC(int8_t(-6));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(ADC_resets_carry_flag_with_sum_of_positive_and_negative_when_condition_not_met)
		{
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			reg_.A = int8_t(3);
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			be_.ADC(int8_t(-5));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(ADC_sets_negative_flag_for_negative_result)
		{
			reg_.A = int8_t(5);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			be_.ADC(int8_t(-10));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(ADC_resets_negative_flag_for_positive_result)
		{
			reg_.A = int8_t(-4);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			be_.ADC(int8_t(5));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(ADC_resets_negative_flag_for_zero_result)
		{
			reg_.A = int8_t(-5);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			be_.ADC(int8_t(5));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}


		TEST_METHOD(ADC_sets_zero_flag_for_zero_result)
		{
			reg_.A = int8_t(3);
			reg_.PS.reset(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			be_.ADC(int8_t(-3));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(ADC_resets_zero_flag_for_positive_result)
		{
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			be_.ADC(int8_t(8));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(ADC_resets_zero_flag_for_negative_result)
		{
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			be_.ADC(int8_t(-3));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(ADC_adds_carry_bit_to_result_when_set_and_resets_carry_when_sum_in_boundaries)
		{
			reg_.A = int8_t(0x01);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			be_.ADC(int8_t(0x01));

			Assert::AreEqual(int8_t(0x03), reg_.A);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(ADC_adds_carry_bit_to_result_when_set_and_sets_carry_again_when_sum_out_of_boundaries)
		{
			reg_.A = int8_t(0x05);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			be_.ADC(int8_t(0xFE));

			Assert::AreEqual(int8_t(0x04), reg_.A);
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(ADC_adds_carry_bit_to_result_when_set_and_sets_carry_again_when_sum_out_of_boundaries_edge_case)
		{
			reg_.A = int8_t(0x07);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			be_.ADC(int8_t(0xFF));

			Assert::AreEqual(int8_t(0x07), reg_.A);
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(ADC_adds_carry_bit_to_result_when_set_and_sets_carry_again_when_sum_out_of_boundaries_edge_case_2)
		{
			reg_.A = int8_t(0x01);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			be_.ADC(int8_t(0xFE));

			Assert::AreEqual(int8_t(0x00), reg_.A);
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}
	};
}
