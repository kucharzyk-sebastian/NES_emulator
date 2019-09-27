#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(JSR_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor oe_;


		JSR_Tests() :
			reg_(),
			oe_(reg_, mem_)
		{
			reg_.PC = 0x0604;
		}

		TEST_METHOD(JSR_copy_current_Program_Counter_decremented_by_one_onto_the_stack_and_copies_passed_value_to_PC)
		{
			uint16_t value = 0x8c4f;

			oe_.JSR(value);

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int8_t(0x06), mem_[0x01FF]);
			Assert::AreEqual(int8_t(0x03), mem_[0x01FE]);
			Assert::AreEqual(int(value), int(reg_.PC));
		}
	};
}
