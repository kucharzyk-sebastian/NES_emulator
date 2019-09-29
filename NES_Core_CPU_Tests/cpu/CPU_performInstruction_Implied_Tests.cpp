#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"
#include "nes/cpu/cpu.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPU
{
	TEST_CLASS(PerformInstruction_Implied_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::CPU cpu_;
		using PSType = std::bitset<nes::cpu::registers::Registers::PSSize>;


		PerformInstruction_Implied_Tests() :
			reg_(),
			mem_(),
			cpu_(reg_, mem_)
		{
			reg_.PC = 0x0800;
		}

		TEST_METHOD(performInstruction_BRK)
		{
			mem_[reg_.PC] = int8_t(0x00);
			mem_[0xFFFE] = int8_t(0x43);
			mem_[0xFFFF] = int8_t(0xf0);

			cpu_.performInstruction();

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0xf043)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_CLC)
		{
			mem_[reg_.PC] = int8_t(0x18);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			cpu_.performInstruction();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x801)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_CLD)
		{
			mem_[reg_.PC] = int8_t(0xD8);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Decimal));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Decimal)]);

			cpu_.performInstruction();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Decimal)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x801)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_CLI)
		{
			mem_[reg_.PC] = int8_t(0x58);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::InterruptDisable));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::InterruptDisable)]);

			cpu_.performInstruction();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::InterruptDisable)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x801)), int(reg_.PC));
		}


		TEST_METHOD(performInstruction_CLV)
		{
			mem_[reg_.PC] = int8_t(0xB8);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);

			cpu_.performInstruction();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Overflow)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x801)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_DEX)
		{
			int8_t previousX = reg_.X = int8_t(13);
			mem_[reg_.PC] = int8_t(0xCA);

			cpu_.performInstruction();

			Assert::AreEqual(--previousX, reg_.X);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0801)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_DEY)
		{
			int8_t previousY = reg_.Y = int8_t(-15);
			mem_[reg_.PC] = int8_t(0x88);

			cpu_.performInstruction();

			Assert::AreEqual(--previousY, reg_.Y);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0801)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_INX)
		{
			reg_.X = int8_t(7);
			mem_[reg_.PC] = int8_t(0xE8);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(8), reg_.X);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0801)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_INY)
		{
			reg_.Y = int8_t(7);
			mem_[reg_.PC] = int8_t(0xC8);

			cpu_.performInstruction();

			Assert::AreEqual(int8_t(8), reg_.Y);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0801)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_NOP)
		{
			mem_[reg_.PC] = int8_t(0xEA);

			cpu_.performInstruction();

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0801)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_PHA)
		{
			int8_t value = 5;
			reg_.A = value;
			mem_[reg_.PC] = int8_t(0x48);
			Assert::AreNotEqual(value, mem_[0x01FF]);

			cpu_.performInstruction();

			Assert::AreEqual(value, mem_[0x01FF]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0801)), int(reg_.PC));
		}


		TEST_METHOD(performInstruction_PHP)
		{
			mem_[reg_.PC] = int8_t(0x08);
			Assert::AreNotEqual(PSType(mem_[0x01FF]).to_string(), reg_.PS.to_string());

			cpu_.performInstruction();

			Assert::AreEqual(reg_.PS.to_string(), PSType(mem_[0x01FF]).to_string());
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0801)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_PLA)
		{
			mem_[reg_.PC] = int8_t(0x68);
			int8_t value = 17;
			mem_[0x01FF] = value;
			reg_.SP = uint8_t(0xFE);
			Assert::AreNotEqual(value, reg_.A);

			cpu_.performInstruction();

			Assert::AreEqual(value, reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0801)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_PLP)
		{
			mem_[reg_.PC] = int8_t(0x28);
			auto value = PSType(0b01101101);
			reg_.SP = uint8_t(0x01FE);
			mem_[0x01FF] = static_cast<int8_t>(value.to_ulong());
			Assert::AreNotEqual(value.to_string(), reg_.PS.to_string());

			cpu_.performInstruction();

			Assert::AreEqual(PSType(mem_[0x01FF]).to_string(), reg_.PS.to_string());
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0801)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_RTI)
		{
			mem_[reg_.PC] = int8_t(0x40);
			uint16_t newPC = 0x14cd;
			mem_[0x01FF] = 0x14;
			mem_[0x01FE] = 0xcd;
			uint8_t newPS = 0b01101000;
			mem_[0x01FD] = newPS;
			reg_.SP = 0x01FC;

			cpu_.performInstruction();

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(newPC), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_RTS)
		{
			mem_[reg_.PC] = int8_t(0x60);
			uint16_t newPC = 0xcf97;
			mem_[0x01FF] = 0xcf;
			mem_[0x01FE] = 0x97;
			reg_.SP = 0x01FD;

			cpu_.performInstruction();

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(++newPC), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_SEC)
		{
			mem_[reg_.PC] = int8_t(0x38);
			reg_.PS.reset(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);

			cpu_.performInstruction();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Carry)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0801)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_SED)
		{
			mem_[reg_.PC] = int8_t(0xF8);
			reg_.PS.reset(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Decimal));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Decimal)]);

			cpu_.performInstruction();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Decimal)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0801)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_SEI)
		{
			mem_[reg_.PC] = int8_t(0x78);
			reg_.PS.reset(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::InterruptDisable));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::InterruptDisable)]);

			cpu_.performInstruction();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::InterruptDisable)]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0801)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_TAX)
		{
			mem_[reg_.PC] = int8_t(0xAA);
			reg_.A = int8_t(-76);

			cpu_.performInstruction();

			Assert::AreEqual(reg_.A, reg_.X);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0801)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_TAY)
		{
			mem_[reg_.PC] = int8_t(0xA8);
			reg_.A = int8_t(-14);

			cpu_.performInstruction();

			Assert::AreEqual(reg_.A, reg_.Y);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0801)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_TSX)
		{
			mem_[reg_.PC] = int8_t(0xBA);
			reg_.SP = uint8_t(0x0C);

			cpu_.performInstruction();

			Assert::AreEqual(reg_.SP, uint8_t(reg_.X));
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0801)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_TXA)
		{
			mem_[reg_.PC] = int8_t(0x8A);
			reg_.X = int8_t(68);

			cpu_.performInstruction();

			Assert::AreEqual(reg_.X, reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0801)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_TXS)
		{
			mem_[reg_.PC] = int8_t(0x9A);
			reg_.X = int8_t(106);

			cpu_.performInstruction();

			Assert::AreEqual(reg_.X, int8_t(reg_.SP));
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0801)), int(reg_.PC));
		}

		TEST_METHOD(performInstruction_TYA)
		{
			mem_[reg_.PC] = int8_t(0x98);
			reg_.Y = int8_t(127);

			cpu_.performInstruction();

			Assert::AreEqual(reg_.Y, reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0801)), int(reg_.PC));
		}
	};
}
