#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(STA_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor oe_;


		STA_Tests() :
			reg_(),
			oe_(reg_, mem_)
		{
		}

		TEST_METHOD(STA_stores_A_register_in_memory)
		{
			int8_t val = reg_.A = 3;
			uint16_t address = 0x07c2;

			oe_.STA(address);

			Assert::AreEqual(val, mem_[address]);
		}
	};
}
