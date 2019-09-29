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

		TEST_METHOD(PLP_pulls_value_from_stack_to_processor_status_register)
		{
			auto value = PSType(0b01101101);
			mem_[0x01FF] = static_cast<int8_t>(value.to_ulong());
			reg_.SP = uint8_t(0x01FE);
			Assert::AreNotEqual(value.to_string(), reg_.PS.to_string());

			ie_.PLP();

			Assert::AreEqual(PSType(mem_[0x01FF]).to_string(), reg_.PS.to_string());
		}

		TEST_METHOD(PLP_pulls_value_from_stack_to_processor_status_register_two_times)
		{
			auto firstValue = PSType(0b01101101);
			auto secondValue = PSType(0b00000111);
			mem_[0x01FF] = static_cast<int8_t>(firstValue.to_ulong());
			mem_[0x01FE] = static_cast<int8_t>(secondValue.to_ulong());
			reg_.SP = uint8_t(0x01FD);
			Assert::AreNotEqual(firstValue.to_string(), reg_.PS.to_string());
			Assert::AreNotEqual(secondValue.to_string(), reg_.PS.to_string());

			ie_.PLP();
			auto firstPull = reg_.PS;
			ie_.PLP();
			auto secondPull = reg_.PS;

			Assert::AreEqual(secondValue.to_string(), firstPull.to_string());
			Assert::AreEqual(firstValue.to_string(), secondPull.to_string());
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
