#pragma once
#include "nes/cpu/registers/registers.h"

namespace nes {
	class CPU
	{
	public:
		CPU() = default;
		CPU(const CPU& rhs) = delete;
		CPU(CPU&& rhs) = delete;
		CPU& operator=(const CPU& rhs) = delete;
		CPU& operator=(CPU&& rhs) = delete;

		void performInstruction(int instruction);
		cpu::registers::Registers getRegisters();
	private:
		cpu::registers::Registers registers;
	private:
	};
}

