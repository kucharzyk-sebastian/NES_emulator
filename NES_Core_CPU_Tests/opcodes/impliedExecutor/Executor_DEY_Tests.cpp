#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include  "nes/cpu/opcodes/impliedExecutor.h"
#include  "nes/cpu/opcodes/immediateExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_ImpliedExecutor
{
	TEST_CLASS(DEY_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::cpu::opcodes::ImpliedExecutor ie_;
		nes::cpu::opcodes::ImmediateExecutor immediateExecHelper_;


		DEY_Tests() :
			reg_(),
			ie_(reg_),
			immediateExecHelper_(reg_)
		{

		}

		TEST_METHOD(DEY_decrements_register_Y_value_by_one)
		{
			int8_t value = 5;
			immediateExecHelper_.LDY(value);

			ie_.DEY();

			Assert::AreEqual(reg_.Y, --value);
		}

		TEST_METHOD(DEY_sets_zero_flag_when_result_equal_zero)
		{
			immediateExecHelper_.LDY(int8_t(1));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.DEY();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(DEY_resets_zero_flag_when_result_lt_zero)
		{
			immediateExecHelper_.LDY(int8_t(0));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.DEY();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(DEY_resets_zero_flag_when_result_gt_zero)
		{
			immediateExecHelper_.LDY(int8_t(5));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.DEY();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(DEY_sets_negative_flag_when_result_lt_zero)
		{
			immediateExecHelper_.LDY(int8_t(0));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.DEY();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(DEY_resets_negative_flag_when_result_gt_zero)
		{
			immediateExecHelper_.LDY(int8_t(-128));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.DEY();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(DEY_resets_negative_flag_when_result_equal_zero)
		{
			immediateExecHelper_.LDY(int8_t(1));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.DEY();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}
	};
}
