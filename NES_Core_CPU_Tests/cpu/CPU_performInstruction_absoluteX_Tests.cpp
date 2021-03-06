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

		TEST_METHOD(performInstruction_CMP)
		{
			reg_.X = int8_t(0x05);
			reg_.A = int8_t(1);
			mem_[reg_.PC] = int8_t(0xDD);
			mem_[reg_.PC + 1] = int8_t(0x76);
			mem_[reg_.PC + 2] = int8_t(0xF4);
			mem_[0xF476 + reg_.X] = int8_t(2);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			cpu_.performInstruction();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_DEC)
		{
			reg_.X = int8_t(0xa0);
			reg_.A = int8_t(1);
			mem_[reg_.PC] = int8_t(0xDE);
			mem_[reg_.PC + 1] = int8_t(0x02);
			mem_[reg_.PC + 2] = int8_t(0x01);
			int8_t value = 8;
			mem_[0x0102 + uint8_t(reg_.X)] = value;

			cpu_.performInstruction();

			Assert::AreEqual(--value, mem_[0x0102 + uint8_t(reg_.X)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_EOR)
		{
			reg_.X = int8_t(0x0c);
			reg_.A = int8_t(0b000001100);
			mem_[reg_.PC] = int8_t(0x5D);
			mem_[reg_.PC + 1] = int8_t(0x30);
			mem_[reg_.PC + 2] = int8_t(0x40);
			mem_[0x4030 + uint8_t(reg_.X)] = int8_t(0b100000101);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b100001001), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_INC)
		{
			reg_.X = int8_t(0x03);
			mem_[reg_.PC] = int8_t(0xFE);
			mem_[reg_.PC + 1] = int8_t(0xFC);
			mem_[reg_.PC + 2] = int8_t(0xB0);
			mem_[0xB0FC + reg_.X] = int8_t(7);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(8), mem_[0xB0FC + reg_.X]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_LDA)
		{
			reg_.X = int8_t(0x06);
			int8_t value = -5;
			mem_[reg_.PC] = int8_t(0xBD);
			mem_[reg_.PC + 1] = int8_t(0xdc);
			mem_[reg_.PC + 2] = int8_t(0xac);
			mem_[0xacdc + reg_.X] = value;

			cpu_.performInstruction();

			Assert::AreEqual(value, reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_LDY)
		{
			reg_.X = int8_t(0x06);
			int8_t value = -5;
			mem_[reg_.PC] = int8_t(0xBC);
			mem_[reg_.PC + 1] = int8_t(0xdc);
			mem_[reg_.PC + 2] = int8_t(0xac);
			mem_[0xacdc + reg_.X] = value;

			cpu_.performInstruction();

			Assert::AreEqual(value, reg_.Y);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_LSR)
		{
			reg_.X = int8_t(17);
			mem_[reg_.PC] = int8_t(0x5E);
			mem_[reg_.PC + 1] = int8_t(0xca);
			mem_[reg_.PC + 2] = int8_t(0xba);
			mem_[0xbaca + reg_.X] = int8_t(0b00001000);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b00000100), mem_[0xbaca + reg_.X]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_ORA)
		{
			reg_.X = int8_t(69);
			reg_.A = int8_t(0b10011000);
			mem_[reg_.PC] = int8_t(0x1D);
			mem_[reg_.PC + 1] = int8_t(0xce);
			mem_[reg_.PC + 2] = int8_t(0xde);
			mem_[0xdece + reg_.X] = int8_t(0b00001101);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b10011101), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_ROL)
		{
			reg_.X = int8_t(13);
			mem_[reg_.PC] = int8_t(0x3E);
			mem_[reg_.PC + 1] = int8_t(0x26);
			mem_[reg_.PC + 2] = int8_t(0x76);
			mem_[0x7626 + reg_.X] = int8_t(0b01110111);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b11101110), mem_[0x7626 + reg_.X]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_ROR)
		{
			reg_.X = int8_t(31);
			mem_[reg_.PC] = int8_t(0x7E);
			mem_[reg_.PC + 1] = int8_t(0xFA);
			mem_[reg_.PC + 2] = int8_t(0xFC);
			mem_[0xFCFA + reg_.X] = int8_t(0b01110111);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b00111011), mem_[0xFCFA + reg_.X]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_SBC)
		{
			reg_.X = int8_t(3);
			reg_.A = int8_t(15);
			mem_[reg_.PC] = int8_t(0xFD);
			mem_[reg_.PC + 1] = int8_t(0xca);
			mem_[reg_.PC + 2] = int8_t(0xcf);
			mem_[0xcfca + reg_.X] = int8_t(5);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(10), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_STA)
		{
			reg_.X = int8_t(0x03);
			reg_.A = int8_t(2);
			mem_[reg_.PC] = int8_t(0x9D);
			mem_[reg_.PC + 1] = int8_t(0x2a);
			mem_[reg_.PC + 2] = int8_t(0x15);

			cpu_.performInstruction();

			Assert::AreEqual(reg_.A, mem_[0x152a + reg_.X]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}
	};
}
