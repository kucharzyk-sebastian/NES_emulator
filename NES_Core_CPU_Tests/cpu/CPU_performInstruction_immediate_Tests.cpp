#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"
#include "nes/cpu/cpu.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPU
{
	TEST_CLASS(PerformInstruction_Immediate_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::CPU cpu_;


		PerformInstruction_Immediate_Tests() :
			reg_(),
			mem_(),
			cpu_(reg_, mem_)
		{
			reg_.PC = 0x0800;
		}

		TEST_METHOD(performInstruction_performs_ADC)
		{
			reg_.A = 5;
			mem_[reg_.PC] = int8_t(0x69);
			mem_[reg_.PC + 1] = int8_t(5);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(10), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_AND)
		{
			reg_.A = int8_t(0b11000010);
			mem_[reg_.PC] = int8_t(0x29);
			mem_[reg_.PC + 1] = int8_t(0b00010001);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b00000000), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_CMP)
		{
			reg_.A = int8_t(1);
			mem_[reg_.PC] = int8_t(0xC9);
			mem_[reg_.PC + 1] = int8_t(2);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			cpu_.performInstruction();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_CPX)
		{
			reg_.X = int8_t(1);
			mem_[reg_.PC] = int8_t(0xE0);
			mem_[reg_.PC + 1] = int8_t(2);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			cpu_.performInstruction();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_CPY)
		{
			reg_.Y = int8_t(1);
			mem_[reg_.PC] = int8_t(0xC0);
			mem_[reg_.PC + 1] = int8_t(2);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			cpu_.performInstruction();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_EOR)
		{
			reg_.A = int8_t(0b000001100);
			mem_[reg_.PC] = int8_t(0x49);
			mem_[reg_.PC + 1] = int8_t(0b100000101);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b100001001), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_LDA)
		{
			int8_t value = -5;
			mem_[reg_.PC] = int8_t(0xA9);
			mem_[reg_.PC + 1] = value;

			cpu_.performInstruction();

			Assert::AreEqual(value, reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_LDX)
		{
			int8_t value = -5;
			mem_[reg_.PC] = int8_t(0xA2);
			mem_[reg_.PC + 1] = value;

			cpu_.performInstruction();

			Assert::AreEqual(value, reg_.X);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_LDY)
		{
			int8_t value = -5;
			mem_[reg_.PC] = int8_t(0xA0);
			mem_[reg_.PC + 1] = value;

			cpu_.performInstruction();

			Assert::AreEqual(value, reg_.Y);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_ORA)
		{
			reg_.A = int8_t(0b10011000);
			mem_[reg_.PC] = int8_t(0x09);
			mem_[reg_.PC + 1] = int8_t(0b00001101);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b10011101), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0802)), int(reg_.PC));
		}
	};
}
