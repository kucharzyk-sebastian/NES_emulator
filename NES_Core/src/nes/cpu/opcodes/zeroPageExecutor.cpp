#include "zeroPageExecutor.h"

namespace nes::cpu::opcodes{

	ZeroPageExecutor::ZeroPageExecutor(registers::Registers& registers, memory::Memory& memory) :
		BasicExecutor(registers, memory)
	{
	}

	void ZeroPageExecutor::ADC(uint8_t address)
	{
		BasicExecutor::ADC(memory_[page_ + address]);
	}
}
