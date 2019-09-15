#include "nes/cpu/opcodes/basicExecutor.h"

namespace nes::cpu::opcodes{
	BasicExecutor::BasicExecutor(registers::Registers& registers, memory::Memory& memory) :
		registers_(registers),
		memory_(memory)
	{
	}

	int8_t BasicExecutor::readFromStack()
	{
		return memory_[stackPage_ + ++registers_.SP];
	}

	void BasicExecutor::writeToStack(int8_t value)
	{
		memory_[stackPage_ + registers_.SP--] = value;
	}
}