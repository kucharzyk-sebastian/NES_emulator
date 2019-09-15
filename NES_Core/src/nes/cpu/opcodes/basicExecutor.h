#pragma once
#include "nes/cpu/registers/registers.h"

namespace nes::cpu::opcodes{
	class BasicExecutor
	{
	public:
		BasicExecutor(registers::Registers& registers);
		~BasicExecutor() = default;
		BasicExecutor(const BasicExecutor& rhs) = delete;
		BasicExecutor(BasicExecutor&& rhs) = delete;
		BasicExecutor& operator=(const BasicExecutor& rhs) = delete;
		BasicExecutor& operator=(BasicExecutor&& rhs) = delete;

		const registers::Registers& getRegisters() const noexcept;
		void setRegisters(const registers::Registers& registers) noexcept;
		void setRegisters(registers::Registers&& registers) noexcept;
	protected:
		registers::Registers& registers_;
	private:
	};
}