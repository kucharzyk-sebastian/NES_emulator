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
		}

		TEST_METHOD(performInstruction_ADC)
		{
			reg_.A = int8_t(5);
			reg_.X = int8_t(2);
			mem_[reg_.PC] = int8_t(0x61);
			mem_[reg_.PC + 1] = int8_t(0x15);
			mem_[0x0015 + reg_.X] = int8_t(0x10);
			mem_[0x0015 + reg_.X + 1] = int8_t(0xD0);
			mem_[0xD010] = int8_t (-3);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(2), reg_.A);
		}

		TEST_METHOD(performInstruction_AND)
		{
			reg_.A = int8_t(0b11000010);
			reg_.X = int8_t(7);
			mem_[reg_.PC] = int8_t(0x21);
			mem_[reg_.PC + 1] = int8_t(0x30);
			mem_[0x0030 + reg_.X] = int8_t(0x03);
			mem_[0x0030 + reg_.X + 1] = int8_t(0xcc);
			mem_[0xcc03] = int8_t(0b10111010);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b10000010), reg_.A);
		}
	};
}
