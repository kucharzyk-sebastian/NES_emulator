#include "nes/cpu/opcodes/implied/executor.h"

namespace nes::cpu::opcodes::implied {
	using rps =  registers::ProcessorStatus;

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
		registers_.PS.reset(static_cast<uint8_t>(rps::Carry));
	}

	void Executor::CLD() noexcept
	{
		registers_.PS.reset(static_cast<uint8_t>(rps::Decimal));
	}

	void Executor::CLI() noexcept
	{
		registers_.PS.reset(static_cast<uint8_t>(rps::InterruptDisable));
	}

	void Executor::CLV() noexcept
	{
		registers_.PS.reset(static_cast<uint8_t>(rps::Overflow));
	}

	void Executor::DEX() noexcept
	{
		int8_t result = registers_.X - 1;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = result < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = result == 0 ? true : false;

		registers_.X = result;
	}

	void Executor::SEC() noexcept
	{
		registers_.PS.set(static_cast<uint8_t>(rps::Carry));
	}

	void Executor::SED() noexcept
	{
		registers_.PS.set(static_cast<uint8_t>(rps::Decimal));
	}

	void Executor::SEI() noexcept
	{
		registers_.PS.set(static_cast<uint8_t>(rps::InterruptDisable));
	}
}
