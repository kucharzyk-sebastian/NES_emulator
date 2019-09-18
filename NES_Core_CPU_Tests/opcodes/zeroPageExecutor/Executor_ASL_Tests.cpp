#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodes/zeroPageExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_ZeroPageExecutor
{
	TEST_CLASS(ASL_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::opcodes::ZeroPageExecutor zpe_;
		uint8_t page = 0x0000;


		ASL_Tests() :
			reg_(),
			zpe_(reg_, mem_)
		{
		}

		TEST_METHOD(ASL_shifts_value_from_memory_one_place_left)
		{
			int8_t val = 0b10110110;
			uint8_t address = 0xEF;
			mem_[page + address] = val;

			zpe_.ASL(address);

			Assert::AreEqual(int8_t(0b01101100), mem_[page + address]);
		}

		TEST_METHOD(ASL_shifts_value_from_memory_one_place_left_min_address)
		{
			int8_t val = 0b10010111;
			uint8_t address = 0x00;
			mem_[page + address] = val;

			zpe_.ASL(address);

			Assert::AreEqual(int8_t(0b00101110), mem_[page + address]);
		}

		TEST_METHOD(ASL_shifts_value_from_memory_one_place_left_max_address)
		{
			int8_t val = 0b00111100;
			uint8_t address = 0xFF;
			mem_[page + address] = val;

			zpe_.ASL(address);

			Assert::AreEqual(int8_t(0b01111000), mem_[page + address]);
		}
	};
}
