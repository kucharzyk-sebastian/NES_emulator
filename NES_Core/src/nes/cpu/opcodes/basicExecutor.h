#pragma once
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"

namespace nes::cpu::opcodes{
	class BasicExecutor
	{
	public:
		BasicExecutor(registers::Registers& registers, memory::Memory& memory);
		virtual ~BasicExecutor() = 0;
		BasicExecutor(const BasicExecutor& rhs) = delete;
		BasicExecutor(BasicExecutor&& rhs) = delete;
		BasicExecutor& operator=(const BasicExecutor& rhs) = delete;
		BasicExecutor& operator=(BasicExecutor&& rhs) = delete;
	protected:
		using rps =  registers::ProcessorStatus;
		registers::Registers& registers_;
		memory::Memory& memory_;
	protected:
		int8_t readFromStack();
		void writeToStack(int8_t value);
		int8_t ADC(int8_t lhs, int8_t rhs) noexcept;
	private:
		static constexpr uint16_t stackPage_ = uint16_t(0x0100);
	};
}