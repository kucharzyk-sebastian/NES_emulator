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
		uint16_t stackPage_ = uint16_t(0x0100);
		using PSType = std::bitset<nes::cpu::registers::Registers::PSSize>;


		PHP_Tests() :
			reg_(),
			ie_(reg_, mem_)
		{

		}

		TEST_METHOD(PHP_pushes_processor_status_flags_value_onto_the_stack)
		{
			reg_.PS = PSType(0b11001011);
			Assert::AreNotEqual(unsigned long(uint8_t(mem_[stackPage_ + reg_.SP])), reg_.PS.to_ulong());

			ie_.PHP();

			Assert::AreEqual(reg_.PS.to_ulong() | 0b00110000, unsigned long(uint8_t(mem_[stackPage_ + reg_.SP + 1])));
		}

		TEST_METHOD(PHP_pushes_processor_status_flags_value_onto_the_stack_two_times_always_with_4_and_5_bits_set)
		{
			auto firstPS = reg_.PS = PSType(0b11001011);
			auto secondPS = PSType(0b010100110);
			Assert::AreNotEqual(firstPS.to_ulong(), PSType(mem_[stackPage_ + reg_.SP - 1]).to_ulong());
			Assert::AreNotEqual(secondPS.to_ulong(), PSType(mem_[stackPage_ + reg_.SP]).to_ulong());

			ie_.PHP();
			reg_.PS = secondPS;
			ie_.PHP();

			Assert::AreEqual(firstPS.to_ulong() | 0b00110000, PSType(mem_[stackPage_ + reg_.SP + 2]).to_ulong());
			Assert::AreEqual(secondPS.to_ulong() | 0b00110000, PSType(mem_[stackPage_ + reg_.SP + 1]).to_ulong() | 0b00110000);
		}

		TEST_METHOD(PHP_decrements_stack_pointer)
		{
			uint8_t previousStack = reg_.SP;

			ie_.PHP();

			Assert::AreEqual(uint8_t(previousStack - 1), reg_.SP);
		}

		TEST_METHOD(PHP_decrements_stack_pointer_two_times)
		{
			uint8_t previousStack = reg_.SP;
			
			ie_.PHA();
			ie_.PHA();

			Assert::AreEqual(uint8_t(previousStack - 2), reg_.SP);
		}

	};
}
