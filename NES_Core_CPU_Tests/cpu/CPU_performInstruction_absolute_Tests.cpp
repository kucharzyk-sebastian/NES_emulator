#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"
#include "nes/cpu/cpu.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPU
{
	TEST_CLASS(PerformInstruction_Absolute_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::CPU cpu_;


		PerformInstruction_Absolute_Tests() :
			reg_(),
			mem_(),
			cpu_(reg_, mem_)
		{
			reg_.PC = 0x0800;
		}

		TEST_METHOD(performInstruction_ADC)
		{
			reg_.A = 5;
			mem_[reg_.PC] = int8_t(0x6d);
			mem_[reg_.PC + 1] = int8_t(0xcd);
			mem_[reg_.PC + 2] = int8_t(0x68);
			mem_[0x68cd] = 15;

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(20), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_AND)
		{
			reg_.A = int8_t(0b10010111);
			mem_[reg_.PC] = int8_t(0x2d);
			mem_[reg_.PC + 1] = int8_t(0x09);
			mem_[reg_.PC + 2] = int8_t(0xda);
			mem_[0xda09] = int8_t(0b11001011);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b10000011), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_ASL)
		{
			mem_[reg_.PC] = int8_t(0x0e);
			mem_[reg_.PC + 1] = int8_t(0xfc);
			mem_[reg_.PC + 2] = int8_t(0x56);
			mem_[0x56fc] = int8_t(0b00001111);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b000011110), mem_[0x56fc]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_BIT)
		{
			reg_.A = int8_t(0b10010001);
			mem_[reg_.PC] = int8_t(0x2c);
			mem_[reg_.PC + 1] = int8_t(0xc5);
			mem_[reg_.PC + 2] = int8_t(0x01);
			mem_[0x01c5] = int8_t(0b10010000);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			cpu_.performInstruction();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_CMP)
		{
			reg_.A = int8_t(1);
			mem_[reg_.PC] = int8_t(0xCD);
			mem_[reg_.PC + 1] = int8_t(0x01);
			mem_[reg_.PC + 2] = int8_t(0xc3);
			mem_[0xc301] =  int8_t(2);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			cpu_.performInstruction();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_CPX)
		{
			reg_.X = int8_t(1);
			mem_[reg_.PC] = int8_t(0xEC);
			mem_[reg_.PC + 1] = int8_t(0x54);
			mem_[reg_.PC + 2] = int8_t(0xc1);
			mem_[0xc154] = int8_t(2);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			cpu_.performInstruction();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_CPY)
		{
			reg_.Y = int8_t(1);
			mem_[reg_.PC] = int8_t(0xCC);
			mem_[reg_.PC + 1] = int8_t(0xFF);
			mem_[reg_.PC + 2] = int8_t(0x02);
			mem_[0x02FF] = int8_t(2);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			cpu_.performInstruction();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_DEC)
		{
			mem_[reg_.PC] = int8_t(0xCE);
			mem_[reg_.PC + 1] = int8_t(0xFF);
			mem_[reg_.PC + 2] = int8_t(0xFF);
			int8_t value = 8;
			mem_[0xFFFF] = value;

			cpu_.performInstruction();

			Assert::AreEqual(--value, mem_[0xFFFF]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}
	};
}
