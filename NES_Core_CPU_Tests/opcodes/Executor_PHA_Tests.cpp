#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(PHA_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor oe_;
		uint16_t stackPage_ = uint16_t(0x0100);


		PHA_Tests() :
			reg_(),
			oe_(reg_, mem_)
		{

		}

		TEST_METHOD(PHA_pushes_A_register_value_onto_the_stack)
		{
			int8_t value = 5;
			reg_.A = value;
			Assert::AreNotEqual(value, mem_[stackPage_ + reg_.SP]);

			oe_.PHA();

			Assert::AreEqual(value, mem_[stackPage_ + reg_.SP + 1]);
		}

		TEST_METHOD(PHA_pushes_A_register_value_onto_the_stack_two_times)
		{
			uint8_t previousSP = reg_.SP;
			int8_t firstValue = 5;
			int8_t secondValue = 5;
			Assert::AreNotEqual(firstValue, mem_[stackPage_ + reg_.SP]);
			Assert::AreNotEqual(secondValue, mem_[stackPage_ + reg_.SP - 1]);

			reg_.A = firstValue;
			oe_.PHA();
			reg_.A = secondValue;
			oe_.PHA();

			Assert::AreEqual(firstValue, mem_[stackPage_ + reg_.SP + 2]);
			Assert::AreEqual(secondValue, mem_[stackPage_ + reg_.SP + 1]);
		}

		TEST_METHOD(PHA_decrements_stack_pointer)
		{
			uint8_t previousSP = reg_.SP;

			oe_.PHA();

			Assert::AreEqual(uint8_t(previousSP - 1), reg_.SP);
		}

		TEST_METHOD(PHA_decrements_stack_pointer_two_times)
		{
			uint8_t previousSP = reg_.SP;

			oe_.PHA();
			oe_.PHA();

			Assert::AreEqual(uint8_t(previousSP - 2), reg_.SP);
		}
	};
}
