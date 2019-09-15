#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodes/impliedExecutor.h"
#include "nes/cpu/opcodes/immediateExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_ImpliedExecutor
{
	TEST_CLASS(PHA_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::opcodes::ImpliedExecutor ie_;
		nes::cpu::opcodes::ImmediateExecutor immediateExecHelper_;


		PHA_Tests() :
			reg_(),
			ie_(reg_, mem_),
			immediateExecHelper_(reg_, mem_)
		{

		}

		TEST_METHOD(PHA_pushes_A_register_value_onto_the_stack)
		{
			int8_t value = 5;
			immediateExecHelper_.LDA(value);

			ie_.PHA();

			Assert::AreEqual(mem_[0x01FF], value);
		}

		TEST_METHOD(PHA_pushes_A_register_value_onto_the_stack_for_the_second_time)
		{
			int8_t value = 5;
			immediateExecHelper_.LDA(value);
			ie_.PHA();

			ie_.PHA();

			Assert::AreEqual(mem_[0x01FE], value);
		}

		TEST_METHOD(PHA_decrements_stack_pointer)
		{
			Assert::AreEqual(reg_.SP, uint8_t(0xFF));

			ie_.PHA();

			Assert::AreEqual(reg_.SP, uint8_t(0xFE));
		}

		TEST_METHOD(PHA_decrements_stack_pointer_for_the_second_time)
		{
			Assert::AreEqual(reg_.SP, uint8_t(0xFF));
			ie_.PHA();

			ie_.PHA();

			Assert::AreEqual(reg_.SP, uint8_t(0xFD));
		}
	};
}
