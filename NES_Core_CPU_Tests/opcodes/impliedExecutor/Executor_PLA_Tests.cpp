#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodes/impliedExecutor.h"
#include "nes/cpu/opcodes/immediateExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_ImpliedExecutor
{
	TEST_CLASS(PLA_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::opcodes::ImpliedExecutor ie_;
		nes::cpu::opcodes::ImmediateExecutor immediateExecHelper_;


		PLA_Tests() :
			reg_(),
			ie_(reg_, mem_),
			immediateExecHelper_(reg_, mem_)
		{

		}

		TEST_METHOD(PLA_pulls_value_from_stack_to_A_register)
		{
			int8_t value = 17;
			immediateExecHelper_.LDA(value);
			ie_.PHA();
			immediateExecHelper_.LDA(0);

			ie_.PLA();

			Assert::AreEqual(reg_.A, value);
		}

		TEST_METHOD(PLA_pulls_value_from_stack_to_A_register_for_the_second_time)
		{
			int8_t value = 5;
			immediateExecHelper_.LDA(value);
			ie_.PHA();
			int8_t value2 = 8;
			immediateExecHelper_.LDA(value2);
			ie_.PHA();

			ie_.PLA();
			Assert::AreEqual(reg_.A, value2);

			ie_.PLA();
			Assert::AreEqual(reg_.A, value);
		}

		TEST_METHOD(PLA_increments_stack_pointer)
		{
			ie_.PHA();
			Assert::AreEqual(reg_.SP, uint8_t(0xFE));

			ie_.PLA();

			Assert::AreEqual(reg_.SP, uint8_t(0xFF));
		}

		TEST_METHOD(PHP_decrements_stack_pointer_for_the_second_time)
		{
			ie_.PHA();
			ie_.PHA();
			Assert::AreEqual(reg_.SP, uint8_t(0xFD));

			ie_.PLA();
			Assert::AreEqual(reg_.SP, uint8_t(0xFE));

			ie_.PLA();
			Assert::AreEqual(reg_.SP, uint8_t(0xFF));
		}

		TEST_METHOD(PLA_sets_negative_flag_when_result_lt_zero)
		{
			int8_t value = -5;
			immediateExecHelper_.LDA(value);
			ie_.PHA();

			ie_.PLA();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(PLA_resets_negative_flag_when_result_equal_to_zero)
		{
			int8_t value = 0;
			immediateExecHelper_.LDA(value);
			ie_.PHA();
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));

			ie_.PLA();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(PLA_resets_negative_flag_when_result_gt_zero)
		{
			int8_t value = 55;
			immediateExecHelper_.LDA(value);
			ie_.PHA();
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));

			ie_.PLA();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(PLA_sets_zero_flag_when_result_equal_to_zero)
		{
			int8_t value = 0;
			immediateExecHelper_.LDA(value);
			ie_.PHA();

			ie_.PLA();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(PLA_resets_zero_flag_when_result_lt_zero)
		{
			int8_t value = -52;
			immediateExecHelper_.LDA(value);
			ie_.PHA();
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));

			ie_.PLA();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(PLA_resets_zero_flag_when_result_gt_zero)
		{
			int8_t value = 27;
			immediateExecHelper_.LDA(value);
			ie_.PHA();
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));

			ie_.PLA();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

	};
}
