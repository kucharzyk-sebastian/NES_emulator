#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(RTS_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor oe_;


		RTS_Tests() :
			reg_(),
			oe_(reg_, mem_)
		{
			reg_.PC = 0x0600;
		}

		TEST_METHOD(RTS_loads_Program_Counter_plus_one_from_stack)
		{
			uint16_t newPC = 0xcf97;
			mem_[0x01FF] = int8_t(0xcf);
			mem_[0x01FE] = int8_t(0x97);
			reg_.SP = 0xFD;

			oe_.RTS();

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(++newPC), int(reg_.PC));
		}
	};
}
