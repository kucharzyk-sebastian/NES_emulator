#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(ASL_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::cpu::OpcodesExecutor oe_;
		nes::memory::Memory mem_;


		ASL_Tests() :
			reg_(),
			oe_(reg_, mem_)
		{

		}

		TEST_METHOD(ASL_shifts_register_A_left)
		{
			reg_.A = int8_t(0b01110111);

			oe_.ASL();

			Assert::AreEqual(int8_t(0b11101110), reg_.A);
		}

		TEST_METHOD(ASL_shifts_value_from_memory_left)
		{
			int8_t value = 0b01100101;
			uint16_t address = 0x0001;
			mem_[address] = value;

			oe_.ASL(address);

			Assert::AreEqual(int8_t(0b11001010), mem_[address]);
		}

		TEST_METHOD(ASL_resets_carry_flag_when_most_left_bit_equals_zero)
		{
			reg_.A = int8_t(0b01000101);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			oe_.ASL();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(ASL_sets_carry_flag_when_most_left_bit_equals_one)
		{
			reg_.A = int8_t(0b10010101);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			oe_.ASL();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
		}

		TEST_METHOD(ASL_sets_zero_flag_when_result_equal_zero)
		{
			reg_.A = int8_t(0b10000000);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.ASL();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(ASL_resets_zero_flag_when_result_lt_zero)
		{
			reg_.A = int8_t(0b01100100);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.ASL();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(ASL_resets_zero_flag_when_result_gt_zero)
		{
			reg_.A = int8_t(0b00100101);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.ASL();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(ASL_sets_negative_flag_when_result_lt_zero)
		{
			reg_.A = int8_t(0b01000000);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.ASL();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(ASL_resets_negative_flag_when_result_gt_zero)
		{
			reg_.A = int8_t(0b00000001);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.ASL();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(ASL_resets_negative_flag_when_result_equal_zero)
		{
			reg_.A = int8_t(0b00000000);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.ASL();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}
	};
}
