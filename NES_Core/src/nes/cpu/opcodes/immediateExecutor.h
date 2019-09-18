#pragma once
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodes/basicExecutor.h"

namespace nes::cpu::opcodes{
	class ImmediateExecutor : private BasicExecutor
	{
	public:
		ImmediateExecutor(registers::Registers& registers, memory::Memory& memory);
		~ImmediateExecutor() = default;
		ImmediateExecutor(const ImmediateExecutor& rhs) = delete;
		ImmediateExecutor(ImmediateExecutor&& rhs) = delete;
		ImmediateExecutor& operator=(const ImmediateExecutor& rhs) = delete;
		ImmediateExecutor& operator=(ImmediateExecutor&& rhs) = delete;

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
		void ORA(int8_t value) noexcept;
		void SBC(int8_t value) noexcept;
	private:

	private:
		// TODO sk: think how to get rid of hardcoded 8 size
		static void compareWithFlags(int8_t& reg, int8_t value, std::bitset<8>& flags) noexcept;
		static void loadWithFlags(int8_t& reg, int8_t value, std::bitset<8>& flags) noexcept;
	};
}
