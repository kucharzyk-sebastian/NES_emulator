#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(TYA_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor oe_;


		TYA_Tests() :
			reg_(),
			oe_(reg_, mem_)
		{

		}

		TEST_METHOD(TYA_copies_value_from_register_Y_to_A)
		{
			reg_.Y = int8_t(41);
			Assert::AreNotEqual(reg_.Y, reg_.A);

			oe_.TYA();

			Assert::AreEqual(reg_.Y, reg_.A);
		}

		TEST_METHOD(TYA_sets_negative_flag_when_result_lt_zero)
		{
			reg_.Y = int8_t(-1);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.TYA();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(TYA_resets_negative_flag_when_result_equal_to_zero)
		{
			reg_.Y = int8_t(0);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.TYA();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(TYA_resets_negative_flag_when_result_gt_zero)
		{
			reg_.Y = int8_t(2);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.TYA();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(TYA_sets_zero_flag_when_result_equal_to_zero)
		{
			reg_.Y = int8_t(0);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.TYA();

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(TYA_resets_zero_flag_when_result_lt_zero)
		{
			reg_.Y = int8_t(-128);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.TYA();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(TYA_resets_zero_flag_when_result_gt_zero)
		{
			reg_.Y = int8_t(19);
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.TYA();

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

	};
}
