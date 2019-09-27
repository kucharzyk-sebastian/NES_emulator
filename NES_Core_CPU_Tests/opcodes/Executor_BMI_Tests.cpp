#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(BMI_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor oe_;


		BMI_Tests() :
			reg_(),
			oe_(reg_, mem_)
		{
			reg_.PC = 0x0600;
		}

		TEST_METHOD(BMI_adds_positive_value_to_program_counter_when_negative_flag_set)
		{
			int8_t value = 15;
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.BMI(value);

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x060F)), int(reg_.PC));
		}

		TEST_METHOD(BMI_adds_negative_value_to_program_counter_when_negative_flag_set)
		{
			int8_t value = -43;
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.BMI(value);

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x05D5)), int(reg_.PC));
		}

		TEST_METHOD(BMI_does_not_add_value_to_program_counter_when_negative_flag_not_set)
		{
			int8_t value = 66;
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.BMI(value);

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0x0600)), int(reg_.PC));
		}
	};
}
