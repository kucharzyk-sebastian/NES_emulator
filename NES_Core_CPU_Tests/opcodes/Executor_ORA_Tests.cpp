#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(ORA_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor oe_;


		ORA_Tests() :
			reg_(),
			oe_(reg_, mem_)
		{
		}

		TEST_METHOD(ORA_performs_binary_inclusive_or_between_register_A_and_immediate_value)
		{
			reg_.A = int8_t(0b00001011);

			oe_.ORA(int8_t(0b00100110));

			Assert::AreEqual(int8_t(0b00101111), reg_.A);
		}

		TEST_METHOD(ORA_performs_binary_inclusive_or_between_register_A_and_value_from_memory)
		{
			uint16_t address = 0x0554;
			mem_[address] = 0b00100110;
			reg_.A = int8_t(0b00001011);

			oe_.ORA(address);

			Assert::AreEqual(int8_t(0b00101111), reg_.A);
		}

		TEST_METHOD(ORA_sets_zero_flag_for_zero_result)
		{
			reg_.A = int8_t(0b00000000);
			reg_.PS.reset(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.ORA(int8_t(0b00000000));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(ORA_resets_zero_flag_for_positive_result)
		{
			reg_.A = int8_t(0b00000000);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.ORA(int8_t(0b00010001));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(ORA_resets_zero_flag_for_negative_result)
		{
			reg_.A = int8_t(0b00000000);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.ORA(int8_t(0b10001010));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(ORA_sets_negative_flag_for_negative_results)
		{
			reg_.A = int8_t(0b00001100);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.ORA(int8_t(0b10101000));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(ORA_resets_negative_flag_for_positive_results)
		{
			reg_.A = int8_t(0b00010101);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.ORA(int8_t(0b00010110));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(ORA_resets_negative_flag_for_zero_result)
		{
			reg_.A = int8_t(0b00000000);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.ORA(int8_t(0b00000000));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}
	};
}
