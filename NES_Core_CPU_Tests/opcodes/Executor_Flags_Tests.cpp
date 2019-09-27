#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include  "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(Flags_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor oe_;


		Flags_Tests() :
			reg_(),
			oe_(reg_, mem_)
		{
			reg_.PS.reset();
		}

		TEST_METHOD(CLV_resets_overflow_flag)
		{
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			oe_.CLV();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(SEI_sets_interrupt_disable_flag)
		{
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::InterruptDisable)]);

			oe_.SEI();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::InterruptDisable)]);
		}

		TEST_METHOD(CLI_resets_interrupt_disable_flag)
		{
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::InterruptDisable));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::InterruptDisable)]);

			oe_.CLI();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::InterruptDisable)]);
		}

		TEST_METHOD(SED_sets_decimal_flag)
		{
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Decimal)]);

			oe_.SED();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Decimal)]);
		}

		TEST_METHOD(CLD_resets_decimal_flag)
		{
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Decimal));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Decimal)]);

			oe_.CLD();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Decimal)]);
		}
		
		TEST_METHOD(SEC_sets_carry_flag)
		{
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			oe_.SEC();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(CLC_resets_carry_flag)
		{
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			oe_.CLC();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}
	};
}
