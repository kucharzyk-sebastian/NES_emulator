#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/cpu/opcodes/immediateExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_ImmediateExecutor
{
	TEST_CLASS(EOR_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::cpu::opcodes::ImmediateExecutor ie_;


		EOR_Tests() :
			reg_(),
			ie_(reg_)
		{
		}

		TEST_METHOD(EOR_performs_binary_exclusive_or)
		{
			ie_.LDA(int8_t(0b00001011));

			ie_.EOR(int8_t(0b00100110));

			Assert::AreEqual(reg_.A, int8_t(0b00101101));
		}

		TEST_METHOD(EOR_sets_zero_flag_for_zero_result)
		{
			ie_.LDA(int8_t(0b00100010));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.EOR(int8_t(0b00100010));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(EOR_resets_zero_flag_for_positive_result)
		{
			ie_.LDA(int8_t(0b00000000));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.EOR(int8_t(0b00010001));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(EOR_resets_zero_flag_for_negative_result)
		{
			ie_.LDA(int8_t(0b00000000));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.EOR(int8_t(0b10001010));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(EOR_sets_negative_flag_for_negative_results)
		{
			ie_.LDA(int8_t(0b00001100));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.EOR(int8_t(0b10101000));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(EOR_resets_negative_flag_for_positive_results)
		{
			ie_.LDA(int8_t(0b10010101));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.EOR(int8_t(0b10010110));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(EOR_resets_negative_flag_for_zero_result)
		{
			ie_.LDA(int8_t(0b10011001));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.EOR(int8_t(0b10011001));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

	};
}