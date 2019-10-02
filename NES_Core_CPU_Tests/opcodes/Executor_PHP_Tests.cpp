#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(PHP_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor ie_;
		using PSType = std::bitset<nes::cpu::registers::Registers::PSSize>;

		PHP_Tests() :
			reg_(),
			ie_(reg_, mem_)
		{

		}

		TEST_METHOD(PHP_pushes_processor_status_flags_value_onto_the_stack)
		{
			reg_.PS = PSType(0b11001011);
			Assert::AreNotEqual(unsigned long(uint8_t(mem_[0x01FF])), reg_.PS.to_ulong());

			ie_.PHP();

			Assert::AreEqual(reg_.PS.to_ulong() | 0b00110000, unsigned long(uint8_t(mem_[0x01FF])));
		}

		TEST_METHOD(PHP_pushes_processor_status_flags_value_onto_the_stack_two_times_always_with_4_and_5_bits_set)
		{
			auto firstPS = reg_.PS = PSType(0b11001011);
			auto secondPS = PSType(0b010100110);
			Assert::AreNotEqual(firstPS.to_ulong(), PSType(mem_[0x01FF]).to_ulong());
			Assert::AreNotEqual(secondPS.to_ulong(), PSType(mem_[0x01FF]).to_ulong());

			ie_.PHP();
			reg_.PS = secondPS;
			ie_.PHP();

			Assert::AreEqual(firstPS.to_ulong() | 0b00110000, PSType(mem_[0x01FF]).to_ulong());
			Assert::AreEqual(secondPS.to_ulong() | 0b00110000, PSType(mem_[0x01FE]).to_ulong() | 0b00110000);
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
