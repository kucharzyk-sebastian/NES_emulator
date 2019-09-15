#include "nes/memory/memory.h"

namespace nes::memory {
	Memory::Memory() :
		memory_(std::make_shared<MemArray>())
	{
	}

	int8_t Memory::readMemory(uint16_t address)
	{
		return (*memory_)[address];
	}

	void Memory::writeMemory(uint16_t address, int8_t value)
	{
		(*memory_)[address] = value;
	}
}
