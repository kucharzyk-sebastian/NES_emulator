#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodes/impliedExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_ImpliedExecutor
{
	TEST_CLASS(TXS_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::opcodes::ImpliedExecutor ie_;


		TXS_Tests() :
			reg_(),
			ie_(reg_, mem_)
		{

		}

		TEST_METHOD(TXS_copies_value_from_register_X_to_Stack_Pointer)
		{
			reg_.X = int8_t(0xCA);
			Assert::AreNotEqual(uint8_t(reg_.X), reg_.SP);

			ie_.TXS();

			Assert::AreEqual(uint8_t(reg_.X), reg_.SP);
		}
	};
}
