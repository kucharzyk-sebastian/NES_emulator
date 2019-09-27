#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(TXA_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor ie_;


		TXA_Tests() :
			reg_(),
			ie_(reg_, mem_)
		{

		}

		TEST_METHOD(TXA_copies_value_from_register_X_to_A)
		{
			reg_.X = int8_t(76);
			Assert::AreNotEqual(reg_.X, reg_.A);

			ie_.TXA();

			Assert::AreEqual(reg_.X, reg_.A);
		}

		TEST_METHOD(TXA_sets_negative_flag_when_result_lt_zero)
		{
			reg_.X = int8_t(-59);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.TXA();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(TXA_resets_negative_flag_when_result_equal_to_zero)
		{
			reg_.X = int8_t(0);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.TXA();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(TXA_resets_negative_flag_when_result_gt_zero)
		{
			reg_.X = int8_t(91);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.TXA();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(TXA_sets_zero_flag_when_result_equal_to_zero)
		{
			reg_.X = int8_t(0);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.TXA();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(TXA_resets_zero_flag_when_result_lt_zero)
		{
			reg_.X = int8_t(-11);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.TXA();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(TXA_resets_zero_flag_when_result_gt_zero)
		{
			reg_.X = int8_t(19);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.TXA();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

	};
}
