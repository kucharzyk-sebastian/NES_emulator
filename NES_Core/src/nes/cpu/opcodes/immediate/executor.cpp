#include "nes/cpu/opcodes/immediate/executor.h"
#include "helpers/math.h"

namespace nes::cpu::opcodes::immediate {
	Executor::Executor(registers::Registers& registers) noexcept :
		registers_(registers)
	{
	}

	registers::Registers Executor::getRegisters() const noexcept
	{
		return registers_;
	}

	void Executor::setRegisters(const registers::Registers& registers) noexcept
	{
		registers_ = registers;
	}

	void Executor::ADC(int8_t value) noexcept
	{
		int8_t result = registers_.A + value;
		registers_.PS[static_cast<uint8_t>(registers::ProcessorStatus::Overflow)] = helpers::math::isOverflow(registers_.A, value, result) ? true : false;
		registers_.PS[static_cast<uint8_t>(registers::ProcessorStatus::Carry)] = helpers::math::isCarry(registers_.A, value) ? true : false;
		registers_.PS[static_cast<uint8_t>(registers::ProcessorStatus::Negative)] = result < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(registers::ProcessorStatus::Zero)] = result == 0 ? true : false;

		registers_.A = result;
	}

	void Executor::AND(int8_t value) noexcept
	{
		int8_t result = registers_.A & value;
		registers_.PS[static_cast<uint8_t>(registers::ProcessorStatus::Negative)] = result < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(registers::ProcessorStatus::Zero)] = result == 0 ? true : false;

		registers_.A = result;
	}

	void Executor::LDA(int8_t value) noexcept
	{
		registers_.PS[static_cast<uint8_t>(registers::ProcessorStatus::Negative)] = value < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(registers::ProcessorStatus::Zero)] = value == 0 ? true : false;

		registers_.A = value;
	}
}


