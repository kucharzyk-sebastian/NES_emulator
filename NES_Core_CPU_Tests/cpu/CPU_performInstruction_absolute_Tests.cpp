#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"
#include "nes/cpu/cpu.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPU
{
	TEST_CLASS(PerformInstruction_Absolute_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::CPU cpu_;


		PerformInstruction_Absolute_Tests() :
			reg_(),
			mem_(),
			cpu_(reg_, mem_)
		{
			reg_.PC = 0x0800;
		}

		TEST_METHOD(performInstruction_ADC)
		{
			reg_.A = 5;
			mem_[reg_.PC] = int8_t(0x6d);
			mem_[reg_.PC + 1] = int8_t(0xcd);
			mem_[reg_.PC + 2] = int8_t(0x68);
			mem_[0x68cd] = 15;

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(20), reg_.A);
		}

		TEST_METHOD(performInstruction_AND)
		{
			reg_.A = int8_t(0b10010111);
			mem_[reg_.PC] = int8_t(0x2d);
			mem_[reg_.PC + 1] = int8_t(0x09);
			mem_[reg_.PC + 2] = int8_t(0xda);
			mem_[0xda09] = int8_t(0b11001011);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b10000011), reg_.A);
		}
	};
}
