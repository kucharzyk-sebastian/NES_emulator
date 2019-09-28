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
		}

		TEST_METHOD(performInstruction_ADC)
		{
			reg_.A = int8_t(5);
			mem_[reg_.PC] = int8_t(0x69);
			mem_[reg_.PC + 1] = int8_t(0x05);
			mem_[0x0005] = int8_t(5);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(10), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_AND)
		{
			reg_.A = int8_t(0b11011101);
			mem_[reg_.PC] = int8_t(0x25);
			mem_[reg_.PC + 1] = int8_t(0xfc);
			mem_[0x00fc] = int8_t(0b00001111);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b00001101), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_ASL)
		{
			mem_[0x00fc] = int8_t(0b00000001);
			mem_[reg_.PC] = int8_t(0x06);
			mem_[reg_.PC + 1] = int8_t(0xfc);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b00000010), mem_[0x00fc]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));

		}
	};
}
