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
			mem_[reg_.PC] = int8_t(0x06);
			mem_[reg_.PC + 1] = int8_t(0xfc);
			mem_[0x00fc] = int8_t(0b00000001);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b00000010), mem_[0x00fc]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_BIT)
		{
			reg_.A = int8_t(0b10010001);
			mem_[reg_.PC] = int8_t(0x24);
			mem_[reg_.PC + 1] = int8_t(0xff);
			mem_[0x00ff] = int8_t(0b10010000);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			cpu_.performInstruction();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_CMP)
		{
			reg_.A = int8_t(1);
			mem_[reg_.PC] = int8_t(0xC5);
			mem_[reg_.PC + 1] = int8_t(0xa0);
			mem_[0x00a0] = int8_t(2);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			cpu_.performInstruction();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_CPX)
		{
			reg_.X = int8_t(1);
			mem_[reg_.PC] = int8_t(0xE4);
			mem_[reg_.PC + 1] = int8_t(0x79);
			mem_[0x0079] = int8_t(2);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			cpu_.performInstruction();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_CPY)
		{
			reg_.Y = int8_t(1);
			mem_[reg_.PC] = int8_t(0xC4);
			mem_[reg_.PC + 1] = int8_t(0x01);
			mem_[0x0001] = int8_t(2);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			cpu_.performInstruction();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_DEC)
		{
			mem_[reg_.PC] = int8_t(0xC6);
			mem_[reg_.PC + 1] = int8_t(0xaf);
			int8_t value = 8;
			mem_[0x00af] = int8_t(value);

			cpu_.performInstruction();

			Assert::AreEqual(--value, mem_[0x00af]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_EOR)
		{
			reg_.A = int8_t(0b000001100);
			mem_[reg_.PC] = int8_t(0x45);
			mem_[reg_.PC + 1] = int8_t(0x00);
			mem_[0x0000] = int8_t(0b100000101);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b100001001), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_INC)
		{
			mem_[reg_.PC] = int8_t(0xE6);
			mem_[reg_.PC + 1] = int8_t(0xC6);
			mem_[0x00C6] = int8_t(7);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(8), mem_[0x00C6]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_LDA)
		{
			int8_t value = -5;
			mem_[reg_.PC] = int8_t(0xA5);
			mem_[reg_.PC + 1] = int8_t(0xac);
			mem_[0x00ac] = value;

			cpu_.performInstruction();

			Assert::AreEqual(value, reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_LDX)
		{
			int8_t value = -5;
			mem_[reg_.PC] = int8_t(0xA6);
			mem_[reg_.PC + 1] = int8_t(0xac);
			mem_[0x00ac] = value;

			cpu_.performInstruction();

			Assert::AreEqual(value, reg_.X);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_LDY)
		{
			int8_t value = -5;
			mem_[reg_.PC] = int8_t(0xA4);
			mem_[reg_.PC + 1] = int8_t(0xac);
			mem_[0x00ac] = value;

			cpu_.performInstruction();

			Assert::AreEqual(value, reg_.Y);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_LSR)
		{
			mem_[reg_.PC] = int8_t(0x46);
			mem_[reg_.PC + 1] = int8_t(0x65);
			mem_[0x0065] = int8_t(0b00001000);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b00000100), mem_[0x0065]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_ORA)
		{
			reg_.A = int8_t(0b10011000);
			mem_[reg_.PC] = int8_t(0x05);
			mem_[reg_.PC + 1] = int8_t(0x16);
			mem_[0x0016] = int8_t(0b00001101);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b10011101), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_ROL)
		{
			mem_[reg_.PC] = int8_t(0x26);
			mem_[reg_.PC + 1] = int8_t(0x26);
			mem_[0x0026] = int8_t(0b01110111);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b11101110), mem_[0x0026]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_ROR)
		{
			mem_[reg_.PC] = int8_t(0x66);
			mem_[reg_.PC + 1] = int8_t(0xFF);
			mem_[0x00FF] = int8_t(0b01110111);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b00111011), mem_[0x00FF]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}
	};
}
