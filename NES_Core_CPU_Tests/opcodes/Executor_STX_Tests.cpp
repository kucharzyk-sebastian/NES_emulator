#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(STX_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor oe_;


		STX_Tests() :
			reg_(),
			oe_(reg_, mem_)
		{
		}

		TEST_METHOD(STX_stores_X_register_in_memory)
		{
			int8_t val = reg_.X = -53;
			uint16_t address = 0x0412;

			oe_.STX(address);

			Assert::AreEqual(val, mem_[address]);
		}
	};
}
