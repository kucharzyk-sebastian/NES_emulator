#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include  "nes/cpu/opcodes/implied/executor.h"
#include  "nes/cpu/opcodes/immediate/executor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_Implied_Executor
{
	TEST_CLASS(DEX_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::cpu::opcodes::implied::Executor ie_;
		nes::cpu::opcodes::immediate::Executor immediateExecHelper_;


		DEX_Tests() :
			reg_(),
			ie_(reg_),
			immediateExecHelper_(reg_)
		{

		}

		TEST_METHOD(DEX_decrements_register_X_value_by_one)
		{
			int8_t value = 5;
			immediateExecHelper_.LDX(value);

			ie_.DEX();

			Assert::AreEqual(reg_.X, --value);
		}

		TEST_METHOD(DEX_sets_zero_flag_when_result_equal_zero)
		{
			immediateExecHelper_.LDX(int8_t(1));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.DEX();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(DEX_resets_zero_flag_when_result_lt_zero)
		{
			immediateExecHelper_.LDX(int8_t(0));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.DEX();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(DEX_resets_zero_flag_when_result_gt_zero)
		{
			immediateExecHelper_.LDX(int8_t(5));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.DEX();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(DEX_sets_negative_flag_when_result_lt_zero)
		{
			immediateExecHelper_.LDX(int8_t(0));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.DEX();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(DEX_resets_negative_flag_when_result_gt_zero)
		{
			immediateExecHelper_.LDX(int8_t(-128));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.DEX();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(DEX_resets_negative_flag_when_result_equal_zero)
		{
			immediateExecHelper_.LDX(int8_t(1));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.DEX();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}
	};
}