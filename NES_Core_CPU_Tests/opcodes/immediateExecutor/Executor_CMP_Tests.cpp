#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/cpu/opcodes/immediateExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_ImmediateExecutor
{
	TEST_CLASS(CMP_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::cpu::opcodes::ImmediateExecutor ie_;


		CMP_Tests() :
			reg_(),
			ie_(reg_)
		{
		}

		TEST_METHOD(CMP_sets_zero_flag_for_equal_values)
		{
			int8_t val = 5;
			ie_.LDA(val);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.CMP(val);

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(CMP_resets_zero_flag_for_A_register_lt_input)
		{
			ie_.LDA(int8_t(0));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.CMP(int8_t(3));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(CMP_resets_zero_flag_for_A_register_gt_input)
		{
			ie_.LDA(int8_t(0));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.CMP(int8_t(-6));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(CMP_sets_carry_flag_for_unsigned_A_register_equal_input)
		{
			ie_.LDA(int8_t(5));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			ie_.CMP(int8_t(5));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(CMP_sets_carry_flag_for_unsigned_A_register_gt_input)
		{
			ie_.LDA(int8_t(5));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			ie_.CMP(int8_t(4));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(CMP_resets_carry_flag_for_unsigned_A_register_lt_input)
		{
			ie_.LDA(int8_t(5));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			ie_.CMP(int8_t(7));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(CMP_sets_negative_flag_for_signed_substraction_of_A_and_input_lt_zero)
		{
			ie_.LDA(int8_t(1));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.CMP(int8_t(2));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(CMP_resets_negative_flag_for_signed_substraction_of_A_and_input_gt_zero)
		{
			ie_.LDA(int8_t(-3));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.CMP(int8_t(-4));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(CMP_resets_negative_flag_for_signed_substraction_of_A_and_input_equal_to_zero)
		{
			int8_t value = -7;
			ie_.LDA(value);
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.CMP(value);

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}
	};
}
