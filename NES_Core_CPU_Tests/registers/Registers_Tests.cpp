#include "CppUnitTest.h"
#include "nes/cpu/registers/registers.h"

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
			Assert::AreEqual(reg_.A, int8_t(0));
			// Casting to int because of a well known bug in CppUnit which does not allow comparison of uint16_t
			Assert::AreEqual(int(reg_.PC), int(uint16_t(0)));
			Assert::AreEqual(reg_.PS.to_string(), std::bitset<8>(0b00110100).to_string());
			Assert::AreEqual(reg_.SP, uint8_t(0xFF));
			Assert::AreEqual(reg_.X, int8_t(0));
			Assert::AreEqual(reg_.Y, int8_t(0));
		}
	};
}
