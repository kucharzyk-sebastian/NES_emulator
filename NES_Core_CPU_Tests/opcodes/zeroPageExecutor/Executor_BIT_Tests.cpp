#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodes/zeroPageExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_ZeroPageExecutor
{
	TEST_CLASS(BIT_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::opcodes::ZeroPageExecutor zpe_;
		uint8_t page = 0x0000;


		BIT_Tests() :
			reg_(),
			zpe_(reg_, mem_)
		{
		}

		TEST_METHOD(BIT_sets_zero_flag_when_logical_and_of_A_register_and_value_from_memory_equals_to_zero)
		{
			int8_t val = 0b10110110;
			reg_.A = 0b01000001;
			uint8_t address = 0x06;
			mem_[page + address] = val;
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			zpe_.BIT(address);

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(BIT_resets_zero_flag_when_logical_and_of_A_register_and_value_from_memory_gt_zero)
		{
			int8_t val = 0b10110110;
			reg_.A = 0b01000111;
			uint8_t address = 0x51;
			mem_[page + address] = val;
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			zpe_.BIT(address);

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(BIT_resets_zero_flag_when_logical_and_of_A_register_and_value_from_memory_lt_zero)
		{
			int8_t val = 0b10110110;
			reg_.A = 0b11010011;
			uint8_t address = 0xc8;
			mem_[page + address] = val;
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			zpe_.BIT(address);

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(BIT_sets_negative_flag_when_logical_and_of_A_register_and_value_from_memory_lt_zero)
		{
			int8_t val = 0b10010110;
			reg_.A = 0b11010001;
			uint8_t address = 0xa2;
			mem_[page + address] = val;
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			zpe_.BIT(address);

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(BIT_resets_negative_flag_when_logical_and_of_A_register_and_value_from_memory_gt_zero)
		{
			int8_t val = 0b10010110;
			reg_.A = 0b01010010;
			uint8_t address = 0x06;
			mem_[page + address] = val;
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			zpe_.BIT(address);

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(BIT_resets_negative_flag_when_logical_and_of_A_register_and_value_from_memory_equals_to_zero)
		{
			int8_t val = 0b00000101;
			reg_.A = 0b01110000;
			uint8_t address = 0x98;
			mem_[page + address] = val;
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			zpe_.BIT(address);

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(BIT_sets_overflow_flag_when_6th_bit_of_result_equals_to_one)
		{
			int8_t val = 0b01000101;
			reg_.A = 0b01010000;
			uint8_t address = 0xfc;
			mem_[page + address] = val;
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			zpe_.BIT(address);

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(BIT_resets_overflow_flag_when_6th_bit_of_result_equals_to_zzero)
		{
			int8_t val = 0b11100101;
			reg_.A = 0b10110011;
			uint8_t address = 0xba;
			mem_[page + address] = val;
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			zpe_.BIT(address);

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}
	};
}
