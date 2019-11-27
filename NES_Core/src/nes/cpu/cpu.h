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
		int8_t getImmediateValue();
		int8_t getRelativeValue();
		uint16_t getZeroPageAddress();
		uint16_t getZeroPageXAddress();
		uint16_t getZeroPageYAddress();
		uint16_t getAbsoluteAddress();
		uint16_t getAbsoluteXAddress();
		uint16_t getAbsoluteYAddress();
		uint16_t getIndirectXAddress();
		uint16_t getIndirectYAddress();
		uint16_t getIndirectAddress();

		static void logStatus(uint16_t PC, uint8_t opcode, uint16_t input, const registers::Registers& reg);
	};
}

