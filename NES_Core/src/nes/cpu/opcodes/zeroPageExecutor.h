#pragma once
#include "nes/cpu/opcodes/basicExecutor.h"

namespace nes::cpu::opcodes{
	class ZeroPageExecutor : private BasicExecutor
	{
	public:
		ZeroPageExecutor(registers::Registers& registers, memory::Memory& memory);
		~ZeroPageExecutor() = default;
		ZeroPageExecutor(const ZeroPageExecutor& rhs) = delete;
		ZeroPageExecutor(ZeroPageExecutor&& rhs) = delete;
		ZeroPageExecutor& operator=(const ZeroPageExecutor& rhs) = delete;
		ZeroPageExecutor& operator=(ZeroPageExecutor&& rhs) = delete;

		void ADC(uint8_t address);
	private:
		uint8_t page_ = 0x0000;
	};
}
