#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(RTI_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor oe_;


		RTI_Tests() :
			reg_(),
			oe_(reg_, mem_)
		{
			reg_.PC = 0x0600;
		}

		TEST_METHOD(RTI_loads_Program_Counter_and_Processor_Status_from_stack_with_skipping_bits_4_and_5)
		{
			reg_.PS = int8_t(0b01011000);
			uint16_t newPC = 0x14cd;
			mem_[0x01FF] = 0x14;
			mem_[0x01FE] = int8_t(0xcd);
			uint8_t newPS = 0b01101000;
			mem_[0x01FD] = newPS;
			reg_.SP = 0xFC;

			oe_.RTI();

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(newPC), int(reg_.PC));
			Assert::AreEqual(int(0b01011000), int(reg_.PS.to_ulong()));
		}
	};
}
