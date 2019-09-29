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
	};
}
