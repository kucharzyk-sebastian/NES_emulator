#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodes/immediateExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_ImmediateExecutor
{
	TEST_CLASS(ADC_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::opcodes::ImmediateExecutor ie_;


		ADC_Tests() :
			reg_(),
			ie_(reg_, mem_)
		{
			reg_.A = 0x03;
		}

		TEST_METHOD(ADC_adds_value_to_A_register)
		{
			int8_t val = 0x01;
			int8_t previousA = reg_.A;

			ie_.ADC(val);

			Assert::AreEqual(int8_t(previousA + val), reg_.A);
		}

		TEST_METHOD(ADC_adds_value_to_A_register_edge_case)
		{
			int8_t val = 0xFF;
			int8_t previousA = reg_.A;

			ie_.ADC(val);

			Assert::AreEqual(int8_t(previousA + val), reg_.A);
		}
	};
}
