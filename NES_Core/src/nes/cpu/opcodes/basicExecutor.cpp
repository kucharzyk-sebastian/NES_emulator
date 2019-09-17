#include "nes/cpu/opcodes/basicExecutor.h"
#include "helpers/math.h"

namespace nes::cpu::opcodes{
	BasicExecutor::BasicExecutor(registers::Registers& registers, memory::Memory& memory) :
		registers_(registers),
		memory_(memory)
	{
	}

	BasicExecutor::~BasicExecutor()
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
	int8_t BasicExecutor::ADC(int8_t lhs, int8_t rhs) noexcept
	{
		int8_t valWithCarry = rhs + registers_.PS[static_cast<uint8_t>(rps::Carry)];
		int8_t result = lhs + valWithCarry;
		registers_.PS[static_cast<uint8_t>(rps::Overflow)] = helpers::math::isOverflow(lhs, rhs, result) ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Carry)] = helpers::math::isCarry(rhs, registers_.PS[static_cast<uint8_t>(rps::Carry)]) ?
			true : helpers::math::isCarry(lhs, valWithCarry);
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = result < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = result == 0 ? true : false;

		return result;
	}
}