#include "nes/cpu/opcodes/immediateExecutor.h"
#include "helpers/math.h"

namespace nes::cpu::opcodes{
	using rps =  registers::ProcessorStatus;

	ImmediateExecutor::ImmediateExecutor(registers::Registers& registers) noexcept :
		BasicExecutor(registers)
	{
	}

	void ImmediateExecutor::ADC(int8_t value) noexcept
	{
		int8_t valWithCarry = value + registers_.PS[static_cast<uint8_t>(rps::Carry)];
		int8_t result = registers_.A + valWithCarry;
		registers_.PS[static_cast<uint8_t>(rps::Overflow)] = helpers::math::isOverflow(registers_.A, value, result) ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Carry)] = helpers::math::isCarry(value, registers_.PS[static_cast<uint8_t>(rps::Carry)]) ? 
			true : helpers::math::isCarry(registers_.A, valWithCarry);
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = result < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = result == 0 ? true : false;

		registers_.A = result;
	}

	void ImmediateExecutor::AND(int8_t value) noexcept
	{
		int8_t result = registers_.A & value;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = result < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = result == 0 ? true : false;

		registers_.A = result;
	}

	void ImmediateExecutor::CMP(int8_t value) noexcept
	{
		compareWithFlags(registers_.A, value, registers_.PS);
	}

	void ImmediateExecutor::CPX(int8_t value) noexcept
	{
		compareWithFlags(registers_.X, value, registers_.PS);
	}

	void ImmediateExecutor::CPY(int8_t value) noexcept
	{
		compareWithFlags(registers_.Y, value, registers_.PS);
	}

	void ImmediateExecutor::EOR(int8_t value) noexcept
	{
		int8_t result = registers_.A ^ value;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = result < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = result == 0 ? true : false;

		registers_.A = result;
	}

	void ImmediateExecutor::LDA(int8_t value) noexcept
	{
		loadWithFlags(registers_.A, value, registers_.PS);
	}

	void ImmediateExecutor::LDX(int8_t value) noexcept
	{
		loadWithFlags(registers_.X, value, registers_.PS);
	}

	void ImmediateExecutor::LDY(int8_t value) noexcept
	{
		loadWithFlags(registers_.Y, value, registers_.PS);
	}

	//TODO sk: once all implemented try to extract common part of all logical instructions
	void ImmediateExecutor::ORA(int8_t value) noexcept
	{
		int8_t result = registers_.A | value;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = result < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = result == 0 ? true : false;

		registers_.A = result;
	}

	void ImmediateExecutor::SBC(int8_t value) noexcept
	{
		ADC(~value);
	}

	void ImmediateExecutor::compareWithFlags(int8_t& reg, int8_t value, std::bitset<8>& flags) noexcept
	{
		flags[static_cast<uint8_t>(rps::Carry)] = static_cast<uint8_t>(reg) >= static_cast<uint8_t>(value) ? true : false;
		flags[static_cast<uint8_t>(rps::Negative)] = (reg - value) < 0 ? true : false;
		flags[static_cast<uint8_t>(rps::Zero)] = reg == value ? true : false;
	}

	void ImmediateExecutor::loadWithFlags(int8_t& reg, int8_t value, std::bitset<8>& flags) noexcept
	{
		flags[static_cast<uint8_t>(rps::Negative)] = value < 0 ? true : false;
		flags[static_cast<uint8_t>(rps::Zero)] = value == 0 ? true : false;

		reg = value;
	}

}


