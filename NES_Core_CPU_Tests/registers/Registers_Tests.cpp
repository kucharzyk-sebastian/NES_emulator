#include "CppUnitTest.h"
#include "nes/cpu/registers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Registers_Tests
{
	TEST_CLASS(Registers_Tests)
	{
	public:
		nes::cpu::registers::Registers reg_;


		Registers_Tests() :
			reg_()
		{
		}

		TEST_METHOD(Registers_initialize_with_correct_default_values)
		{
			Assert::AreEqual(int8_t(0), reg_.A);
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(uint16_t(0)), int(reg_.PC));
			Assert::AreEqual(std::bitset<8>(0b00100100).to_string(), reg_.PS.to_string());
			Assert::AreEqual(uint8_t(0xFD), reg_.SP);
			Assert::AreEqual(int8_t(0), reg_.X);
			Assert::AreEqual(int8_t(0), reg_.Y);
		}
	};
}
