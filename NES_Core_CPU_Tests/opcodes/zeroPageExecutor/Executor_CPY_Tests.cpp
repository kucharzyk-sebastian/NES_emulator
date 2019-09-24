#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodes/zeroPageExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_ZeroPageExecutor
{
	TEST_CLASS(CPY_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::opcodes::ZeroPageExecutor zpe_;


		CPY_Tests() :
			reg_(),
			zpe_(reg_, mem_)
		{
		}

		TEST_METHOD(CPY_compares_register_A_and_value_from_memory_in_zero_page_mode)
		{
			int8_t val = 8;
			reg_.Y = val;
			uint8_t address = 0x75;
			mem_[address] = val;
			reg_.PS.reset(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			zpe_.CPY(address);

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}
	};
}
