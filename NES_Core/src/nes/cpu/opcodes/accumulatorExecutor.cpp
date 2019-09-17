#include "nes/cpu/opcodes/accumulatorExecutor.h"
#include "accumulatorExecutor.h"

namespace nes::cpu::opcodes{
	nes::cpu::opcodes::AccumulatorExecutor::AccumulatorExecutor(nes::cpu::registers::Registers& registers, nes::memory::Memory& memory) :
	BasicExecutor(registers, memory)
	{
	}

	void nes::cpu::opcodes::AccumulatorExecutor::ASL() noexcept
	{
		registers_.PS[static_cast<uint8_t>(rps::Carry)] = registers_.A >> (sizeof(unsigned int) * CHAR_BIT - 1);
		registers_.A = registers_.A << 1;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = registers_.A < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = registers_.A == 0 ? true : false;
	}

	void AccumulatorExecutor::LSR() noexcept
	{
		registers_.PS[static_cast<uint8_t>(rps::Carry)] = registers_.A & 1;
		registers_.A = uint8_t(registers_.A) >> 1;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = registers_.A < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = registers_.A == 0 ? true : false;
	}
}
