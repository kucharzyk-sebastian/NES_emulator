#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"
#include  "nes/cpu/opcodes/basicExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_BasicExecutor
{
	TEST_CLASS(ASL_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::cpu::opcodes::BasicExecutor be_;
		nes::memory::Memory mem_;


		ASL_Tests() :
			reg_(),
			be_(reg_, mem_)
		{

		}

		TEST_METHOD(ASL_shifts_value_left)
		{

			int8_t res = be_.ASL(int8_t(0b01110111));

			Assert::AreEqual(int8_t(0b11101110), res);
		}

		TEST_METHOD(ASL_resets_carry_flag_when_most_left_bit_equals_zero)
		{
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			be_.ASL(int8_t(0b01000101));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(ASL_sets_carry_flag_when_most_left_bit_equals_one)
		{
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			be_.ASL(int8_t(0b10010101));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(ASL_sets_zero_flag_when_result_equal_zero)
		{
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			be_.ASL(int8_t(0b10000000));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(ASL_resets_zero_flag_when_result_lt_zero)
		{
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			be_.ASL(int8_t(0b01100100));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(ASL_resets_zero_flag_when_result_gt_zero)
		{
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			be_.ASL(int8_t(0b00100101));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(ASL_sets_negative_flag_when_result_lt_zero)
		{
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			be_.ASL(int8_t(0b01000000));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(ASL_resets_negative_flag_when_result_gt_zero)
		{
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			be_.ASL(int8_t(0b00000001));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(ASL_resets_negative_flag_when_result_equal_zero)
		{
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			be_.ASL(int8_t(0b00000000));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}
	};
}
