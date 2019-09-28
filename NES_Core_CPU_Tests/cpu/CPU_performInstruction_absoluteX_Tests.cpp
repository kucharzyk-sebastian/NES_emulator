#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"
#include "nes/cpu/cpu.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPU
{
	TEST_CLASS(PerformInstruction_AbsoluteX_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::CPU cpu_;


		PerformInstruction_AbsoluteX_Tests() :
			reg_(),
			mem_(),
			cpu_(reg_, mem_)
		{
			reg_.PC = 0x0800;
			reg_.A = 5;
			reg_.X = 4;
		}

		TEST_METHOD(performInstruction_ADC)
		{
			mem_[reg_.PC] = 0x7d;
			mem_[reg_.PC + 1] = uint8_t(0xcd);
			mem_[reg_.PC + 2] = uint8_t(0x68);
			mem_[0x68cd + reg_.X] = 8;

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(13), reg_.A);
		}
	};
}
