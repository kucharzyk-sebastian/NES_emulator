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

		void ADC(int8_t value) noexcept;
		void AND(int8_t value) noexcept;
		int8_t ASL(int8_t value) noexcept;
		void CMP(int8_t value) noexcept;
		void CPX(int8_t value) noexcept;
		void CPY(int8_t value) noexcept;
	protected:
		using rps =  registers::ProcessorStatus;
		registers::Registers& registers_;
		memory::Memory& memory_;
	protected:
		int8_t readFromStack();
		void writeToStack(int8_t value);
	private:
		static constexpr uint16_t stackPage_ = uint16_t(0x0100);
	private:
		void compareWithFlags(int8_t registerValue, int8_t inputValue) noexcept;
	};
}