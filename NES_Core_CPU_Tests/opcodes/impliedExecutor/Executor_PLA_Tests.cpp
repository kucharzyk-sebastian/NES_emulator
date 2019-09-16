#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodes/impliedExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_ImpliedExecutor
{
	TEST_CLASS(PLA_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::opcodes::ImpliedExecutor ie_;


		PLA_Tests() :
			reg_(),
			ie_(reg_, mem_)
		{

		}

		TEST_METHOD(PLA_pulls_value_from_stack_to_A_register)
		{
			int8_t value = 17;
			mem_[0x01FF] = value;
			reg_.SP = uint8_t(0xFE);
			Assert::AreNotEqual(value, reg_.A);

			ie_.PLA();

			Assert::AreEqual(value, reg_.A);
		}

		TEST_METHOD(PLA_pulls_value_from_stack_to_A_register_two_times)
		{
			int8_t firstValue = 17;
			int8_t secondValue = -15;
			mem_[0x01FF] = firstValue;
			mem_[0x01FE] = secondValue;
			reg_.SP = uint8_t(0xFD);
			Assert::AreNotEqual(firstValue, reg_.A);
			Assert::AreNotEqual(secondValue, reg_.A);

			ie_.PLA();
			int8_t firstPull = reg_.A;
			ie_.PLA();
			int8_t secondPull = reg_.A;

			Assert::AreEqual(secondValue, firstPull);
			Assert::AreEqual(firstValue, secondPull);
		}

		TEST_METHOD(PLA_increments_stack_pointer)
		{
			reg_.SP = uint8_t(0xFE);
			Assert::AreEqual(uint8_t(0xFE), reg_.SP);

			ie_.PLA();

			Assert::AreEqual(uint8_t(0xFF), reg_.SP);
		}

		TEST_METHOD(PLA_increments_stack_pointer_for_the_second_time)
		{
			reg_.SP = uint8_t(0xFD);
			Assert::AreEqual(uint8_t(0xFD), reg_.SP);

			ie_.PLA();
			ie_.PLA();

			Assert::AreEqual(uint8_t(0xFF), reg_.SP);
		}

		TEST_METHOD(PLA_sets_negative_flag_when_result_lt_zero)
		{
			mem_[0x01FF] = int8_t(-5);
			reg_.SP = uint8_t(0xFE);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.PLA();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(PLA_resets_negative_flag_when_result_equal_to_zero)
		{
			mem_[0x01FF] = int8_t(0);
			reg_.SP = uint8_t(0xFE);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.PLA();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(PLA_resets_negative_flag_when_result_gt_zero)
		{
			mem_[0x01FF] = int8_t(78);
			reg_.SP = uint8_t(0xFE);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.PLA();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(PLA_sets_zero_flag_when_result_equal_to_zero)
		{
			mem_[0x01FF] = int8_t(0);
			reg_.SP = uint8_t(0xFE);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.PLA();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(PLA_resets_zero_flag_when_result_lt_zero)
		{
			mem_[0x01FF] = int8_t(-5);
			reg_.SP = uint8_t(0xFE);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.PLA();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(PLA_resets_zero_flag_when_result_gt_zero)
		{
			mem_[0x01FF] = int8_t(124);
			reg_.SP = uint8_t(0xFE);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.PLA();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

	};
}
