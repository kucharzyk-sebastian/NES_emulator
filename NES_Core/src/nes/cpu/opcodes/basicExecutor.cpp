#include "nes/cpu/opcodes/basicExecutor.h"

namespace nes::cpu::opcodes{
	BasicExecutor::BasicExecutor(registers::Registers& registers) :
		registers_(registers)
	{
	}

	const registers::Registers& BasicExecutor::getRegisters() const noexcept
	{
		return registers_;
	}

	void BasicExecutor::setRegisters(const registers::Registers& registers) noexcept
	{
		registers_ = registers;
	}
}