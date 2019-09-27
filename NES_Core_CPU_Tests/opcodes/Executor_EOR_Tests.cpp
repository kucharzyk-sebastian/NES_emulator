#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(EOR_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor ie_;


		EOR_Tests() :
			reg_(),
			ie_(reg_, mem_)
		{
		}

		TEST_METHOD(EOR_performs_binary_exclusive_or_between_A_register_and_immediate_value)
		{
			reg_.A = int8_t(0b00001011);

			ie_.EOR(int8_t(0b00100110));

			Assert::AreEqual(int8_t(0b00101101), reg_.A);
		}

		TEST_METHOD(EOR_performs_binary_exclusive_or_between_A_register_and_value_from_memory)
		{
			reg_.A = int8_t(0b00001011);
			int8_t value = 0b00100110;
			uint16_t address = 0x0123;
			mem_[address] = value;

			ie_.EOR(address);

			Assert::AreEqual(int8_t(0b00101101), reg_.A);
		}

		TEST_METHOD(EOR_sets_zero_flag_for_zero_result)
		{
			reg_.A = int8_t(0b00100010);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.EOR(int8_t(0b00100010));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(EOR_resets_zero_flag_for_positive_result)
		{
			reg_.A = int8_t(0b00000000);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.EOR(int8_t(0b00010001));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(EOR_resets_zero_flag_for_negative_result)
		{
			reg_.A = int8_t(0b00000000);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.EOR(int8_t(0b10001010));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(EOR_sets_negative_flag_for_negative_results)
		{
			reg_.A = int8_t(0b00001100);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.EOR(int8_t(0b10101000));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(EOR_resets_negative_flag_for_positive_results)
		{
			reg_.A = int8_t(0b10010101);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.EOR(int8_t(0b10010110));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(EOR_resets_negative_flag_for_zero_result)
		{
			reg_.A = int8_t(0b10011001);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.EOR(int8_t(0b10011001));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

	};
}
