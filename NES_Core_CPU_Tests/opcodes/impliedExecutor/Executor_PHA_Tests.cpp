#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodes/impliedExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_ImpliedExecutor
{
	TEST_CLASS(PHA_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::opcodes::ImpliedExecutor ie_;


		PHA_Tests() :
			reg_(),
			ie_(reg_, mem_)
		{

		}

		TEST_METHOD(PHA_pushes_A_register_value_onto_the_stack)
		{
			int8_t value = 5;
			reg_.A = value;
			Assert::AreNotEqual(value, mem_[0x01FF]);

			ie_.PHA();

			Assert::AreEqual(value, mem_[0x01FF]);
		}

		TEST_METHOD(PHA_pushes_A_register_value_onto_the_stack_two_times)
		{
			int8_t firstValue = 5;
			int8_t secondValue = 5;
			Assert::AreNotEqual(firstValue, mem_[0x01FF]);
			Assert::AreNotEqual(secondValue, mem_[0x01FE]);

			reg_.A = firstValue;
			ie_.PHA();
			reg_.A = secondValue;
			ie_.PHA();

			Assert::AreEqual(firstValue, mem_[0x01FF]);
			Assert::AreEqual(secondValue, mem_[0x01FE]);
		}

		TEST_METHOD(PHA_decrements_stack_pointer)
		{
			Assert::AreEqual(uint8_t(0xFF), reg_.SP);

			ie_.PHA();

			Assert::AreEqual(uint8_t(0xFE), reg_.SP);
		}

		TEST_METHOD(PHA_decrements_stack_pointer_two_times)
		{
			Assert::AreEqual(uint8_t(0xFF), reg_.SP);

			ie_.PHA();
			ie_.PHA();

			Assert::AreEqual(uint8_t(0xFD), reg_.SP);
		}
	};
}
