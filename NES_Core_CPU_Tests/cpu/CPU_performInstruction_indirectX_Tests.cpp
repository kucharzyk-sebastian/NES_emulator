#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"
#include "nes/cpu/cpu.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPU
{
	TEST_CLASS(PerformInstruction_IndirectX_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::CPU cpu_;


		PerformInstruction_IndirectX_Tests() :
			reg_(),
			mem_(),
			cpu_(reg_, mem_)
		{
			reg_.PC = 0x0800;
			reg_.A = 5;
			reg_.X = 2;
		}

		TEST_METHOD(performInstruction_ADC)
		{
			mem_[reg_.PC] = 0x61;
			mem_[reg_.PC + 1] = int8_t(0x15);
			mem_[0x0017] = int8_t(0x10);
			mem_[0x0018] = int8_t(0xD0);
			mem_[0xD010] = -3;

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(2), reg_.A);
		}
	};
}
