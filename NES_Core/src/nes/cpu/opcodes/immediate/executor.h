#pragma once
#include "nes/cpu/registers/registers.h"

namespace nes::cpu::opcodes::immediate {
	class Executor
	{
	public:
		Executor(registers::Registers& registers) noexcept;
		~Executor() = default;
		Executor(Executor& rhs) = delete;
		Executor(Executor&& rhs) = delete;
		Executor& operator=(const Executor& rhs) = delete;
		Executor& operator=(Executor&& rhs) = delete;

		void ADC(int8_t value) noexcept;
	private:
		registers::Registers& registers_;
	private:
	};
}
