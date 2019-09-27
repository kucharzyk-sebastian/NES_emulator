#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(NOP_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor oe_;


		NOP_Tests() :
			reg_(),
			oe_(reg_, mem_)
		{
			reg_.PC = 0x0600;
		}

		TEST_METHOD(NOP_increments_Program_Counter)
		{

			oe_.NOP();

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0601)), int(reg_.PC));
		}

		TEST_METHOD(NOP_increments_Program_Counter_twice_in_a_row)
		{

			oe_.NOP();
			oe_.NOP();

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0602)), int(reg_.PC));
		}
	};
}
