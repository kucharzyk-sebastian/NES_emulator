#include "nes/cpu/opcodes/immediateExecutor.h"
#include "helpers/math.h"

namespace nes::cpu::opcodes{

	ImmediateExecutor::ImmediateExecutor(registers::Registers& registers, memory::Memory& memory) :
		BasicExecutor(registers, memory)
	{
	}

	void ImmediateExecutor::ADC(int8_t value) noexcept
	{
		BasicExecutor::ADC(value);
	}

	void ImmediateExecutor::AND(int8_t value) noexcept
	{
		BasicExecutor::AND(value);
	}

	void ImmediateExecutor::CMP(int8_t value) noexcept
	{
		BasicExecutor::CMP(value);
	}

	void ImmediateExecutor::CPX(int8_t value) noexcept
	{
		BasicExecutor::CPX(value);
	}

	void ImmediateExecutor::CPY(int8_t value) noexcept
	{
		BasicExecutor::CPY(value);
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

	void ImmediateExecutor::loadWithFlags(int8_t& reg, int8_t value, std::bitset<8>& flags) noexcept
	{
		flags[static_cast<uint8_t>(rps::Negative)] = value < 0 ? true : false;
		flags[static_cast<uint8_t>(rps::Zero)] = value == 0 ? true : false;

		reg = value;
	}

}


