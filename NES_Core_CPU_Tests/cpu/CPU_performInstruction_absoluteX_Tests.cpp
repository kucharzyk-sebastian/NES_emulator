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
		}

		TEST_METHOD(performInstruction_ADC)
		{
			reg_.A = int8_t(5);
			reg_.X = int8_t(4);
			mem_[reg_.PC] = int8_t(0x7d);
			mem_[reg_.PC + 1] = uint8_t(0xcd);
			mem_[reg_.PC + 2] = uint8_t(0x68);
			mem_[0x68cd + reg_.X] = int8_t(8);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(13), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_AND)
		{
			reg_.A = int8_t(0b10000000);
			reg_.X = int8_t(0xFF);
			mem_[reg_.PC] = int8_t(0x3d);
			mem_[reg_.PC + 1] = int8_t(0x08);
			mem_[reg_.PC + 2] = int8_t(0x08);
			mem_[0x0808 + uint8_t(reg_.X)] = int8_t(0b11001011);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b10000000), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_ASL)
		{
			reg_.X = int8_t(0xca);
			mem_[reg_.PC] = int8_t(0x1E);
			mem_[reg_.PC + 1] = int8_t(0x08);
			mem_[reg_.PC + 2] = int8_t(0x10);
			mem_[0x1008 + uint8_t(reg_.X)] = int8_t(0b00001111);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b000011110), mem_[0x1008 + uint8_t(reg_.X)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}
	};
}
