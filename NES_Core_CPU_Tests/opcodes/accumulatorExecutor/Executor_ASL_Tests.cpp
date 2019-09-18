#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"
#include  "nes/cpu/opcodes/accumulatorExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_AccumulatorExecutor
{
	TEST_CLASS(ASL_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::cpu::opcodes::AccumulatorExecutor ae_;
		nes::memory::Memory mem_;


		ASL_Tests() :
			reg_(),
			ae_(reg_, mem_)
		{

		}

		TEST_METHOD(ASL_shifts_A_register_left)
		{
			reg_.A = int8_t(0b11101110);
			Assert::AreNotEqual(int8_t(0b11011100), reg_.A);

			ae_.ASL();

			Assert::AreEqual(int8_t(0b11011100), reg_.A);
		}
	};
}
