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

		TEST_METHOD(JSR_copy_Program_Counter_of_next_instruction_decremented_by_one_onto_the_stack_and_copies_passed_value_to_PC)
		{
			uint16_t value = 0x8c4f;
			uint16_t nextPC = reg_.PC + 1;

			oe_.JSR(value);

			Assert::AreEqual(nextPC - 1, (mem_[0x0100 + reg_.SP + 2] << CHAR_BIT) + mem_[0x0100 + reg_.SP + 1]);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(value), int(reg_.PC));
		}
	};
}
