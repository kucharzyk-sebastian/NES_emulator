#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodes/immediateExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_ImmediateExecutor
{
	TEST_CLASS(AND_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::opcodes::ImmediateExecutor ie_;


		AND_Tests() :
			reg_(),
			ie_(reg_, mem_)
		{
		}

		TEST_METHOD(AND_performs_binary_and_operation_between_immediate_value_and_A_register)
		{
			reg_.A = int8_t(0b00001011);

			ie_.AND(int8_t(0b00100110));

			Assert::AreEqual(int8_t(0b00000010), reg_.A);
		}
	};
}
