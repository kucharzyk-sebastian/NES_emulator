#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"
#include "nes/cpu/cpu.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPU
{
	TEST_CLASS(PerformInstruction_ZeroPageX_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::CPU cpu_;


		PerformInstruction_ZeroPageX_Tests() :
			reg_(),
			mem_(),
			cpu_(reg_, mem_)
		{
			reg_.PC = 0x0800;
		}

		TEST_METHOD(performInstruction_LDX)
		{
			reg_.Y = int8_t(3);
			int8_t value = -5;
			mem_[reg_.PC] = int8_t(0xB6);
			mem_[reg_.PC + 1] = int8_t(0xac);
			mem_[0x00ac + reg_.Y] = value;

			cpu_.performInstruction();

			Assert::AreEqual(value, reg_.X);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_STY)
		{
			reg_.Y = int8_t(4);
			reg_.X = int8_t(127);
			mem_[reg_.PC] = int8_t(0x96);
			mem_[reg_.PC + 1] = int8_t(0x26);

			cpu_.performInstruction();

			Assert::AreEqual(reg_.X, mem_[0x0026 + reg_.Y]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}
	};
}
