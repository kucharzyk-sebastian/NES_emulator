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
		}

		TEST_METHOD(performInstruction_ADC)
		{
			reg_.A = 5;
			reg_.Y = 17;
			mem_[reg_.PC] = int8_t(0x79);
			mem_[reg_.PC + 1] = int8_t(0xFE);
			mem_[reg_.PC + 2] = int8_t(0xFC);
			mem_[0xFCFE + reg_.Y] = int8_t(17);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(22), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_AND)
		{
			reg_.A = int8_t(0b00010001);
			reg_.Y = int8_t(0x01);
			mem_[reg_.PC] = int8_t(0x39);
			mem_[reg_.PC + 1] = int8_t(0x96);
			mem_[reg_.PC + 2] = int8_t(0x54);
			mem_[0x5496 + reg_.Y] = int8_t(0b11111111);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b00010001), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}
	};
}
