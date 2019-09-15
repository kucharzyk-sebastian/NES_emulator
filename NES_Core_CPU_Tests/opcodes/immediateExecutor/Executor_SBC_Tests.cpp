#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/cpu/opcodes/immediateExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_ImmediateExecutor
{
	TEST_CLASS(SBC_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::cpu::opcodes::ImmediateExecutor ie_;


		SBC_Tests() :
			reg_(),
			ie_(reg_)
		{
			ie_.LDA(0);
		}

		TEST_METHOD(SBC_subtracts_value_in_boundaries_with_carry_flag_set)
		{
			ie_.LDA(int8_t(15));
			/*Carry set to True in case of SBC means reverse borrow. If not set then it indicates that one bit was borrowed so result is decreased by one */
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));

			ie_.SBC(int8_t(5));

			Assert::AreEqual(reg_.A, int8_t(10));
		}

		TEST_METHOD(SBC_subtracts_value_in_boundaries_and_decrement_by_one_without_carry_flag_set)
		{
			ie_.LDA(int8_t(10));

			ie_.SBC(int8_t(7));

			Assert::AreEqual(reg_.A, int8_t(2));
		}

		TEST_METHOD(SBC_sets_overflow_flag_with_positive_and_negative_subtraction_out_of_range)
		{
			ie_.LDA(int8_t(120));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			ie_.SBC(int8_t(-10));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(SBC_sets_overflow_flag_with_positive_and_negative_subtraction_out_of_range_edge_case)
		{
			ie_.LDA(int8_t(127));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			ie_.SBC(int8_t(-1));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(SBC_resets_overflow_flag_with_positive_and_negative_subtraction_in_range)
		{
			ie_.LDA(int8_t(15));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			ie_.SBC(int8_t(-10));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(SBC_resets_overflow_flag_with_positive_and_zero_subtraction)
		{
			ie_.LDA(int8_t(127));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			ie_.SBC(int8_t(0));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(SBC_sets_overflow_flag_with_negative_and_positive_subtraction_out_of_range)
		{
			ie_.LDA(int8_t(-123));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			ie_.SBC(int8_t(20));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(SBC_sets_overflow_flag_with_negative_and_positive_subtraction_out_of_range_edge_case)
		{
			ie_.LDA(int8_t(-128));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			ie_.SBC(int8_t(1));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(SBC_resets_overflow_flag_with_negative_and_positive_subtraction_in_range)
		{
			ie_.LDA(int8_t(-23));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			ie_.SBC(int8_t(5));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(SBC_resets_overflow_flag_with_negative_and_zero_subtraction)
		{
			ie_.LDA(int8_t(-128));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			ie_.SBC(int8_t(0));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(SBC_resets_carry_flag_with_unsigned_register_A_lt_input)
		{
			ie_.LDA(uint8_t(7));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			ie_.SBC(uint8_t(8));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(SBC_sets_carry_flag_with_unsigned_register_A_gt_input)
		{
			ie_.LDA(uint8_t(9));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			ie_.SBC(uint8_t(8));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(SBC_sets_carry_flag_with_unsigned_register_A_equal_input)
		{
			ie_.LDA(uint8_t(10));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			ie_.SBC(uint8_t(10));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(SBC_sets_negative_flag_for_negative_result)
		{
			ie_.LDA(int8_t(5));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.SBC(int8_t(6));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(SBC_resets_negative_flag_for_positive_result)
		{
			ie_.LDA(int8_t(-4));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.SBC(int8_t(-5));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(SBC_resets_negative_flag_for_zero_result)
		{
			ie_.LDA(int8_t(-5));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.SBC(int8_t(-5));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}


		TEST_METHOD(SBC_sets_zero_flag_for_zero_result)
		{
			ie_.LDA(int8_t(3));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.SBC(int8_t(3));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(SBC_resets_zero_flag_for_positive_result)
		{
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.SBC(int8_t(-8));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(SBC_resets_zero_flag_for_negative_result)
		{
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.SBC(int8_t(3));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(SBC_adds_carry_bit_to_result_when_set_and_resets_carry_when_register_A_lt_input)
		{
			ie_.LDA(int8_t(0x01));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			ie_.SBC(int8_t(0x04));

			Assert::AreEqual(reg_.A, int8_t(0xfd));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(SBC_adds_carry_bit_to_result_when_set_and_sets_carry_again_when_register_A_gt_input)
		{
			ie_.LDA(int8_t(0x06));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			ie_.SBC(int8_t(0x04));

			Assert::AreEqual(reg_.A, int8_t(0x02));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(SBC_adds_carry_bit_to_result_when_set_and_sets_carry_again_when_register_A_equal_input)
		{
			ie_.LDA(int8_t(0x07));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			ie_.SBC(int8_t(0x07));

			Assert::AreEqual(reg_.A, int8_t(0x00));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(SBC_does_not_add_carry_bit_when_not_set_and_resets_carry_when_register_A_equal_input)
		{
			ie_.LDA(int8_t(0x10));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			ie_.SBC(int8_t(0x10));

			Assert::AreEqual(reg_.A, int8_t(0xFF));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(SBC_does_not_add_carry_bit_when_not_set_and_resets_carry_when_register_A_lt_input)
		{
			ie_.LDA(int8_t(0xaa));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			ie_.SBC(int8_t(0xab));

			Assert::AreEqual(reg_.A, int8_t(0xFE));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(SBC_does_not_add_carry_bit_when_not_set_and_sets_carry_when_register_A_gt_input)
		{
			ie_.LDA(int8_t(0xc0));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			ie_.SBC(int8_t(0xbf));

			Assert::AreEqual(reg_.A, int8_t(0x00));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

	};
}
