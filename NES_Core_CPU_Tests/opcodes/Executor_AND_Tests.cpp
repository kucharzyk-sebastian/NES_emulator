#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(AND_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor oe_;


		AND_Tests() :
			reg_(),
			oe_(reg_, mem_)
		{
		}

		TEST_METHOD(AND_performs_binary_and_between_A_register_and_immediate_value)
		{
			reg_.A = int8_t(0b00001011);

			oe_.AND(int8_t(0b00100110));

			Assert::AreEqual(int8_t(0b00000010), reg_.A);
		}

		TEST_METHOD(AND_performs_binary_and_between_A_register_and_value_from_memory)
		{
			reg_.A = int8_t(0b00001011);
			int8_t val = 0b00100110;
			uint16_t address = 0xa070;
			mem_[address] = val;

			oe_.AND(address);

			Assert::AreEqual(int8_t(0b00000010), reg_.A);
		}

		TEST_METHOD(AND_sets_zero_flag_for_zero_result)
		{
			reg_.A = int8_t(0b00100010);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.AND(int8_t(0b00001000));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(AND_resets_zero_flag_for_positive_result)
		{
			reg_.A = int8_t(0b00001111);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.AND(int8_t(0b00001010));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(AND_resets_zero_flag_for_negative_result)
		{
			reg_.A = int8_t(0b10001111);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.AND(int8_t(0b10001110));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(AND_sets_negative_flag_for_negative_results)
		{
			reg_.A = int8_t(0b10001100);
			reg_.PS.reset(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.AND(int8_t(0b10000000));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(AND_resets_negative_flag_for_positive_results)
		{
			reg_.A = int8_t(0b10011001);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.AND(int8_t(0b00011000));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(AND_resets_negative_flag_for_zero_result)
		{
			reg_.A = int8_t(0b10011001);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.AND(int8_t(0b00100100));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

	};
}
