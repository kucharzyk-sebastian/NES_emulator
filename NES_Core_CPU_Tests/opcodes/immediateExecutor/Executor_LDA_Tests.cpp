#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodes/immediateExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_ImmediateExecutor
{
	TEST_CLASS(LDA_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::opcodes::ImmediateExecutor ie_;


		LDA_Tests() :
			reg_(),
			ie_(reg_, mem_)
		{
		}

		TEST_METHOD(LDA_loads_value_to_A_register)
		{
			int8_t val = 3;

			ie_.LDA(val);

			Assert::AreEqual(reg_.A, val);
		}

		TEST_METHOD(LDA_does_not_change_any_flags_when_not_needed)
		{
			auto flags = reg_.PS;

			ie_.LDA(uint8_t(3));

			Assert::IsTrue(reg_.PS == flags);
		}

		TEST_METHOD(LDA_sets_zero_flag_for_zero)
		{
			ie_.LDA(uint8_t(3));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.LDA(uint8_t(0));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(LDA_resets_zero_flag_for_positive)
		{
			ie_.LDA(uint8_t(0));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
			
			ie_.LDA(uint8_t(3));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(LDA_resets_zero_flag_for_negative)
		{
			ie_.LDA(uint8_t(0));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.LDA(uint8_t(-2));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(LDA_sets_negative_flag_for_negative_number)
		{
			ie_.LDA(uint8_t(3));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.LDA(uint8_t(-2));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(LDA_resets_negative_flag_for_positive)
		{
			ie_.LDA(uint8_t(-2));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.LDA(uint8_t(3));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(LDA_resets_negative_flag_for_zero)
		{
			ie_.LDA(uint8_t(-2));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.LDA(uint8_t(0));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}
	};
}
