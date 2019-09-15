#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodes/immediateExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_ImmediateExecutor
{
	TEST_CLASS(LDX_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::opcodes::ImmediateExecutor ie_;


		LDX_Tests() :
			reg_(),
			ie_(reg_, mem_)
		{
		}

		TEST_METHOD(LDX_loads_value_to_X_register)
		{
			int8_t val = 3;

			ie_.LDX(val);

			Assert::AreEqual(val, reg_.X);
		}

		TEST_METHOD(LDX_does_not_change_any_flags_when_not_needed)
		{
			auto flags = reg_.PS;

			ie_.LDX(int8_t(3));

			Assert::IsTrue(reg_.PS == flags);
		}

		TEST_METHOD(LDX_sets_zero_flag_for_zero)
		{
			reg_.X = int8_t(3);
			Assert::IsFalse(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.LDX(int8_t(0));

			Assert::IsTrue(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(LDX_resets_zero_flag_for_positive)
		{
			reg_.X = int8_t(0);
			reg_.PS.set(static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.LDX(int8_t(3));

			Assert::IsFalse(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(LDX_resets_zero_flag_for_negative)
		{
			reg_.X = int8_t(0);
			reg_.PS.set(static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.LDX(int8_t(-2));

			Assert::IsFalse(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(LDX_sets_negative_flag_for_negative_number)
		{
			reg_.X = int8_t(3);
			Assert::IsFalse(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.LDX(int8_t(-2));

			Assert::IsTrue(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(LDX_resets_negative_flag_for_positive)
		{
			reg_.X = int8_t(-2);
			reg_.PS.set(static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.LDX(int8_t(3));

			Assert::IsFalse(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(LDX_resets_negative_flag_for_zero)
		{
			reg_.X = int8_t(-2);
			reg_.PS.set(static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.LDX(int8_t(0));

			Assert::IsFalse(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}
	};
}
