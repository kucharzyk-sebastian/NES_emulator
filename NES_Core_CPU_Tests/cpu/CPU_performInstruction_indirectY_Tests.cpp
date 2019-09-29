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

		}

		TEST_METHOD(performInstruction_ADC)
		{
			reg_.A = int8_t(5);
			reg_.Y = int8_t(3);
			mem_[reg_.PC] = int8_t(0x71);
			mem_[reg_.PC + 1] = int8_t(0x2A);
			mem_[0x002A] = int8_t(0x35);
			mem_[0x002B] = int8_t(0xC2);
			mem_[0xC235 + reg_.Y] = 6;

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(11), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_AND)
		{
			reg_.A = int8_t(0b11000101);
			reg_.Y = int8_t(0xFF);
			mem_[reg_.PC] = int8_t(0x31);
			mem_[reg_.PC + 1] = int8_t(0xa0);
			mem_[0x00a0] = int8_t(0x00);
			mem_[0x00a1] = int8_t(0x6d);
			mem_[0x6d00 + uint8_t(reg_.Y)] = int8_t(0b00000110);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b00000100), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_CMP)
		{
			reg_.A = int8_t(1);
			reg_.Y = int8_t(0xFF);
			mem_[reg_.PC] = int8_t(0xD1);
			mem_[reg_.PC + 1] = int8_t(0xFF);
			mem_[0x00FF] = int8_t(0x03);
			mem_[0x0100] = int8_t(0x65);
			mem_[0x6503 + uint8_t(reg_.Y)] = int8_t(2);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			cpu_.performInstruction();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_EOR)
		{
			reg_.A = int8_t(0b000001100);
			reg_.Y = int8_t(0xc5);
			mem_[reg_.PC] = int8_t(0x51);
			mem_[reg_.PC + 1] = int8_t(0x65);
			mem_[0x0065] = int8_t(0xF7);
			mem_[0x0066] = int8_t(0x04);
			mem_[0x04F7 + uint8_t(reg_.Y)] = int8_t(0b100000101);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b100001001), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_LDA)
		{
			reg_.Y = int8_t(0x09);
			int8_t value = -5;
			mem_[reg_.PC] = int8_t(0xB1);
			mem_[reg_.PC + 1] = int8_t(0x07);
			mem_[0x0007] = int8_t(0xcf);
			mem_[0x0008] = int8_t(0xfc);
			mem_[0xfccf + reg_.Y] = value;

			cpu_.performInstruction();

			Assert::AreEqual(value, reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_ORA)
		{
			reg_.Y = int8_t(96);
			reg_.A = int8_t(0b10011000);
			mem_[reg_.PC] = int8_t(0x11);
			mem_[reg_.PC + 1] = int8_t(0xcf);
			mem_[0x00cf] = int8_t(0x12);
			mem_[0x00cf + 1] = int8_t(0x0b);
			mem_[0x0b12 + reg_.Y] = int8_t(0b00001101);

			cpu_.performInstruction();
			 
			Assert::AreEqual(int8_t(0b10011101), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_SBC)
		{
			reg_.Y = int8_t(3);
			reg_.A = int8_t(15);
			mem_[reg_.PC] = int8_t(0xF1);
			mem_[reg_.PC + 1] = int8_t(0xca);
			mem_[0x00ca] = int8_t(0x60);
			mem_[0x00ca + 1] = int8_t(0x50);
			mem_[0x5060 + reg_.Y] = int8_t(5);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(10), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_STA)
		{
			reg_.Y = int8_t(11);
			reg_.A = int8_t(-103);
			mem_[reg_.PC] = int8_t(0x91);
			mem_[reg_.PC + 1] = int8_t(0xd0);
			mem_[0xd0] = int8_t(0xa0);
			mem_[0xd0 + 1] = int8_t(0x07);

			cpu_.performInstruction();

			Assert::AreEqual(reg_.A, mem_[0x07a0 + reg_.Y]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}
	};
}
