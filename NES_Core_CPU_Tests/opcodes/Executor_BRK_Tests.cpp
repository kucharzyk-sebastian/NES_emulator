#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(BRK_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor oe_;
		uint16_t stackPage_ = uint16_t(0x0100);


		BRK_Tests() :
			reg_(),
			oe_(reg_, mem_)
		{
			
		}

		TEST_METHOD(BRK_pushes_Program_Counter_and_Processor_Status_onto_the_stack)
		{
			reg_.PC = 0xaf38;
			reg_.PS = 0b00110101;
			
			oe_.BRK();

			Assert::AreEqual(int8_t(0xaf), mem_[stackPage_ + reg_.SP + 3]);
			Assert::AreEqual(int8_t(0x38), mem_[stackPage_ + reg_.SP + 2]);
			Assert::AreEqual(uint8_t(reg_.PS.to_ulong()), uint8_t(mem_[stackPage_ + reg_.SP + 1]));
		}

		TEST_METHOD(BRK_loads_interrupt_vector_to_PC)
		{
			uint16_t interruptVector = 0xda71;
			mem_[0xFFFF] = int8_t(0xda);
			mem_[0xFFFE] = 0x71;

			oe_.BRK();

			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(interruptVector), int(reg_.PC));
		}

		TEST_METHOD(BRK_sets_Break_flag)
		{
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Break)]);
			
			oe_.BRK();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Break)]);
		}
	};
}
