#include "CppUnitTest.h"
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"
#include  "nes/cpu/opcodesExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpcodesExecutor
{
	TEST_CLASS(DEC_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::cpu::OpcodesExecutor oe_;
		nes::memory::Memory mem_;


		DEC_Tests() :
			reg_(),
			oe_(reg_, mem_)
		{

		}

		TEST_METHOD(DEC_decrements_value_in_memory_by_one)
		{
			int8_t value = 5;
			uint16_t address = 0x5655;
			mem_[address] = value;

			oe_.DEC(address);

			Assert::AreEqual(--value, mem_[address]);
		}

		TEST_METHOD(DEC_sets_zero_flag_when_result_equal_zero)
		{
			uint16_t address = 0xa05f;
			mem_[address] = 1;
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.DEC(address);

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(DEC_resets_zero_flag_when_result_lt_zero)
		{
			uint16_t address = 0xdcca;
			mem_[address] = 0;
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.DEC(address);

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(DEC_resets_zero_flag_when_result_gt_zero)
		{
			uint16_t address = 0xacc8;
			mem_[address] = 5;
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);

			oe_.DEC(address);

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Zero)]);
		}

		TEST_METHOD(DEC_sets_negative_flag_when_result_lt_zero)
		{
			uint16_t address = 0x1002;
			mem_[address] = 0;
			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.DEC(address);

			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(DEC_resets_negative_flag_when_result_gt_zero)
		{
			uint16_t address = 0x0076;
			mem_[address] = -128;
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.DEC(address);

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}

		TEST_METHOD(DEC_resets_negative_flag_when_result_equal_zero)
		{
			uint16_t address = 0xa002;
			mem_[address] = 1;
			reg_.PS.set(static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative));
			Assert::IsTrue(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);

			oe_.DEC(address);

			Assert::IsFalse(reg_.PS[static_cast<uint8_t>(nes::cpu::registers::ProcessorStatus::Negative)]);
		}
	};
}
