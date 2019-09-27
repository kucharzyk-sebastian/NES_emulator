#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(BNE_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor oe_;


		BNE_Tests() :
			reg_(),
			oe_(reg_, mem_)
		{
			reg_.PC = 0x0600;
		}

		TEST_METHOD(BNE_adds_positive_value_to_program_counter_when_zero_flag_not_set)
		{
			int8_t value = 127;
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.BNE(value);

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x067F)), int(reg_.PC));
		}

		TEST_METHOD(BNE_adds_negative_value_to_program_counter_when_zero_flag_not_set)
		{
			int8_t value = -88;
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.BNE(value);

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x05A8)), int(reg_.PC));
		}

		TEST_METHOD(BNE_does_not_add_value_to_program_counter_when_zero_flag_set)
		{
			int8_t value = 43;
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.BNE(value);

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0600)), int(reg_.PC));
		}
	};
}
