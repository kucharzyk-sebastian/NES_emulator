#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"
#include "nes/cpu/cpu.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPU
{
	TEST_CLASS(PerformInstruction_Accumulator_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::CPU cpu_;


		PerformInstruction_Accumulator_Tests() :
			reg_(),
			mem_(),
			cpu_(reg_, mem_)
		{
			reg_.PC = 0x0800;
		}

		TEST_METHOD(performInstruction_ASL)
		{
			reg_.A = int8_t(0b00001000);
			mem_[reg_.PC] = int8_t(0x0A);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b00010000), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0801)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_LSR)
		{
			reg_.A = int8_t(0b00001000);
			mem_[reg_.PC] = int8_t(0x4A);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b00000100), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0801)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_ROL)
		{
			reg_.A = int8_t(0b01110111);
			mem_[reg_.PC] = int8_t(0x2A);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b11101110), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0801)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_ROR)
		{
			reg_.A = int8_t(0b01110111);
			mem_[reg_.PC] = int8_t(0x6A);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(0b00111011), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0801)), int(reg_.PC));
		}
	};
}
