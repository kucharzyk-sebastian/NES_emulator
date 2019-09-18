#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodes/zeroPageExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_ZeroPageExecutor
{
	TEST_CLASS(AND_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::opcodes::ZeroPageExecutor zpe_;
		uint8_t page = 0x0000;


		AND_Tests() :
			reg_(),
			zpe_(reg_, mem_)
		{
		}

		TEST_METHOD(AND_performs_binary_and_operation_between_value_from_memory_and_A_register)
		{
			reg_.A = 0b01010011;
			int8_t val = 0b10110110;
			uint8_t address = 0xAA;
			mem_[page + address] = val;

			zpe_.AND(address);

			Assert::AreEqual(int8_t(0b00010010), reg_.A);
		}

		TEST_METHOD(AND_performs_binary_and_operation_between_value_from_memory_and_A_register_min_address)
		{
			reg_.A = 0b00111011;
			int8_t val = 0b10010111;
			uint8_t address = 0x00;
			mem_[page + address] = val;

			zpe_.AND(address);

			Assert::AreEqual(int8_t(0b00010011), reg_.A);
		}

		TEST_METHOD(AND_performs_binary_and_operation_between_value_from_memory_and_A_register_max_address)
		{
			reg_.A = 0b11011011;
			int8_t val = 0b00111100;
			uint8_t address = 0xFF;
			mem_[page + address] = val;

			zpe_.AND(address);

			Assert::AreEqual(int8_t(0b00011000), reg_.A);
		}
	};
}
