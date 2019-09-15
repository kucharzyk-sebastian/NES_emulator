#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodes/immediateExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_ImmediateExecutor
{
	TEST_CLASS(LDY_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::opcodes::ImmediateExecutor ie_;


		LDY_Tests() :
			reg_(),
			ie_(reg_, mem_)
		{
		}

		TEST_METHOD(LDY_loads_value_to_Y_register)
		{
			int8_t val = 3;

			ie_.LDY(val);

			Assert::AreEqual(reg_.Y, val);
		}

		TEST_METHOD(LDY_does_not_change_any_flags_when_not_needed)
		{
			auto flags = reg_.PS;

			ie_.LDY(uint8_t(3));

			Assert::IsTrue(reg_.PS == flags);
		}

		TEST_METHOD(LDY_sets_zero_flag_for_zero)
		{
			ie_.LDY(uint8_t(3));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.LDY(uint8_t(0));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(LDY_resets_zero_flag_for_positive)
		{
			ie_.LDY(uint8_t(0));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.LDY(uint8_t(3));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(LDY_resets_zero_flag_for_negative)
		{
			ie_.LDY(uint8_t(0));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.LDY(uint8_t(-2));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(LDY_sets_negative_flag_for_negative_number)
		{
			ie_.LDY(uint8_t(3));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.LDY(uint8_t(-2));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(LDY_resets_negative_flag_for_positive)
		{
			ie_.LDY(uint8_t(-2));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.LDY(uint8_t(3));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(LDY_resets_negative_flag_for_zero)
		{
			ie_.LDY(uint8_t(-2));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.LDY(uint8_t(0));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}
	};
}
