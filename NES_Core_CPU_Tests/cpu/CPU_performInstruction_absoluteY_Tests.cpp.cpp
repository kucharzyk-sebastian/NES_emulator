#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"
#include "nes/cpu/cpu.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPU
{
	TEST_CLASS(PerformInstruction_AbsoluteY_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::CPU cpu_;


		PerformInstruction_AbsoluteY_Tests() :
			reg_(),
			mem_(),
			cpu_(reg_, mem_)
		{
			reg_.PC = 0x0800;
			reg_.Y = 17;
			reg_.A = 5;
		}

		TEST_METHOD(performInstruction_ADC)
		{
			mem_[reg_.PC] = 0x79;
			mem_[reg_.PC + 1] = int8_t(0xFE);
			mem_[reg_.PC + 2] = int8_t(0xFC);
			mem_[0xFCFE + reg_.Y] = 17;

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(22), reg_.A);
		}
	};
}
