#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/cpu/opcodes/immediate/executor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_Immediate_Executor
{
	TEST_CLASS(CPY_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::cpu::opcodes::immediate::Executor ie_;


		CPY_Tests() :
			reg_(),
			ie_(reg_)
		{
		}

		TEST_METHOD(CPY_sets_zero_flag_for_equal_values)
		{
			int8_t val = 5;
			ie_.LDY(val);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.CPY(val);

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(CPY_resets_zero_flag_for_Y_register_lt_input)
		{
			ie_.LDY(int8_t(0));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.CPY(int8_t(3));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(CPY_resets_zero_flag_for_Y_register_gt_input)
		{
			ie_.LDY(int8_t(0));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.CPY(int8_t(-6));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(CPY_sets_carry_flag_for_unsigned_Y_register_equal_input)
		{
			ie_.LDY(int8_t(5));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			ie_.CPY(int8_t(5));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(CPY_sets_carry_flag_for_unsigned_Y_register_gt_input)
		{
			ie_.LDY(int8_t(5));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			ie_.CPY(int8_t(4));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(CPY_resets_carry_flag_for_unsigned_Y_register_lt_input)
		{
			ie_.LDY(int8_t(5));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			ie_.CPY(int8_t(7));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(CPY_sets_negative_flag_for_signed_substraction_of_Y_and_input_lt_zero)
		{
			ie_.LDY(int8_t(1));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.CPY(int8_t(2));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(CPY_resets_negative_flag_for_signed_substraction_of_Y_and_input_gt_zero)
		{
			ie_.LDY(int8_t(-3));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.CPY(int8_t(-4));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(CPY_resets_negative_flag_for_signed_substraction_of_Y_and_input_equal_to_zero)
		{
			int8_t value = -7;
			ie_.LDY(value);
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.CPY(value);

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}
	};
}
