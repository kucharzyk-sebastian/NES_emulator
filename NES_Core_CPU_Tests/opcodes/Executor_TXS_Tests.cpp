#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(TXS_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor oe_;


		TXS_Tests() :
			reg_(),
			oe_(reg_, mem_)
		{

		}

		TEST_METHOD(TXS_copies_value_from_register_X_to_Stack_Pointer)
		{
			reg_.X = int8_t(0xCA);
			Assert::AreNotEqual(uint8_t(reg_.X), reg_.SP);

			oe_.TXS();

			Assert::AreEqual(uint8_t(reg_.X), reg_.SP);
		}
	};
}
