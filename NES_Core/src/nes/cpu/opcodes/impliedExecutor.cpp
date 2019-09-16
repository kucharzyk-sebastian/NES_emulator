#include "nes/cpu/opcodes/impliedExecutor.h"

namespace nes::cpu::opcodes{
	using rps =  registers::ProcessorStatus;

	ImpliedExecutor::ImpliedExecutor(registers::Registers& registers, memory::Memory& memory) :
		BasicExecutor(registers, memory)
	{
	}

	void ImpliedExecutor::CLC() noexcept
	{
		registers_.PS.reset(static_cast<uint8_t>(rps::Carry));
	}

	void ImpliedExecutor::CLD() noexcept
	{
		registers_.PS.reset(static_cast<uint8_t>(rps::Decimal));
	}

	void ImpliedExecutor::CLI() noexcept
	{
		registers_.PS.reset(static_cast<uint8_t>(rps::InterruptDisable));
	}

	void ImpliedExecutor::CLV() noexcept
	{
		registers_.PS.reset(static_cast<uint8_t>(rps::Overflow));
	}

	void ImpliedExecutor::DEX() noexcept
	{
		int8_t result = registers_.X - 1;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = result < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = result == 0 ? true : false;

		registers_.X = result;
	}

	void ImpliedExecutor::DEY() noexcept
	{
		int8_t result = registers_.Y - 1;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = result < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = result == 0 ? true : false;

		registers_.Y = result;
	}

	void ImpliedExecutor::INX() noexcept
	{
		int8_t result = registers_.X + 1;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = result < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = result == 0 ? true : false;

		registers_.X = result;
	}

	void ImpliedExecutor::INY() noexcept
	{
		int8_t result = registers_.Y + 1;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = result < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = result == 0 ? true : false;

		registers_.Y = result;
	}

	//TODO sk: probably will need to increase program counter
	void ImpliedExecutor::NOP() noexcept
	{
	}

	void ImpliedExecutor::PHA()
	{
		writeToStack(registers_.A);
	}

	void ImpliedExecutor::PHP()
	{
		writeToStack(static_cast<int8_t>(registers_.PS.to_ulong()));
	}

	void ImpliedExecutor::PLA()
	{
		registers_.A = readFromStack();
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = registers_.A < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = registers_.A == 0 ? true : false;
	}

	void ImpliedExecutor::PLP()
	{
		registers_.PS = readFromStack();
	}

	void ImpliedExecutor::SEC() noexcept
	{
		registers_.PS.set(static_cast<uint8_t>(rps::Carry));
	}

	void ImpliedExecutor::SED() noexcept
	{
		registers_.PS.set(static_cast<uint8_t>(rps::Decimal));
	}

	void ImpliedExecutor::SEI() noexcept
	{
		registers_.PS.set(static_cast<uint8_t>(rps::InterruptDisable));
	}

	void ImpliedExecutor::TAX() noexcept
	{
		registers_.X = registers_.A;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = registers_.X < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = registers_.X == 0 ? true : false;
	}

	void ImpliedExecutor::TAY() noexcept
	{
		registers_.Y = registers_.A;
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = registers_.Y < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = registers_.Y == 0 ? true : false;
	}

	void ImpliedExecutor::TSX() noexcept
	{
		registers_.X = int8_t(registers_.SP);
		registers_.PS[static_cast<uint8_t>(rps::Negative)] = registers_.X < 0 ? true : false;
		registers_.PS[static_cast<uint8_t>(rps::Zero)] = registers_.X == 0 ? true : false;
	}
}
