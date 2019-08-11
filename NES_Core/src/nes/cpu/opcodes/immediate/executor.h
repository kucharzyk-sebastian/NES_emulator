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

		registers::Registers getRegisters() const noexcept;
		// TODO sk: think about move setRegisters version
		void setRegisters(const registers::Registers& registers) noexcept;

		// TODO sk: think about changing them to const once all implemented
		void ADC(int8_t value) noexcept;
		void AND(int8_t value) noexcept;
		void CMP(int8_t value) noexcept;
		void CPX(int8_t value) noexcept;
		void CPY(int8_t value) noexcept;
		void EOR(int8_t value) noexcept;
		void LDA(int8_t value) noexcept;
		void LDX(int8_t value) noexcept;
		void LDY(int8_t value) noexcept;
	private:
		registers::Registers& registers_;
	private:
		// TODO sk: think how to get rid of hardcoded 8 size
		static void compareWithFlags(int8_t& reg, int8_t value, std::bitset<8>& flags) noexcept;
	};
}
