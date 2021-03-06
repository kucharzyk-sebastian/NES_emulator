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

		TEST_METHOD(performInstruction_CMP)
		{
			reg_.Y = int8_t(0x05);
			reg_.A = int8_t(1);
			mem_[reg_.PC] = int8_t(0xD9);
			mem_[reg_.PC + 1] = int8_t(0x33);
			mem_[reg_.PC + 2] = int8_t(0xF0);
			mem_[0xF033 + reg_.Y] = int8_t(2);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			cpu_.performInstruction();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_EOR)
		{
			reg_.Y = int8_t(0xFC);
			reg_.A = int8_t(0b000001100);
			mem_[reg_.PC] = int8_t(0x59);
			mem_[reg_.PC + 1] = int8_t(0x25);
			mem_[reg_.PC + 2] = int8_t(0x01);
			mem_[0x0125 + uint8_t(reg_.Y)] = int8_t(0b100000101);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b100001001), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_LDA)
		{
			reg_.Y = int8_t(0x06);
			int8_t value = -5;
			mem_[reg_.PC] = int8_t(0xB9);
			mem_[reg_.PC + 1] = int8_t(0x0c);
			mem_[reg_.PC + 2] = int8_t(0x0e);
			mem_[0x0e0c + reg_.Y] = value;

			cpu_.performInstruction();

			Assert::AreEqual(value, reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_LDX)
		{
			reg_.Y = int8_t(0x06);
			int8_t value = -5;
			mem_[reg_.PC] = int8_t(0xBE);
			mem_[reg_.PC + 1] = int8_t(0x0c);
			mem_[reg_.PC + 2] = int8_t(0x0e);
			mem_[0x0e0c + reg_.Y] = value;

			cpu_.performInstruction();

			Assert::AreEqual(value, reg_.X);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_ORA)
		{
			reg_.Y = int8_t(96);
			reg_.A = int8_t(0b10011000);
			mem_[reg_.PC] = int8_t(0x19);
			mem_[reg_.PC + 1] = int8_t(0xce);
			mem_[reg_.PC + 2] = int8_t(0xde);
			mem_[0xdece + reg_.Y] = int8_t(0b00001101);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b10011101), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_STA)
		{
			reg_.Y = int8_t(0x06);
			reg_.A = int8_t(-15);
			mem_[reg_.PC] = int8_t(0x99);
			mem_[reg_.PC + 1] = int8_t(0xd0);
			mem_[reg_.PC + 2] = int8_t(0x0d);

			cpu_.performInstruction();

			Assert::AreEqual(reg_.A, mem_[0x0dd0 + reg_.Y]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}
	};
}
