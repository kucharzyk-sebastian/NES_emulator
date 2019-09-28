#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"
#include "nes/cpu/cpu.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPU
{
	TEST_CLASS(PerformInstruction_IndirectY_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::CPU cpu_;


		PerformInstruction_IndirectY_Tests() :
			reg_(),
			mem_(),
			cpu_(reg_, mem_)
		{
			reg_.PC = 0x0800;
			reg_.A = 5;
			reg_.Y = 3;
		}

		TEST_METHOD(performInstruction_ADC)
		{
			auto x = uint8_t(int8_t(-127)) + int8_t(-4);
			mem_[reg_.PC] = 0x71;
			mem_[reg_.PC + 1] = int8_t(0x2A);
			mem_[0x002A] = int8_t(0x35);
			mem_[0x002B] = int8_t(0xC2);
			mem_[0xC238] = 6;

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(11), reg_.A);
		}
	};
}
