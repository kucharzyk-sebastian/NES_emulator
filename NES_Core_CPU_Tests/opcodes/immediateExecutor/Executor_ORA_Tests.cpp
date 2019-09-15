#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodes/immediateExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_ImmediateExecutor
{
	TEST_CLASS(ORA_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::opcodes::ImmediateExecutor ie_;


		ORA_Tests() :
			reg_(),
			ie_(reg_, mem_)
		{
		}

		TEST_METHOD(ORA_performs_binary_inclusive_or)
		{
			ie_.LDA(int8_t(0b00001011));

			ie_.ORA(int8_t(0b00100110));

			Assert::AreEqual(reg_.A, int8_t(0b00101111));
		}

		TEST_METHOD(ORA_sets_zero_flag_for_zero_result)
		{
			ie_.LDA(int8_t(0b00000000));
			reg_.PS.reset(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.ORA(int8_t(0b00000000));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(ORA_resets_zero_flag_for_positive_result)
		{
			ie_.LDA(int8_t(0b00000000));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.ORA(int8_t(0b00010001));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(ORA_resets_zero_flag_for_negative_result)
		{
			ie_.LDA(int8_t(0b00000000));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.ORA(int8_t(0b10001010));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(ORA_sets_negative_flag_for_negative_results)
		{
			ie_.LDA(int8_t(0b00001100));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.ORA(int8_t(0b10101000));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(ORA_resets_negative_flag_for_positive_results)
		{
			ie_.LDA(int8_t(0b00010101));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.ORA(int8_t(0b00010110));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(ORA_resets_negative_flag_for_zero_result)
		{
			ie_.LDA(int8_t(0b00000000));
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.ORA(int8_t(0b00000000));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}
	};
}
