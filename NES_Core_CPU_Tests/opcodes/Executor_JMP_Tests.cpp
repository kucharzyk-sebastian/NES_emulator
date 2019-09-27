#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(JMP_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor oe_;


		JMP_Tests() :
			reg_(),
			oe_(reg_, mem_)
		{
			reg_.PC = 0x0600;
		}

		TEST_METHOD(JMP_absolute_copy_passed_value_to_Program_Counter)
		{
			uint16_t value = 0x2137;

			oe_.JMP_absolute(value);

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(value)), int(reg_.PC));
		}

		TEST_METHOD(JMP_indirect_copy_2_bytes_of_memory_from_passed_address)
		{
			uint16_t address = 0xda75;
			mem_[address] = 0x23;
			mem_[address + 1] = 0xac;

			oe_.JMP_indirect(address);

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0xac23)), int(reg_.PC));
		}

		TEST_METHOD(JMP_indirect_copy_2_bytes_of_memory_from_passed_address_crossing_page)
		{
			uint16_t address = 0xdaFF;
			mem_[address] = 0x97;
			mem_[0xda00] = 0xfd;

			oe_.JMP_indirect(address);

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0xfd97)), int(reg_.PC));
		}
	};
}
