#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(STY_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor oe_;


		STY_Tests() :
			reg_(),
			oe_(reg_, mem_)
		{
		}

		TEST_METHOD(STY_stores_Y_register_in_memory)
		{
			int8_t val = reg_.Y = -1;
			uint16_t address = 0x0fce;

			oe_.STY(address);

			Assert::AreEqual(val, mem_[address]);
		}
	};
}
