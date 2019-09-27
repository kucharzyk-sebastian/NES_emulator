#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(CPX_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor oe_;


		CPX_Tests() :
			reg_(),
			oe_(reg_, mem_)
		{
		}

		TEST_METHOD(CPX_sets_zero_flag_for_X_register_equal_immediate_value)
		{
			int8_t val = 5;
			reg_.X = val;
			reg_.PS.reset(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.CPX(val);

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(CPX_sets_zero_flag_for_X_register_equal_value_from_memory)
		{
			int8_t val = 5;
			reg_.X = val;
			reg_.PS.reset(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.CPX(val);

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(CPX_resets_zero_flag_for_X_register_lt_input)
		{
			reg_.X = int8_t(0);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.CPX(int8_t(3));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(CPX_resets_zero_flag_for_X_register_gt_input)
		{
			reg_.X = int8_t(0);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.CPX(int8_t(-6));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(CPX_sets_carry_flag_for_unsigned_X_register_equal_input)
		{
			reg_.X = int8_t(5);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			oe_.CPX(int8_t(5));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(CPX_sets_carry_flag_for_unsigned_X_register_gt_input)
		{
			reg_.X = int8_t(5);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			oe_.CPX(int8_t(4));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(CPX_resets_carry_flag_for_unsigned_X_register_lt_input)
		{
			reg_.X = int8_t(5);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			oe_.CPX(int8_t(7));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(CPX_sets_negative_flag_for_signed_substraction_of_X_and_input_lt_zero)
		{
			reg_.X = int8_t(1);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.CPX(int8_t(2));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(CPX_resets_negative_flag_for_signed_substraction_of_X_and_input_gt_zero)
		{
			reg_.X = int8_t(-3);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.CPX(int8_t(-4));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(CPX_resets_negative_flag_for_signed_substraction_of_X_and_input_equal_to_zero)
		{
			int8_t value = -7;
			reg_.X = value;
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.CPX(value);

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}
	};
}
