#include "nes/cpu/opcodes/implied/executor.h"

namespace nes::cpu::opcodes::implied {
	Executor::Executor(registers::Registers & registers) noexcept :
		registers_(registers)
	{
	}

	registers::Registers Executor::getRegisters() const noexcept
	{
		return registers_;
	}

	void Executor::setRegisters(const registers::Registers & registers) noexcept
	{
		registers_ = registers;
	}

	void Executor::CLC() noexcept
	{
		registers_.PS.reset(static_cast<uint8_t>(registers::ProcessorStatus::Carry));
	}

	void Executor::CLD() noexcept
	{
		registers_.PS.reset(static_cast<uint8_t>(registers::ProcessorStatus::Decimal));
	}

	void Executor::CLI() noexcept
	{
		registers_.PS.reset(static_cast<uint8_t>(registers::ProcessorStatus::InterruptDisable));
	}

	void Executor::CLV() noexcept
	{
		registers_.PS.reset(static_cast<uint8_t>(registers::ProcessorStatus::Overflow));
	}

	void Executor::SEC() noexcept
	{
		registers_.PS.set(static_cast<uint8_t>(registers::ProcessorStatus::Carry));
	}

	void Executor::SED() noexcept
	{
		registers_.PS.set(static_cast<uint8_t>(registers::ProcessorStatus::Decimal));
	}

	void Executor::SEI() noexcept
	{
		registers_.PS.set(static_cast<uint8_t>(registers::ProcessorStatus::InterruptDisable));
	}
}
