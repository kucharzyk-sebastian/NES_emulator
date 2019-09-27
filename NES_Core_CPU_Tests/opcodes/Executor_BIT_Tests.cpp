#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(BIT_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor zpe_;


		BIT_Tests() :
			reg_(),
			zpe_(reg_, mem_)
		{
		}

		TEST_METHOD(BIT_sets_zero_flag_when_logical_and_of_A_register_and_value_from_memory_equals_to_zero)
		{
			reg_.A = 0b01000001;
			uint16_t address = 0x0006;
			mem_[address] = int8_t(0b10110110);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			zpe_.BIT(address);

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(BIT_resets_zero_flag_when_logical_and_of_A_register_and_value_from_memory_gt_zero)
		{
			reg_.A = 0b01000111;
			uint16_t address = 0xac51;
			mem_[address] = int8_t(0b10110110);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			zpe_.BIT(address);

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(BIT_resets_zero_flag_when_logical_and_of_A_register_and_value_from_memory_lt_zero)
		{
			reg_.A = int8_t(0b11010011);
			uint16_t address = 0x08c8;
			mem_[address] = int8_t(0b10110110);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			zpe_.BIT(address);

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(BIT_sets_negative_flag_when_logical_and_of_A_register_and_value_from_memory_lt_zero)
		{
			reg_.A = int8_t(0b11010001);
			uint16_t address = 0xcaa2;
			mem_[address] = int8_t(0b10010110);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			zpe_.BIT(address);

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(BIT_resets_negative_flag_when_logical_and_of_A_register_and_value_from_memory_gt_zero)
		{
			reg_.A = 0b01010010;
			uint16_t address = 0x3406;
			mem_[address] = int8_t(0b10010110);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			zpe_.BIT(address);

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(BIT_resets_negative_flag_when_logical_and_of_A_register_and_value_from_memory_equals_to_zero)
		{
			int8_t val = 0b00000101;
			reg_.A = 0b01110000;
			uint16_t address = 0xf098;
			mem_[address] = val;
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			zpe_.BIT(address);

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(BIT_sets_overflow_flag_when_6th_bit_of_result_equals_to_one)
		{
			int8_t val = 0b01000101;
			reg_.A = 0b01010000;
			uint16_t address = 0xacfc;
			mem_[address] = val;
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			zpe_.BIT(address);

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}

		TEST_METHOD(BIT_resets_overflow_flag_when_6th_bit_of_result_equals_to_zzero)
		{
			reg_.A = int8_t(0b10110011);
			uint16_t address = 0x66ba;
			mem_[address] = int8_t(0b11100101);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			zpe_.BIT(address);

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
		}
	};
}
