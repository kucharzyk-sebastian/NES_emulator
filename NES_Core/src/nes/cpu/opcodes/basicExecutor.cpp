#include "nes/cpu/opcodes/basicExecutor.h"
#include "helpers/math.h"

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

	void BasicExecutor::ADC(int8_t value) noexcept
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

	void BasicExecutor::AND(int8_t value) noexcept
	{
		int8_t result = registers_.A & value;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = result < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = result == 0 ? true : false;

		registers_.A = result;
	}

	int8_t BasicExecutor::ASL(int8_t value) noexcept
	{
		registers_.PS[static_cast<uint8_t>(rps::Carry)] = value >> (sizeof(int8_t) * CHAR_BIT - 1);
		value = value << 1;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = value < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = value == 0 ? true : false;

		return value;
	}
}