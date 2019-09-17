#pragma once
#include "nes/cpu/opcodes/basicExecutor.h"

namespace nes::cpu::opcodes{
	class AccumulatorExecutor : public BasicExecutor
	{
	public:
		AccumulatorExecutor(nes::cpu::registers::Registers& registers, nes::memory::Memory& memory);
		~AccumulatorExecutor() = default;
		AccumulatorExecutor(const AccumulatorExecutor& rhs) = delete;
		AccumulatorExecutor(AccumulatorExecutor&& rhs) = delete;
		AccumulatorExecutor& operator=(const AccumulatorExecutor& rhs) = delete;
		AccumulatorExecutor& operator=(AccumulatorExecutor&& rhs) = delete;

		void ASL() noexcept;
		void LSR() noexcept;
		void ROL() noexcept;
	private:
	private:
	};
}
