#include "nes/cpu/opcodesExecutor.h"
#include "helpers/math.h"

namespace nes::cpu{
	OpcodesExecutor::OpcodesExecutor(registers::Registers& registers, memory::Memory& memory) :
		registers_(registers),
		memory_(memory)
	{
	}

	int8_t OpcodesExecutor::readFromStack()
	{
		return memory_[stackPage_ + ++registers_.SP];
	}

	void OpcodesExecutor::writeToStack(int8_t value)
	{
		memory_[stackPage_ + registers_.SP--] = value;
	}

	void OpcodesExecutor::ADC(int8_t value) noexcept
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

	void OpcodesExecutor::ADC(uint16_t address)
	{
		ADC(memory_[address]);
	}

	void OpcodesExecutor::AND(int8_t value) noexcept
	{
		int8_t result = registers_.A & value;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = result < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = result == 0 ? true : false;

		registers_.A = result;
	}

	void OpcodesExecutor::AND(uint16_t address)
	{
		AND(memory_[address]);
	}

	void OpcodesExecutor::ASL() noexcept
	{
		registers_.A = shiftLeftWithFlags(registers_.A);
	}

	void OpcodesExecutor::ASL(uint16_t address)
	{
		memory_[address] = shiftLeftWithFlags(memory_[address]);
	}

	void OpcodesExecutor::BIT(uint16_t address)
	{
		int8_t result = memory_[address] & registers_.A;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = result == 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = result < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Overflow)] = result & 0b01000000;
	}

	void OpcodesExecutor::CMP(int8_t value) noexcept
	{
		compareWithFlags(registers_.A, value);
	}

	void OpcodesExecutor::CMP(uint16_t address)
	{
		compareWithFlags(registers_.A, memory_[address]);
	}

	void OpcodesExecutor::CPX(int8_t value) noexcept
	{
		compareWithFlags(registers_.X, value);
	}

	void OpcodesExecutor::CPX(uint16_t address)
	{
		compareWithFlags(registers_.X, memory_[address]);
	}

	void OpcodesExecutor::CPY(int8_t value) noexcept
	{
		compareWithFlags(registers_.Y, value);
	}

	void OpcodesExecutor::CPY(uint16_t address)
	{
		compareWithFlags(registers_.Y, memory_[address]);
	}

	void OpcodesExecutor::CLC() noexcept
	{
		registers_.PS.reset(static_cast<uint8_t>(rps::Carry));
	}

	void OpcodesExecutor::CLD() noexcept
	{
		registers_.PS.reset(static_cast<uint8_t>(rps::Decimal));
	}

	void OpcodesExecutor::CLI() noexcept
	{
		registers_.PS.reset(static_cast<uint8_t>(rps::InterruptDisable));
	}

	void OpcodesExecutor::CLV() noexcept
	{
		registers_.PS.reset(static_cast<uint8_t>(rps::Overflow));
	}

	void OpcodesExecutor::DEC(uint16_t address)
	{
		memory_[address] = decrementWithFlags(memory_[address]);
	}

	void OpcodesExecutor::DEX() noexcept
	{
		registers_.X = decrementWithFlags(registers_.X);
	}

	void OpcodesExecutor::DEY() noexcept
	{
		registers_.Y = decrementWithFlags(registers_.Y);
	}

	void OpcodesExecutor::EOR(int8_t value) noexcept
	{
		int8_t result = registers_.A ^ value;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = result < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = result == 0 ? true : false;

		registers_.A = result;
	}

	void OpcodesExecutor::EOR(uint16_t address)
	{
		EOR(memory_[address]);
	}

	void OpcodesExecutor::INC(uint16_t address)
	{
		memory_[address] = incrementWithFlags(memory_[address]);
	}

	void OpcodesExecutor::INX() noexcept
	{
		registers_.X = incrementWithFlags(registers_.X);
	}

	void OpcodesExecutor::INY() noexcept
	{
		registers_.Y = incrementWithFlags(registers_.Y);
	}

	void OpcodesExecutor::LDA(int8_t value) noexcept
	{
		loadWithFlags(registers_.A, value, registers_.PS);
	}

	void OpcodesExecutor::LDA(uint16_t address)
	{
		loadWithFlags(registers_.A, memory_[address], registers_.PS);
	}

	void OpcodesExecutor::LDX(int8_t value) noexcept
	{
		loadWithFlags(registers_.X, value, registers_.PS);
	}

	void OpcodesExecutor::LDX(uint16_t address)
	{
		loadWithFlags(registers_.X, memory_[address], registers_.PS);
	}

	void OpcodesExecutor::LDY(int8_t value) noexcept
	{
		loadWithFlags(registers_.Y, value, registers_.PS);
	}

	void OpcodesExecutor::LDY(uint16_t address)
	{
		loadWithFlags(registers_.Y, memory_[address], registers_.PS);
	}

	void OpcodesExecutor::LSR() noexcept
	{
		registers_.A = shiftRightWithFlags(registers_.A);
	}

	void OpcodesExecutor::LSR(uint16_t address)
	{
		memory_[address] = shiftRightWithFlags(memory_[address]);
	}

	//TODO sk: probably will need to increase program counter
	void OpcodesExecutor::NOP() noexcept
	{
	}

	void OpcodesExecutor::ORA(int8_t value) noexcept
	{
		int8_t result = registers_.A | value;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = result < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = result == 0 ? true : false;

		registers_.A = result;
	}

	void OpcodesExecutor::ORA(uint16_t address)
	{
		ORA(memory_[address]);
	}

	void OpcodesExecutor::PHA()
	{
		writeToStack(registers_.A);
	}

	void OpcodesExecutor::PHP()
	{
		writeToStack(static_cast<int8_t>(registers_.PS.to_ulong()));
	}

	void OpcodesExecutor::PLA()
	{
		registers_.A = readFromStack();
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = registers_.A < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = registers_.A == 0 ? true : false;
	}

	void OpcodesExecutor::PLP()
	{
		registers_.PS = readFromStack();
	}

	void OpcodesExecutor::ROL() noexcept
	{
		registers_.A = rotateLeftWithFlags(registers_.A);
	}

	void OpcodesExecutor::ROL(uint16_t address)
	{
		memory_[address] = rotateLeftWithFlags(memory_[address]);
	}

	void OpcodesExecutor::ROR() noexcept
	{
		registers_.A = rotateRightWithFlags(registers_.A);
	}

	void OpcodesExecutor::ROR(uint16_t address)
	{
		memory_[address] = rotateRightWithFlags(memory_[address]);
	}

	void OpcodesExecutor::SBC(int8_t value) noexcept
	{
		ADC(int8_t(~value));
	}

	void OpcodesExecutor::SBC(uint16_t address)
	{
		SBC(memory_[address]);
	}

	void OpcodesExecutor::SEC() noexcept
	{
		registers_.PS.set(static_cast<uint8_t>(rps::Carry));
	}

	void OpcodesExecutor::SED() noexcept
	{
		registers_.PS.set(static_cast<uint8_t>(rps::Decimal));
	}

	void OpcodesExecutor::SEI() noexcept
	{
		registers_.PS.set(static_cast<uint8_t>(rps::InterruptDisable));
	}

	void OpcodesExecutor::TAX() noexcept
	{
		registers_.X = registers_.A;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = registers_.X < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = registers_.X == 0 ? true : false;
	}

	void OpcodesExecutor::TAY() noexcept
	{
		registers_.Y = registers_.A;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = registers_.Y < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = registers_.Y == 0 ? true : false;
	}

	void OpcodesExecutor::TSX() noexcept
	{
		registers_.X = int8_t(registers_.SP);
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = registers_.X < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = registers_.X == 0 ? true : false;
	}

	void OpcodesExecutor::TXA() noexcept
	{
		registers_.A = registers_.X;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = registers_.A < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = registers_.A == 0 ? true : false;
	}

	void OpcodesExecutor::TXS() noexcept
	{
		registers_.SP = registers_.X;
	}

	void OpcodesExecutor::TYA() noexcept
	{
		registers_.A = registers_.Y;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = registers_.A < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = registers_.A == 0 ? true : false;
	}


	int8_t OpcodesExecutor::shiftLeftWithFlags(int8_t value) noexcept
	{
		registers_.PS[static_cast<uint8_t>(rps::Carry)] = value >> (sizeof(int8_t) * CHAR_BIT - 1);
		value = value << 1;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = value < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = value == 0 ? true : false;

		return value;
	}

	int8_t OpcodesExecutor::decrementWithFlags(int8_t value) noexcept
	{
		int8_t result = value - 1;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = result < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = result == 0 ? true : false;

		return result;
	}
	int8_t OpcodesExecutor::incrementWithFlags(int8_t value) noexcept
	{
		int8_t result = value + 1;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = result < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = result == 0 ? true : false;

		return result;
	}

	int8_t OpcodesExecutor::shiftRightWithFlags(int8_t value) noexcept
	{
		registers_.PS[static_cast<uint8_t>(rps::Carry)] = value & 1;
		value = uint8_t(value) >> 1;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = value < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = value == 0 ? true : false;

		return value;
	}

	int8_t OpcodesExecutor::rotateLeftWithFlags(int8_t value) noexcept
	{
		int8_t oldCarry = registers_.PS[static_cast<uint8_t>(rps::Carry)];
		registers_.PS[static_cast<uint8_t>(rps::Carry)] = value >> (sizeof(int8_t) * CHAR_BIT - 1);
		value = (value << 1) + oldCarry;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = value < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = value == 0 ? true : false;

		return value;
	}

	int8_t OpcodesExecutor::rotateRightWithFlags(int8_t value) noexcept
	{
		int8_t oldCarry = registers_.PS[static_cast<uint8_t>(rps::Carry)];
		registers_.PS[static_cast<uint8_t>(rps::Carry)] = value & 1;
		value = (uint8_t(value) >> 1) + (oldCarry << (sizeof(int8_t) * CHAR_BIT - 1));
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = value < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = value == 0 ? true : false;

		return value;
	}


	void OpcodesExecutor::compareWithFlags(int8_t registerValue, int8_t inputValue) noexcept
	{
		registers_.PS[static_cast<uint8_t>(rps::Carry)] = static_cast<uint8_t>(registerValue) >= static_cast<uint8_t>(inputValue) ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = (registerValue - inputValue) < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = registerValue == inputValue ? true : false;
	}

	void OpcodesExecutor::loadWithFlags(int8_t& reg, int8_t value, std::bitset<8> & flags) noexcept
	{
		flags[static_cast<uint8_t>(rps::Negative)] = value < 0 ? true : false;
		flags[static_cast<uint8_t>(rps::Zero)] = value == 0 ? true : false;

		reg = value;
	}
}