#include "CppUnitTest.h"
#include "nes/memory/romLoader.h"
#include "nes/memory/memory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Memory_Tests
{
	TEST_CLASS(RomLoader_Tests)
	{
	public:
		nes::memory::RomLoader rl_;
		nes::memory::Memory mem_;

		RomLoader_Tests() :
			rl_(),
			mem_()
		{
		}

		TEST_METHOD(loadRom_loads_rom_from_memory)
		{
			std::string path = "C:\\dev\\NES_Emulator\\NES_Core_CPU_Tests\\test_data\\nestest.nes";
			rl_.loadMemory(path, mem_);
		}
	};
}
