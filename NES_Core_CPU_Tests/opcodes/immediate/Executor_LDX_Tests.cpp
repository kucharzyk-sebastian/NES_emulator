#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/cpu/opcodes/immediate/executor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_Immediate_Executor
{
	TEST_CLASS(LDX_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::cpu::opcodes::immediate::Executor ie_;


		LDX_Tests() :
			reg_(),
			ie_(reg_)
		{
		}

		TEST_METHOD(LDX_loads_value_to_X_register)
		{
			int8_t val = 3;

			ie_.LDX(val);

			Assert::AreEqual(reg_.X, val);
		}

		TEST_METHOD(LDX_does_not_change_any_flags_when_not_needed)
		{
			auto flags = reg_.PS;

			ie_.LDX(uint8_t(3));

			Assert::IsTrue(reg_.PS == flags);
		}

		TEST_METHOD(LDX_sets_zero_flag_for_zero)
		{
			ie_.LDX(uint8_t(3));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.LDX(uint8_t(0));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(LDX_resets_zero_flag_for_positive)
		{
			ie_.LDX(uint8_t(0));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.LDX(uint8_t(3));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(LDX_resets_zero_flag_for_negative)
		{
			ie_.LDX(uint8_t(0));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.LDX(uint8_t(-2));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(LDX_sets_negative_flag_for_negative_number)
		{
			ie_.LDX(uint8_t(3));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.LDX(uint8_t(-2));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(LDX_resets_negative_flag_for_positive)
		{
			ie_.LDX(uint8_t(-2));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.LDX(uint8_t(3));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(LDX_resets_negative_flag_for_zero)
		{
			ie_.LDX(uint8_t(-2));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.LDX(uint8_t(0));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}
	};
}
