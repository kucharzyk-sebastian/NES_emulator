#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"
#include  "nes/cpu/opcodes/accumulatorExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_AccumulatorExecutor
{
	TEST_CLASS(LSR_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::cpu::opcodes::AccumulatorExecutor ae_;
		nes::memory::Memory mem_;


		LSR_Tests() :
			reg_(),
			ae_(reg_, mem_)
		{

		}

		TEST_METHOD(LSR_shifts_A_register_right)
		{
			reg_.A = int8_t(0b10100111);
			Assert::AreNotEqual(int8_t(0b01010011), reg_.A);

			ae_.LSR();

			Assert::AreEqual(int8_t(0b01010011), reg_.A);
		}

		TEST_METHOD(LSR_resets_carry_flag_when_most_right_bit_equals_zero)
		{
			reg_.A = int8_t(0b01000100);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			ae_.LSR();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(LSR_sets_carry_flag_when_most_right_bit_equals_one)
		{
			reg_.A = int8_t(0b10010101);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			ae_.LSR();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(LSR_sets_zero_flag_when_result_equal_zero)
		{
			reg_.A = int8_t(0b00000001);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ae_.LSR();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(LSR_resets_zero_flag_when_result_gt_zero)
		{
			reg_.A = int8_t(0b00100101);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ae_.LSR();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(LSR_resets_negative_flag_when_result_gt_zero)
		{
			reg_.A = int8_t(0b00011001);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ae_.LSR();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(LSR_resets_negative_flag_when_result_equal_zero)
		{
			reg_.A = int8_t(0b00000001);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ae_.LSR();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}
	};
}
