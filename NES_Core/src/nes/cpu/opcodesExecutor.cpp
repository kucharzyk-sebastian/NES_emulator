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
		using namespace helpers::math;
		int8_t result = registers_.A + value + registers_.PS[rps::Carry];
		registers_.PS[rps::Overflow] = isOverflow(registers_.A, value, registers_.PS[rps::Carry]);
		registers_.PS[rps::Carry] = isCarry(registers_.A, value, registers_.PS[rps::Carry]);
		registers_.PS[rps::Negative] = result < 0;
		registers_.PS[rps::Zero] = result == 0;
		registers_.A = result;
	}

	void OpcodesExecutor::ADC(uint16_t address)
	{
		ADC(memory_[address]);
	}

	void OpcodesExecutor::AND(int8_t value) noexcept
	{
		int8_t result = registers_.A & value;
		registers_.PS[rps::Negative] = result < 0;
		registers_.PS[rps::Zero] = result == 0;

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

	void OpcodesExecutor::BCC(int8_t value) noexcept
	{
		if (!registers_.PS[rps::Carry])
			registers_.PC += value;
	}

	void OpcodesExecutor::BCS(int8_t value) noexcept
	{
		if (registers_.PS[rps::Carry])
			registers_.PC += value;
	}

	void OpcodesExecutor::BEQ(int8_t value) noexcept
	{
		if (registers_.PS[rps::Zero])
			registers_.PC += value;
	}

	void OpcodesExecutor::BIT(uint16_t address)
	{
		int8_t result = memory_[address] & registers_.A;
		registers_.PS[rps::Zero] = result == 0;
		registers_.PS[rps::Negative] = memory_[address] < 0;
		registers_.PS[rps::Overflow] = memory_[address] & 0b01000000;
	}

	void OpcodesExecutor::BMI(int8_t value) noexcept
	{
		if (registers_.PS[rps::Negative])
			registers_.PC += value;
	}

	void OpcodesExecutor::BNE(int8_t value) noexcept
	{
		if (!registers_.PS[rps::Zero])
			registers_.PC += value;
	}

	void OpcodesExecutor::BPL(int8_t value) noexcept
	{
		if (!registers_.PS[rps::Negative])
			registers_.PC += value;
	}

	void OpcodesExecutor::BRK()
	{
		writeToStack(registers_.PC >> CHAR_BIT);
		writeToStack(registers_.PC & 0x00FF);
		registers_.PS.set(rps::Break);
		writeToStack(int8_t(registers_.PS.to_ulong() | (1 << rps::Unknown)));
		registers_.PC = uint8_t(memory_[interruptVectorLSB_]) + (memory_[interruptVectorMSB_] << CHAR_BIT);
	}

	void OpcodesExecutor::BVC(int8_t value) noexcept
	{
		if (!registers_.PS[rps::Overflow])
			registers_.PC += value;
	}

	void OpcodesExecutor::BVS(int8_t value) noexcept
	{
		if (registers_.PS[rps::Overflow])
			registers_.PC += value;
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
		registers_.PS.reset(rps::Carry);
	}

	void OpcodesExecutor::CLD() noexcept
	{
		registers_.PS.reset(rps::Decimal);
	}

	void OpcodesExecutor::CLI() noexcept
	{
		registers_.PS.reset(rps::InterruptDisable);
	}

	void OpcodesExecutor::CLV() noexcept
	{
		registers_.PS.reset(rps::Overflow);
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
		registers_.PS[rps::Negative] = result < 0;
		registers_.PS[rps::Zero] = result == 0;

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

	void OpcodesExecutor::JMP_absolute(uint16_t value) noexcept
	{
		registers_.PC = value;
	}

	// there's a common bug in 6502 Jump method. For example if address $3000 contains $40, $30FF contains $80, and $3100 contains $50, 
	// the result of JMP ($30FF) will be a transfer of control to $4080 rather than $5080 as you intended
	// i.e. the 6502 took the low byte of the address from $30FF and the high byte from $3000.
	void OpcodesExecutor::JMP_indirect(uint16_t address)
	{
		registers_.PC = ((address & 0xFF) == 0xFF ? memory_[address & 0xFF00] << CHAR_BIT : memory_[address + 1] << CHAR_BIT) + uint8_t(memory_[address]);
	}

	void OpcodesExecutor::JSR(uint16_t value)
	{
		uint16_t returnPoint = registers_.PC;
		writeToStack(returnPoint >> CHAR_BIT);
		writeToStack(returnPoint & 0x00FF);
		registers_.PC = value;
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

	void OpcodesExecutor::NOP() noexcept
	{
		++registers_.PC;
	}

	void OpcodesExecutor::ORA(int8_t value) noexcept
	{
		int8_t result = registers_.A | value;
		registers_.PS[rps::Negative] = result < 0;
		registers_.PS[rps::Zero] = result == 0;

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
		int8_t valueToWrite = static_cast<int8_t>(registers_.PS.to_ulong());
		valueToWrite |= (1 << rps::Break);
		valueToWrite |= (1 << rps::Unknown);
		writeToStack(valueToWrite);
	}

	void OpcodesExecutor::PLA()
	{
		registers_.A = readFromStack();
		registers_.PS[rps::Negative] = registers_.A < 0;
		registers_.PS[rps::Zero] = registers_.A == 0;
	}

	void OpcodesExecutor::PLP()
	{
		auto oldPS = registers_.PS;
		registers_.PS = uint8_t(readFromStack());
		registers_.PS[rps::Break] = oldPS[rps::Break];
		registers_.PS[rps::Unknown] = oldPS[rps::Unknown];
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

	void OpcodesExecutor::RTI()
	{
		PLP();
		registers_.PC = uint8_t(readFromStack()) + (readFromStack() << CHAR_BIT);
	}

	void OpcodesExecutor::RTS()
	{
		registers_.PC = uint8_t(readFromStack()) + (readFromStack() << CHAR_BIT) + 1;
	}

	void OpcodesExecutor::SBC(int8_t value) noexcept
	{
		using namespace helpers::math;
		value = ~value;
		if (registers_.PS[rps::Carry])
			value = uint8_t(value) + 1;
		int8_t result = registers_.A + value;
		registers_.PS[rps::Overflow] = isOverflow(registers_.A, value);
		registers_.PS[rps::Carry] = isCarry(registers_.A, value);
		registers_.PS[rps::Negative] = result < 0;
		registers_.PS[rps::Zero] = result == 0;
		registers_.A = result;
	}

	void OpcodesExecutor::SBC(uint16_t address)
	{
		SBC(memory_[address]);
	}

	void OpcodesExecutor::SEC() noexcept
	{
		registers_.PS.set(rps::Carry);
	}

	void OpcodesExecutor::SED() noexcept
	{
		registers_.PS.set(rps::Decimal);
	}

	void OpcodesExecutor::SEI() noexcept
	{
		registers_.PS.set(rps::InterruptDisable);
	}

	void OpcodesExecutor::STA(uint16_t address)
	{
		memory_[address] = registers_.A;
	}

	void OpcodesExecutor::STX(uint16_t address)
	{
		memory_[address] = registers_.X;
	}

	void OpcodesExecutor::STY(uint16_t address)
	{
		memory_[address] = registers_.Y;
	}

	void OpcodesExecutor::TAX() noexcept
	{
		transferWithFlags(registers_.A, registers_.X);
	}

	void OpcodesExecutor::TAY() noexcept
	{
		transferWithFlags(registers_.A, registers_.Y);
	}

	void OpcodesExecutor::TSX() noexcept
	{
		int8_t castedSP = int8_t(registers_.SP);
		transferWithFlags(castedSP, registers_.X);
	}

	void OpcodesExecutor::TXA() noexcept
	{
		transferWithFlags(registers_.X, registers_.A);
	}

	void OpcodesExecutor::TXS() noexcept
	{
		registers_.SP = registers_.X;
	}

	void OpcodesExecutor::TYA() noexcept
	{
		transferWithFlags(registers_.Y, registers_.A);
	}

	int8_t OpcodesExecutor::decrementWithFlags(int8_t value) noexcept
	{
		int8_t result = value - 1;
		registers_.PS[rps::Negative] = result < 0;
		registers_.PS[rps::Zero] = result == 0;

		return result;
	}
	int8_t OpcodesExecutor::incrementWithFlags(int8_t value) noexcept
	{
		int8_t result = value + 1;
		registers_.PS[rps::Negative] = result < 0;
		registers_.PS[rps::Zero] = result == 0;

		return result;
	}

	int8_t OpcodesExecutor::shiftLeftWithFlags(int8_t value) noexcept
	{
		registers_.PS[rps::Carry] = value >> (sizeof(value) * CHAR_BIT - 1);
		value = value << 1;
		registers_.PS[rps::Negative] = value < 0;
		registers_.PS[rps::Zero] = value == 0;

		return value;
	}

	int8_t OpcodesExecutor::shiftRightWithFlags(int8_t value) noexcept
	{
		registers_.PS[rps::Carry] = value & 1;
		value = uint8_t(value) >> 1;
		registers_.PS[rps::Negative] = value < 0;
		registers_.PS[rps::Zero] = value == 0;

		return value;
	}

	int8_t OpcodesExecutor::rotateLeftWithFlags(int8_t value) noexcept
	{
		int8_t oldCarry = registers_.PS[rps::Carry];
		registers_.PS[rps::Carry] = value >> (sizeof(value) * CHAR_BIT - 1);
		value = (value << 1) + oldCarry;
		registers_.PS[rps::Negative] = value < 0;
		registers_.PS[rps::Zero] = value == 0;

		return value;
	}

	int8_t OpcodesExecutor::rotateRightWithFlags(int8_t value) noexcept
	{
		int8_t oldCarry = registers_.PS[rps::Carry];
		registers_.PS[rps::Carry] = value & 1;
		value = (uint8_t(value) >> 1) + (oldCarry << (sizeof(value) * CHAR_BIT - 1));
		registers_.PS[rps::Negative] = value < 0;
		registers_.PS[rps::Zero] = value == 0;

		return value;
	}

	void OpcodesExecutor::transferWithFlags(int8_t& src, int8_t& dest)
	{
		dest = src;
		registers_.PS[rps::Negative] = src < 0;
		registers_.PS[rps::Zero] = src == 0;
	}


	void OpcodesExecutor::compareWithFlags(int8_t registerValue, int8_t inputValue) noexcept
	{
		registers_.PS[rps::Carry] = static_cast<uint8_t>(registerValue) >= static_cast<uint8_t>(inputValue);
		registers_.PS[rps::Negative] = int8_t(registerValue - inputValue) < 0;
		registers_.PS[rps::Zero] = registerValue == inputValue;
	}

	void OpcodesExecutor::loadWithFlags(int8_t& reg, int8_t value, std::bitset<registers::Registers::PSSize> & flags) noexcept
	{
		flags[rps::Negative] = value < 0;
		flags[rps::Zero] = value == 0;

		reg = value;
	}
}