#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(PLP_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor ie_;
		using PSType = std::bitset<nes::cpu::registers::Registers::PSSize>;


		PLP_Tests() :
			reg_(),
			ie_(reg_, mem_)
		{

		}

		TEST_METHOD(PLP_pulls_value_from_stack_to_processor_status_register_ignoring_bit_4_and_5)
		{
			reg_.PS = PSType(0b011011110);
			mem_[0x01FF] = int8_t(0b01101101);
			reg_.SP = uint8_t(0x01FE);

			ie_.PLP();

			Assert::AreEqual(PSType(0b01011101).to_string(), reg_.PS.to_string());
		}

		TEST_METHOD(PLP_pulls_value_from_stack_to_processor_status_register_two_times_ignoring_bit_4_and_5)
		{
			reg_.PS = PSType(0b11011110);
			mem_[0x01FF] = int8_t(0b01101101);
			mem_[0x01FE] = int8_t(0b01111100);
			reg_.SP = uint8_t(0x01FD);

			ie_.PLP();
			uint8_t firstPull = reg_.PS.to_ullong();
			reg_.PS = PSType(0b011011110);
			ie_.PLP();
			uint8_t secondPull = reg_.PS.to_ullong();

			Assert::AreEqual(uint8_t(0b01011100), firstPull);
			Assert::AreEqual(uint8_t(0b01011101), secondPull);
		}

		TEST_METHOD(PLP_increments_stack_pointer)
		{
			reg_.SP = uint8_t(0xFE);
			Assert::AreEqual(uint8_t(0xFE), reg_.SP);

			ie_.PLP();

			Assert::AreEqual(uint8_t(0xFF), reg_.SP);
		}

		TEST_METHOD(PLP_increments_stack_pointer_for_the_second_time)
		{
			reg_.SP = uint8_t(0xFD);
			Assert::AreEqual(uint8_t(0xFD), reg_.SP);

			ie_.PLP();
			ie_.PLP();

			Assert::AreEqual(uint8_t(0xFF), reg_.SP);
		}
	};
}
