#include "CppUnitTest.h"
#include "nes/memory/memory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Memory_Tests
{
	TEST_CLASS(Memory_Tests)
	{
	public:
		nes::memory::Memory mem_;

		Memory_Tests() :
			mem_()
		{
		}

		TEST_METHOD(Memory_performs_read_write_operations_using_operator)
		{
			uint16_t address = 0x0003;
			int8_t value = int8_t(7);
			mem_[address] = value;
			Assert::AreEqual(value, mem_[address]);
		}

		TEST_METHOD(Memory_performs_read_write_operation_using_operator_edge_addresses)
		{
			uint16_t lhsAddress = 0x0000;
			int8_t lhsValue = int8_t(7);
			mem_[lhsAddress] = lhsValue;
			Assert::AreEqual(lhsValue, mem_[lhsAddress]);

			uint16_t rhsAddress = 0xFFFF;
			int8_t rhsValue = int8_t(12);
			mem_[rhsAddress] = rhsValue;
			Assert::AreEqual(rhsValue, mem_[rhsAddress]);
		}
	};
}
