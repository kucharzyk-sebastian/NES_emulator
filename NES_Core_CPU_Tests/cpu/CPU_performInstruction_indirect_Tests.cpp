
#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"
#include "nes/cpu/cpu.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPU
{
	TEST_CLASS(PerformInstruction_Indirect_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::CPU cpu_;


		PerformInstruction_Indirect_Tests() :
			reg_(),
			mem_(),
			cpu_(reg_, mem_)
		{
			reg_.PC = 0x0800;
		}

		TEST_METHOD(performInstruction_JMP)
		{
			mem_[reg_.PC] = int8_t(0x6C);
			mem_[reg_.PC + 1] = int8_t(0x01);
			mem_[reg_.PC + 2] = int8_t(0xFB);
			mem_[0xFB01] = int8_t(0x23);
			mem_[0xFB02] = int8_t(0xea);

			cpu_.performInstruction();

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0xea23)), int(reg_.PC));
		}
	};
}
