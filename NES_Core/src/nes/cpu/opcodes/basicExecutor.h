#pragma once
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"

namespace nes::cpu::opcodes{
	class BasicExecutor
	{
	public:
		BasicExecutor(registers::Registers& registers, memory::Memory& memory);
		~BasicExecutor() = default;
		BasicExecutor(const BasicExecutor& rhs) = delete;
		BasicExecutor(BasicExecutor&& rhs) = delete;
		BasicExecutor& operator=(const BasicExecutor& rhs) = delete;
		BasicExecutor& operator=(BasicExecutor&& rhs) = delete;
	protected:
		registers::Registers& registers_;
		memory::Memory& memory_;
	protected:
		int8_t readFromStack();
		void writeToStack(int8_t value);
	private:
		static constexpr uint16_t stackPage_ = uint16_t(0x0100);
	};
}