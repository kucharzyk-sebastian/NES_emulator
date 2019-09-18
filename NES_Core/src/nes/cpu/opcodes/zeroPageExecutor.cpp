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

	void ZeroPageExecutor::AND(uint8_t address)
	{
		BasicExecutor::AND(memory_[page_ + address]);
	}

	void ZeroPageExecutor::ASL(uint8_t address)
	{
		address = page_ + address;
		memory_[address] = BasicExecutor::ASL(memory_[address]);
	}
}
