#include "nes/memory/romLoader.h"
#include <vector>
#include <fstream>


namespace nes::memory {
	void RomLoader::loadMemory(const std::string& path, Memory& memory)
	{
		std::ifstream file(path, std::ios::binary);
		std::vector<uint8_t> v(std::istreambuf_iterator<char>{file}, {});

		for (uint16_t addr = 0x0010; addr < 0x4000; ++addr)
		{
			memory[0x8000] = v[addr];
			memory[0xC000] = v[addr];
		}
	} 
}
