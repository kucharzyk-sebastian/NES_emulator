#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodes/zeroPageExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OPCodes_ZeroPageExecutor
{
	TEST_CLASS(ADC_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;
		nes::memory::Memory mem_;
		nes::cpu::opcodes::ZeroPageExecutor zpe_;
		uint8_t page = 0x0000;


		ADC_Tests() :
			reg_(),
			zpe_(reg_, mem_)
		{
			reg_.A = 0x07;
		}

		TEST_METHOD(ADC_adds_value_from_memory_address_to_A_register)
		{
			int8_t val = 91;
			uint8_t address = 0x76;
			mem_[page + address] = val;
			int8_t previousA = reg_.A;
			int8_t expectedResult = int8_t(previousA + val);
			Assert::AreEqual(mem_[page + address], val);
			Assert::AreNotEqual(expectedResult, reg_.A);

			zpe_.ADC(address);

			Assert::AreEqual(expectedResult, reg_.A);
		}

		TEST_METHOD(ADC_adds_value_from_memory_address_to_A_register_min_address)
		{
			int8_t val = 121;
			uint8_t address = 0x00;
			mem_[page + address] = val;
			int8_t previousA = reg_.A;
			int8_t expectedResult = int8_t(previousA + val);
			Assert::AreEqual(mem_[page + address], val);
			Assert::AreNotEqual(expectedResult, reg_.A);

			zpe_.ADC(address);

			Assert::AreEqual(expectedResult, reg_.A);
		}

		TEST_METHOD(ADC_adds_value_from_memory_address_to_A_register_max_address)
		{
			int8_t val = -15;
			uint8_t address = 0xFF;
			mem_[page + address] = val;
			int8_t previousA = reg_.A;
			int8_t expectedResult = int8_t(previousA + val);
			Assert::AreEqual(mem_[page + address], val);
			Assert::AreNotEqual(expectedResult, reg_.A);

			zpe_.ADC(address);

			Assert::AreEqual(expectedResult, reg_.A);
		}
	};
}
