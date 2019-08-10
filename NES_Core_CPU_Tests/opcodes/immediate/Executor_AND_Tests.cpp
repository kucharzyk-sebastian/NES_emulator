#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/cpu/opcodes/immediate/executor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_Immediate_Executor
{
	TEST_CLASS(AND_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::cpu::opcodes::immediate::Executor ie_;


		AND_Tests() :
			reg_(),
			ie_(reg_)
		{
		}

		TEST_METHOD(AND_performs_binary_and)
		{
			ie_.LDA(int8_t(0b00001011));

			ie_.AND(int8_t(0b00100110));

			Assert::AreEqual(reg_.A, int8_t(0b00000010));
		}

		TEST_METHOD(AND_sets_zero_flag_for_zero_result)
		{
			ie_.LDA(int8_t(0b00100010));
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.AND(int8_t(0b00001000));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(AND_resets_zero_flag_for_positive_result)
		{
			ie_.LDA(int8_t(0b00001111));
			auto registers = ie_.getRegisters();
			registers.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			ie_.setRegisters(registers);
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.AND(int8_t(0b00001010));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(AND_resets_zero_flag_for_negative_result)
		{
			ie_.LDA(int8_t(0b10001111));
			auto registers = ie_.getRegisters();
			registers.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			ie_.setRegisters(registers);
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			ie_.AND(int8_t(0b10001110));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(AND_sets_negative_flag_for_negative_results)
		{
			ie_.LDA(int8_t(0b10001100));
			auto registers = ie_.getRegisters();
			registers.PS.reset(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			ie_.setRegisters(registers);
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.AND(int8_t(0b10000000));

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(AND_resets_negative_flag_for_positive_results)
		{
			ie_.LDA(int8_t(0b10011001));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.AND(int8_t(0b00011000));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(AND_resets_negative_flag_for_zero_result)
		{
			ie_.LDA(int8_t(0b10011001));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			ie_.AND(int8_t(0b00100100));

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

	};
}
