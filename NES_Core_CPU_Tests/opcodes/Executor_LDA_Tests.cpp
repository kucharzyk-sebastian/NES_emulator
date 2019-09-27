#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(LDA_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::OpcodesExecutor ie_;


		LDA_Tests() :
			reg_(),
			ie_(reg_, mem_)
		{
		}

		TEST_METHOD(LDA_loads_immediate_value_to_A_register)
		{
			int8_t val = 3;

			ie_.LDA(val);

			Assert::AreEqual(val, reg_.A);
		}

		TEST_METHOD(LDA_loads_value_from_memory_to_A_register)
		{
			int8_t val = 3;
			uint16_t address = 0x6502;
			mem_[address] = val;

			ie_.LDA(address);

			Assert::AreEqual(val, reg_.A);
		}

		TEST_METHOD(LDA_does_not_change_any_flags_when_not_needed)
		{
			auto flags = reg_.PS;

			ie_.LDA(int8_t(3));

			Assert::IsTrue(reg_.PS == flags);
		}

		TEST_METHOD(LDA_sets_zero_flag_for_zero)
		{
			reg_.A = int8_t(3);
			Assert::IsFalse(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.LDA(int8_t(0));

			Assert::IsTrue(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(LDA_resets_zero_flag_for_positive)
		{
			reg_.A = int8_t(0);
			reg_.PS.set(static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
			
			ie_.LDA(int8_t(3));

			Assert::IsFalse(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(LDA_resets_zero_flag_for_negative)
		{
			reg_.A = int8_t(0);
			reg_.PS.set(static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.LDA(int8_t(-2));

			Assert::IsFalse(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(LDA_sets_negative_flag_for_negative_number)
		{
			reg_.A = int8_t(3);
			Assert::IsFalse(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.LDA(int8_t(-2));

			Assert::IsTrue(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(LDA_resets_negative_flag_for_positive)
		{
			reg_.A = int8_t(-2);
			reg_.PS.set(static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.LDA(int8_t(3));

			Assert::IsFalse(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(LDA_resets_negative_flag_for_zero)
		{
			reg_.A = int8_t(-2);
			reg_.PS.set(static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.LDA(int8_t(0));

			Assert::IsFalse(reg_.PS[static_cast<int8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}
	};
}
