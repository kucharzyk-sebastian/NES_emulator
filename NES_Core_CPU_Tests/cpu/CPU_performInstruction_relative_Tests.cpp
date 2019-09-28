#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"
#include "nes/cpu/cpu.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPU
{
	TEST_CLASS(PerformInstruction_Relative_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::CPU cpu_;


		PerformInstruction_Relative_Tests() :
			reg_(),
			mem_(),
			cpu_(reg_, mem_)
		{
			reg_.PC = 0x0800;
		}

		TEST_METHOD(performInstruction_BCC)
		{
			mem_[reg_.PC] = int8_t(0x90);
			mem_[reg_.PC + 1] = int8_t(3);
			reg_.PS.reset(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));

			cpu_.performInstruction();

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0805)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_BCS)
		{
			mem_[reg_.PC] = int8_t(0xB0);
			mem_[reg_.PC + 1] = int8_t(3);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));

			cpu_.performInstruction();

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0805)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_BEQ)
		{
			mem_[reg_.PC] = int8_t(0xF0);
			mem_[reg_.PC + 1] = int8_t(-128);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));

			cpu_.performInstruction();

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0782)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_BMI)
		{
			mem_[reg_.PC] = int8_t(0x30);
			mem_[reg_.PC + 1] = int8_t(6);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));

			cpu_.performInstruction();

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0808)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_BNE)
		{
			mem_[reg_.PC] = int8_t(0xD0);
			mem_[reg_.PC + 1] = int8_t(127);
			reg_.PS.reset(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));

			cpu_.performInstruction();

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0881)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_BPL)
		{
			mem_[reg_.PC] = int8_t(0x10);
			mem_[reg_.PC + 1] = int8_t(5);
			reg_.PS.reset(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));

			cpu_.performInstruction();

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0807)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_BVC)
		{
			mem_[reg_.PC] = int8_t(0x50);
			mem_[reg_.PC + 1] = int8_t(8);
			reg_.PS.reset(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow));

			cpu_.performInstruction();

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x080A)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_BVS)
		{
			mem_[reg_.PC] = int8_t(0x70);
			mem_[reg_.PC + 1] = int8_t(1);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow));

			cpu_.performInstruction();

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0803)), int(reg_.PC));
		}
	};
}
