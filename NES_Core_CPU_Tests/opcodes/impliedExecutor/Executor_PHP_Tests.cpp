#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodes/impliedExecutor.h"
#include "nes/cpu/opcodes/immediateExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_ImpliedExecutor
{
	TEST_CLASS(PHP_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::opcodes::ImpliedExecutor ie_;
		nes::cpu::opcodes::ImmediateExecutor immediateExecHelper_;


		PHP_Tests() :
			reg_(),
			ie_(reg_, mem_),
			immediateExecHelper_(reg_, mem_)
		{

		}

		TEST_METHOD(PHP_pushes_processor_status_flag_value_onto_the_stack)
		{

			ie_.PHP();

			Assert::AreEqual(std::bitset<nes::cpu::registers::Registers::PSSize>(mem_[0x01FF]).to_string(), reg_.PS.to_string());
		}

		TEST_METHOD(PHP_pushes_processor_status_flag_value_onto_the_stack_for_the_second_time)
		{
			ie_.PHP();

			ie_.PHP();

			Assert::AreEqual(std::bitset<nes::cpu::registers::Registers::PSSize>(mem_[0x01FE]).to_string(), reg_.PS.to_string());
		}

		TEST_METHOD(PHP_decrements_stack_pointer)
		{
			Assert::AreEqual(reg_.SP, uint8_t(0xFF));

			ie_.PHP();

			Assert::AreEqual(reg_.SP, uint8_t(0xFE));
		}

		TEST_METHOD(PHP_decrements_stack_pointer_for_the_second_time)
		{
			Assert::AreEqual(reg_.SP, uint8_t(0xFF));
			ie_.PHA();

			ie_.PHA();

			Assert::AreEqual(reg_.SP, uint8_t(0xFD));
		}

	};
}
