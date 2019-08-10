#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/cpu/opcodes/immediate/executor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_Immediate_Executor
{
	TEST_CLASS(AND_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::cpu::opcodes::immediate::Executor ie_;


		AND_Tests() :
			reg_(),
			ie_(reg_)
		{
		}

		TEST_METHOD(AND_performs_logical_and)
		{
			ie_.AND(int8_t(3));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
			ie_.ADC(int8_t(1));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

	};
}
