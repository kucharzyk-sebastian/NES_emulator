#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(SBC_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor oe_;


		SBC_Tests() :
			reg_(),
			oe_(reg_, mem_)
		{
		}

		TEST_METHOD(SBC_subtracts_immediate_value_in_boundaries_with_carry_flag_set)
		{
			reg_.A = int8_t(15);
			/*Carry set to True in case of SBC means reverse borrow. If not set then it indicates that one bit was borrowed so result is decreased by one */
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));

			oe_.SBC(int8_t(5));

			Assert::AreEqual(int8_t(10), reg_.A);
		}


		TEST_METHOD(SBC_subtracts_value_from_memory_in_boundaries_with_carry_flag_set)
		{
			reg_.A = int8_t(15);
			uint16_t address = 0x1304;
			mem_[address] = 5;
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));

			oe_.SBC(address);

			Assert::AreEqual(int8_t(10), reg_.A);
		}

		TEST_METHOD(SBC_subtracts_value_in_boundaries_and_decrement_by_one_without_carry_flag_set)
		{
			reg_.A = int8_t(10);

			oe_.SBC(int8_t(7));

			Assert::AreEqual(int8_t(2), reg_.A);
		}

		TEST_METHOD(SBC_sets_overflow_flag_with_positive_and_negative_subtraction_out_of_range)
		{
			reg_.A = int8_t(120);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			oe_.SBC(int8_t(-10));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(SBC_sets_overflow_flag_with_positive_and_negative_subtraction_out_of_range_edge_case)
		{
			reg_.A = int8_t(127);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			oe_.SBC(int8_t(-1));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(SBC_resets_overflow_flag_with_positive_and_negative_subtraction_in_range)
		{
			reg_.A = int8_t(15);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			oe_.SBC(int8_t(-10));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(SBC_resets_overflow_flag_with_positive_and_zero_subtraction)
		{
			reg_.A = int8_t(127);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			oe_.SBC(int8_t(0));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(SBC_sets_overflow_flag_with_negative_and_positive_subtraction_out_of_range)
		{
			reg_.A = int8_t(-123);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			oe_.SBC(int8_t(20));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(SBC_sets_overflow_flag_with_negative_and_positive_subtraction_out_of_range_edge_case)
		{
			reg_.A = int8_t(-128);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			oe_.SBC(int8_t(1));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(SBC_resets_overflow_flag_with_negative_and_positive_subtraction_in_range)
		{
			reg_.A = int8_t(-23);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			oe_.SBC(int8_t(5));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(SBC_resets_overflow_flag_with_negative_and_zero_subtraction)
		{
			reg_.A = int8_t(-128);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			oe_.SBC(int8_t(0));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(SBC_resets_carry_flag_with_unsigned_register_A_lt_input)
		{
			reg_.A = uint8_t(7);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			oe_.SBC(int8_t(8));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(SBC_sets_carry_flag_with_unsigned_register_A_gt_input)
		{
			reg_.A = uint8_t(9);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			oe_.SBC(int8_t(8));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(SBC_sets_carry_flag_with_unsigned_register_A_equal_input)
		{
			reg_.A = uint8_t(10);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			oe_.SBC(int8_t(10));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(SBC_sets_negative_flag_for_negative_result)
		{
			reg_.A = int8_t(5);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.SBC(int8_t(6));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(SBC_resets_negative_flag_for_positive_result)
		{
			reg_.A = int8_t(-4);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.SBC(int8_t(-5));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(SBC_resets_negative_flag_for_zero_result)
		{
			reg_.A = int8_t(-5);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.SBC(int8_t(-5));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}


		TEST_METHOD(SBC_sets_zero_flag_for_zero_result)
		{
			reg_.A = int8_t(3);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.SBC(int8_t(3));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(SBC_resets_zero_flag_for_positive_result)
		{
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.SBC(int8_t(-8));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(SBC_resets_zero_flag_for_negative_result)
		{
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.SBC(int8_t(3));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(SBC_adds_carry_bit_to_result_when_set_and_resets_carry_when_register_A_lt_input)
		{
			reg_.A = int8_t(0x01);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			oe_.SBC(int8_t(0x04));

			Assert::AreEqual(int8_t(0xfd), reg_.A);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(SBC_adds_carry_bit_to_result_when_set_and_sets_carry_again_when_register_A_gt_input)
		{
			reg_.A = int8_t(0x06);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			oe_.SBC(int8_t(0x04));

			Assert::AreEqual(int8_t(0x02), reg_.A);
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(SBC_adds_carry_bit_to_result_when_set_and_sets_carry_again_when_register_A_equal_input)
		{
			reg_.A = int8_t(0x07);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			oe_.SBC(int8_t(0x07));

			Assert::AreEqual(int8_t(0x00), reg_.A);
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(SBC_does_not_add_carry_bit_when_not_set_and_resets_carry_when_register_A_equal_input)
		{
			reg_.A = int8_t(0x10);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			oe_.SBC(int8_t(0x10));

			Assert::AreEqual(int8_t(0xFF), reg_.A);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(SBC_does_not_add_carry_bit_when_not_set_and_resets_carry_when_register_A_lt_input)
		{
			reg_.A = int8_t(0xaa);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			oe_.SBC(int8_t(0xab));

			Assert::AreEqual(int8_t(0xFE), reg_.A);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(SBC_does_not_add_carry_bit_when_not_set_and_sets_carry_when_register_A_gt_input)
		{
			reg_.A = int8_t(0xc0);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			oe_.SBC(int8_t(0xbf));

			Assert::AreEqual(int8_t(0x00), reg_.A);
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

	};
}
