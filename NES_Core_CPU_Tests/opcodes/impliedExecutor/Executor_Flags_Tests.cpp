#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include  "nes/cpu/opcodes/impliedExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_ImpliedExecutor
{
	TEST_CLASS(Flags_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::cpu::opcodes::ImpliedExecutor ie_;


		Flags_Tests() :
			reg_(),
			ie_(reg_)
		{
			auto reg = reg_;
			reg.PS.reset();
			ie_.setRegisters(reg);
		}

		TEST_METHOD(CLV_resets_overflow_flag)
		{
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			ie_.CLV();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(SEI_sets_interrupt_disable_flag)
		{
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::InterruptDisable)]);

			ie_.SEI();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::InterruptDisable)]);
		}

		TEST_METHOD(CLI_resets_interrupt_disable_flag)
		{
			ie_.SEI();
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::InterruptDisable)]);

			ie_.CLI();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::InterruptDisable)]);
		}

		TEST_METHOD(SED_sets_decimal_flag)
		{
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Decimal)]);

			ie_.SED();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Decimal)]);
		}

		TEST_METHOD(CLD_resets_decimal_flag)
		{
			ie_.SED();
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Decimal)]);

			ie_.CLD();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Decimal)]);
		}
		
		TEST_METHOD(SEC_sets_carry_flag)
		{
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			ie_.SEC();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(CLC_resets_carry_flag)
		{
			ie_.SEC();
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			ie_.CLC();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}
	};
}
