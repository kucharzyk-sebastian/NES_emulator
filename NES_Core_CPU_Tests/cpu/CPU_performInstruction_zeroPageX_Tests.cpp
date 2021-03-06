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

		TEST_METHOD(performInstruction_ADC)
		{
			reg_.A = int8_t(5);
			reg_.X = int8_t(0xa1);
			mem_[reg_.PC] = int8_t(0x75);
			mem_[reg_.PC + 1] = int8_t(0x05);
			mem_[0x00a6] = int8_t(6);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(11), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_AND)
		{
			reg_.A = int8_t(0b00011001);
			reg_.X = int8_t(0xFF);
			mem_[reg_.PC] = int8_t(0x35);
			mem_[reg_.PC + 1] = int8_t(0x02);
			mem_[0x0001] = int8_t(0b00001111);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b00001001), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_ASL)
		{
			reg_.X = int8_t(0x03);
			mem_[reg_.PC] = int8_t(0x16);
			mem_[reg_.PC + 1] = int8_t(0x20);
			mem_[0x0020 + reg_.X] = int8_t(0b00001111);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b00011110), mem_[0x0020 + reg_.X]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_CMP)
		{
			reg_.X = int8_t(0x03);
			reg_.A = int8_t(1);
			mem_[reg_.PC] = int8_t(0xD5);
			mem_[reg_.PC + 1] = int8_t(0x45);
			mem_[0x0045 + reg_.X] = int8_t(2);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			cpu_.performInstruction();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_DEC)
		{
			reg_.X = int8_t(0x03);
			mem_[reg_.PC] = int8_t(0xD6);
			mem_[reg_.PC + 1] = int8_t(0xFA);
			int8_t value = 8;
			mem_[0x00FA + reg_.X] = value;

			cpu_.performInstruction();

			Assert::AreEqual(--value, mem_[0x00FA + reg_.X]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_EOR)
		{
			reg_.A = int8_t(0b000001100);
			reg_.X = int8_t(0x07);
			mem_[reg_.PC] = int8_t(0x55);
			mem_[reg_.PC + 1] = int8_t(0x0A);
			mem_[0x000A + reg_.X] = int8_t(0b100000101);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b100001001), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_INC)
		{
			reg_.X = int8_t(0xc1);
			mem_[reg_.PC] = int8_t(0xF6);
			mem_[reg_.PC + 1] = int8_t(0xFA);
			mem_[uint8_t(0x00FA + uint8_t(reg_.X))] = int8_t(7);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(8), mem_[uint8_t(0x00FA + uint8_t(reg_.X))]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_LDA)
		{
			reg_.X = int8_t(3);
			int8_t value = -5;
			mem_[reg_.PC] = int8_t(0xB5);
			mem_[reg_.PC + 1] = int8_t(0xac);
			mem_[0x00ac + reg_.X] = value;

			cpu_.performInstruction();

			Assert::AreEqual(value, reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_LDY)
		{
			reg_.X = int8_t(3);
			int8_t value = -5;
			mem_[reg_.PC] = int8_t(0xB4);
			mem_[reg_.PC + 1] = int8_t(0xac);
			mem_[0x00ac + reg_.X] = value;

			cpu_.performInstruction();

			Assert::AreEqual(value, reg_.Y);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_LSR)
		{
			reg_.X = int8_t(17);
			mem_[reg_.PC] = int8_t(0x56);
			mem_[reg_.PC + 1] = int8_t(0x65);
			mem_[0x0065 + reg_.X] = int8_t(0b00001000);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b00000100), mem_[0x0065 + reg_.X]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_ORA)
		{
			reg_.X = int8_t(1);
			reg_.A = int8_t(0b10011000);
			mem_[reg_.PC] = int8_t(0x15);
			mem_[reg_.PC + 1] = int8_t(0x16);
			mem_[0x0016 + reg_.X] = int8_t(0b00001101);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b10011101), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_ROL)
		{
			reg_.X = int8_t(6);
			mem_[reg_.PC] = int8_t(0x36);
			mem_[reg_.PC + 1] = int8_t(0x26);
			mem_[0x0026 + reg_.X] = int8_t(0b01110111);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b11101110), mem_[0x0026 + reg_.X]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_ROR)
		{
			reg_.X = int8_t(69);
			mem_[reg_.PC] = int8_t(0x76);
			mem_[reg_.PC + 1] = int8_t(0xFF);
			mem_[uint8_t(0x00FF + reg_.X)] = int8_t(0b01110111);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b00111011), mem_[uint8_t(0x00FF + reg_.X)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_SBC)
		{
			reg_.X = int8_t(3);
			reg_.A = int8_t(15);
			mem_[reg_.PC] = int8_t(0xF5);
			mem_[reg_.PC + 1] = int8_t(0xca);
			mem_[0x00ca + reg_.X] = int8_t(5);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(10), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_STA)
		{
			reg_.X = int8_t(4);
			reg_.A = int8_t(33);
			mem_[reg_.PC] = int8_t(0x95);
			mem_[reg_.PC + 1] = int8_t(0xE7);

			cpu_.performInstruction();

			Assert::AreEqual(reg_.A, mem_[0x00E7 + reg_.X]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_STY)
		{
			reg_.X = int8_t(4);
			reg_.Y = int8_t(-128);
			mem_[reg_.PC] = int8_t(0x94);
			mem_[reg_.PC + 1] = int8_t(0xc6);

			cpu_.performInstruction();

			Assert::AreEqual(reg_.Y, mem_[0x00c6 + reg_.X]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}
	};
}
