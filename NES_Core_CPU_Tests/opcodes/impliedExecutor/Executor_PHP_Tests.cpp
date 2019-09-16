#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodes/impliedExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_ImpliedExecutor
{
	TEST_CLASS(PHP_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::opcodes::ImpliedExecutor ie_;
		using PSType = std::bitset<nes::cpu::registers::Registers::PSSize>;

		PHP_Tests() :
			reg_(),
			ie_(reg_, mem_)
		{

		}

		TEST_METHOD(PHP_pushes_processor_status_flags_value_onto_the_stack)
		{
			Assert::AreNotEqual(PSType(mem_[0x01FF]).to_string(), reg_.PS.to_string());

			ie_.PHP();

			Assert::AreEqual(reg_.PS.to_string(), PSType(mem_[0x01FF]).to_string());
		}

		TEST_METHOD(PHP_pushes_processor_status_flags_value_onto_the_stack_two_times)
		{
			auto firstPS = reg_.PS;
			auto secondPS = PSType(0b010100110);
			Assert::AreNotEqual(firstPS.to_string(), PSType(mem_[0x01FF]).to_string());
			Assert::AreNotEqual(secondPS.to_string(), PSType(mem_[0x01FF]).to_string());

			ie_.PHP();
			reg_.PS = secondPS;
			ie_.PHP();

			Assert::AreEqual(firstPS.to_string(), PSType(mem_[0x01FF]).to_string());
			Assert::AreEqual(secondPS.to_string(), PSType(mem_[0x01FE]).to_string());
		}

		TEST_METHOD(PHP_decrements_stack_pointer)
		{
			Assert::AreEqual(uint8_t(0xFF), reg_.SP);

			ie_.PHP();

			Assert::AreEqual(uint8_t(0xFE), reg_.SP);
		}

		TEST_METHOD(PHP_decrements_stack_pointer_two_times)
		{
			Assert::AreEqual(uint8_t(0xFF), reg_.SP);
			
			ie_.PHA();
			ie_.PHA();

			Assert::AreEqual(uint8_t(0xFD), reg_.SP);
		}

	};
}
