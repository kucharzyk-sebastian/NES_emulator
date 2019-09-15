#include "nes/memory/memory.h"

namespace nes::memory {
	Memory::Memory() :
		memory_(std::make_shared<MemArray>())
	{
	}

	int8_t& Memory::operator[](uint16_t address)
	{
		return (*memory_)[address];
	}
}
