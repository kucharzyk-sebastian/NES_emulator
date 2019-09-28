#pragma once
#include "nes/cpu/registers.h"
#include "nes/cpu/opcodesExecutor.h"
#include "nes/memory/memory.h"

namespace nes::cpu {
	class CPU
	{
	public:
		CPU(registers::Registers& registers, memory::Memory& memory);
		~CPU() = default;
		CPU(const CPU& rhs) = delete;
		CPU(CPU&& rhs) = delete;
		CPU& operator=(const CPU& rhs) = delete;
		CPU& operator=(CPU&& rhs) = delete;

		void performInstruction();
	private:
		registers::Registers& registers_;
		memory::Memory& memory_;
		OpcodesExecutor executor_;
	private:
		uint16_t extractZeroPageAddressWithProgramCounter();
		uint16_t extractZeroPageXAddressWithProgramCounter();
		uint16_t extractAbsoluteAddressWithProgramCounter();
		uint16_t extractAbsoluteXAddressWithProgramCounter();
		uint16_t extractAbsoluteYAddressWithProgramCounter();
		uint16_t extractIndirectXAddressWithProgramCounter();
		uint16_t extractIndirectYAddressWithProgramCounter();
	};
}

