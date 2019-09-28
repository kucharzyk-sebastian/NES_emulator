#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"
#include "nes/cpu/cpu.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPU
{
	TEST_CLASS(PerformInstruction_ZeroPage_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::CPU cpu_;


		PerformInstruction_ZeroPage_Tests() :
			reg_(),
			mem_(),
			cpu_(reg_, mem_)
		{
			reg_.PC = 0x0800;
			reg_.A = 5;
		}

		TEST_METHOD(performInstruction_adds_value_to_A_register_immediate_addressing)
		{
			mem_[reg_.PC] = 0x69;
			mem_[reg_.PC + 1] = 5;

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(10), reg_.A);
		}
	};
}
