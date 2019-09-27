#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(LDX_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor oe_;


		LDX_Tests() :
			reg_(),
			oe_(reg_, mem_)
		{
		}

		TEST_METHOD(LDX_loads_immediate_value_to_X_register)
		{
			int8_t val = 3;

			oe_.LDX(val);

			Assert::AreEqual(val, reg_.X);
		}

		TEST_METHOD(LDX_loads_value_from_memory_to_X_register)
		{
			int8_t val = 3;
			uint16_t address = 0x6502;
			mem_[address] = val;

			oe_.LDX(address);

			Assert::AreEqual(val, reg_.X);
		}

		TEST_METHOD(LDX_does_not_change_any_flags_when_not_needed)
		{
			auto flags = reg_.PS;

			oe_.LDX(int8_t(3));

			Assert::IsTrue(reg_.PS == flags);
		}

		TEST_METHOD(LDX_sets_zero_flag_for_zero)
		{
			reg_.X = int8_t(3);
			Assert::IsFalse(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.LDX(int8_t(0));

			Assert::IsTrue(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(LDX_resets_zero_flag_for_positive)
		{
			reg_.X = int8_t(0);
			reg_.PS.set(static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.LDX(int8_t(3));

			Assert::IsFalse(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(LDX_resets_zero_flag_for_negative)
		{
			reg_.X = int8_t(0);
			reg_.PS.set(static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.LDX(int8_t(-2));

			Assert::IsFalse(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(LDX_sets_negative_flag_for_negative_number)
		{
			reg_.X = int8_t(3);
			Assert::IsFalse(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.LDX(int8_t(-2));

			Assert::IsTrue(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(LDX_resets_negative_flag_for_positive)
		{
			reg_.X = int8_t(-2);
			reg_.PS.set(static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.LDX(int8_t(3));

			Assert::IsFalse(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(LDX_resets_negative_flag_for_zero)
		{
			reg_.X = int8_t(-2);
			reg_.PS.set(static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.LDX(int8_t(0));

			Assert::IsFalse(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}
	};
}
