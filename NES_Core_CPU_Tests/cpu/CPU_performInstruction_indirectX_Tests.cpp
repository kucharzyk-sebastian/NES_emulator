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
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
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
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_CMP)
		{
			reg_.A = int8_t(1);
			reg_.X = int8_t(0x05);
			mem_[reg_.PC] = int8_t(0xC1);
			mem_[reg_.PC + 1] = int8_t(0xFF);
			mem_[0x0004] = int8_t(0xFF);
			mem_[0x0005] = int8_t(0xcc);
			mem_[0xccFF] = int8_t(2);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			cpu_.performInstruction();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_EOR)
		{
			reg_.A = int8_t(0b000001100);
			reg_.X = int8_t(0x07);
			mem_[reg_.PC] = int8_t(0x41);
			mem_[reg_.PC + 1] = int8_t(0x01);
			mem_[0x0001 + reg_.X] = int8_t(0x7a);
			mem_[0x0001 + reg_.X + 1] = int8_t(0x80);
			mem_[0x807a] = int8_t(0b100000101);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b100001001), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_LDA)
		{
			reg_.X = int8_t(0x09);
			int8_t value = -5;
			mem_[reg_.PC] = int8_t(0xA1);
			mem_[reg_.PC + 1] = int8_t(0x07);
			mem_[0x0007 + reg_.X] = int8_t(0xcf);
			mem_[0x0007 + reg_.X + 1] = int8_t(0xfc);
			mem_[0xfccf] = value;

			cpu_.performInstruction();

			Assert::AreEqual(value, reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_ORA)
		{
			reg_.X = int8_t(96);
			reg_.A = int8_t(0b10011000);
			mem_[reg_.PC] = int8_t(0x01);
			mem_[reg_.PC + 1] = int8_t(0xcf);
			mem_[uint8_t(0x00cf + reg_.X)] = int8_t(0x12);
			mem_[uint8_t(0x00cf + reg_.X + 1)] = int8_t(0x0b);
			mem_[0x0b12] = int8_t(0b00001101);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b10011101), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_SBC)
		{
			reg_.X = int8_t(3);
			reg_.A = int8_t(15);
			mem_[reg_.PC] = int8_t(0xE1);
			mem_[reg_.PC + 1] = int8_t(0xca);
			mem_[0x00ca + reg_.X] = int8_t(0x60);
			mem_[0x00ca + reg_.X + 1] = int8_t(0x50);
			mem_[0x5060] = int8_t(5);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(10), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}
	};
}
