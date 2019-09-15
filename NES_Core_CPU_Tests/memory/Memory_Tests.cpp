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

		TEST_METHOD(Memory_performs_read_write_operation)
		{
			uint16_t address = 0x0003;
			int8_t value = int8_t(7);
			mem_.writeMemory(address, value);
			Assert::AreEqual(mem_.readMemory(address), value);
		}

		TEST_METHOD(Memory_performs_read_write_operation_edge_addresses)
		{
			uint16_t lhsAddress = 0x0000;
			int8_t lhsValue = int8_t(7);
			mem_.writeMemory(lhsAddress, lhsValue);
			Assert::AreEqual(mem_.readMemory(lhsAddress), lhsValue);

			uint16_t rhsAddress = 0xFFFF;
			int8_t rhsValue = int8_t(12);
			mem_.writeMemory(rhsAddress, rhsValue);
			Assert::AreEqual(mem_.readMemory(rhsAddress), rhsValue);
		}
	};
}
