#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"
#include "nes/cpu/cpu.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPU
{
	TEST_CLASS(PerformInstruction_Implied_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::CPU cpu_;


		PerformInstruction_Implied_Tests() :
			reg_(),
			mem_(),
			cpu_(reg_, mem_)
		{
			reg_.PC = 0x0800;
		}

		TEST_METHOD(performInstruction_performs_BRK)
		{
			mem_[reg_.PC] = int8_t(00);
			mem_[0xFFFE] = int8_t(0x43);
			mem_[0xFFFF] = int8_t(0xf0);

			cpu_.performInstruction();

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0xf043)), int(reg_.PC));
		}
	};
}
