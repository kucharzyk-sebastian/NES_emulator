#pragma once
#include "nes/cpu/registers/registers.h"

namespace nes::cpu::opcodes::implied{
	class Executor
	{
	public:
		Executor(registers::Registers& registers) noexcept;
		~Executor() = default;
		Executor(Executor& rhs) = delete;
		Executor(Executor&& rhs) = delete;
		Executor& operator=(const Executor& rhs) = delete;
		Executor& operator=(Executor&& rhs) = delete;

		registers::Registers getRegisters() const noexcept;
		// TODO sk: think about move setRegisters version
		void setRegisters(const registers::Registers& registers) noexcept;

		// TODO sk: think about changing them to const once all implemented
		//TODO sk: not implemented yet
		void BRK() noexcept;
		void CLC() noexcept;
		void CLD() noexcept;
		void CLI() noexcept;
		void CLV() noexcept;
		void DEX() noexcept;
		void SEC() noexcept;
		void SED() noexcept;
		void SEI() noexcept;
	private:
		registers::Registers& registers_;
	private:
	};
}
