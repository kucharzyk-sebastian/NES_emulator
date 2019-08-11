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

	void Executor::CMP(int8_t value) noexcept
	{
		compareWithFlags(registers_.A, value, registers_.PS);
	}

	void Executor::CPX(int8_t value) noexcept
	{
		compareWithFlags(registers_.X, value, registers_.PS);
	}

	void Executor::CPY(int8_t value) noexcept
	{
		compareWithFlags(registers_.Y, value, registers_.PS);
	}

	void Executor::EOR(int8_t value) noexcept
	{
		int8_t result = registers_.A ^ value;
		registers_.PS[static_cast<uint8_t>(registers::ProcessorStatus::Negative)] = result < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(registers::ProcessorStatus::Zero)] = result == 0 ? true : false;

		registers_.A = result;
	}

	void Executor::LDA(int8_t value) noexcept
	{
		loadWithFlags(registers_.A, value, registers_.PS);
	}

	void Executor::LDX(int8_t value) noexcept
	{
		loadWithFlags(registers_.X, value, registers_.PS);
	}

	void Executor::LDY(int8_t value) noexcept
	{
		loadWithFlags(registers_.Y, value, registers_.PS);
	}

	void Executor::compareWithFlags(int8_t& reg, int8_t value, std::bitset<8>& flags) noexcept
	{
		flags[static_cast<uint8_t>(registers::ProcessorStatus::Carry)] = static_cast<uint8_t>(reg) >= static_cast<uint8_t>(value) ? true : false;
		flags[static_cast<uint8_t>(registers::ProcessorStatus::Negative)] = (reg - value) < 0 ? true : false;
		flags[static_cast<uint8_t>(registers::ProcessorStatus::Zero)] = reg == value ? true : false;
	}

	void Executor::loadWithFlags(int8_t& reg, int8_t value, std::bitset<8>& flags) noexcept
	{
		flags[static_cast<uint8_t>(registers::ProcessorStatus::Negative)] = value < 0 ? true : false;
		flags[static_cast<uint8_t>(registers::ProcessorStatus::Zero)] = value == 0 ? true : false;

		reg = value;
	}

}


