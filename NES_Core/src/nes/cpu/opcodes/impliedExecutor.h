#pragma once
#include "nes/cpu/registers/registers.h"
#include "nes/memory/memory.h"
#include "nes/cpu/opcodes/basicExecutor.h"

namespace nes::cpu::opcodes{
	class ImpliedExecutor : public BasicExecutor
	{
	public:
		ImpliedExecutor(registers::Registers& registers, memory::Memory& memory);
		~ImpliedExecutor() = default;
		ImpliedExecutor(const ImpliedExecutor& rhs) = delete;
		ImpliedExecutor(ImpliedExecutor&& rhs) = delete;
		ImpliedExecutor& operator=(const ImpliedExecutor& rhs) = delete;
		ImpliedExecutor& operator=(ImpliedExecutor&& rhs) = delete;

		// TODO sk: think about changing them to const once all implemented
		void BRK() noexcept; //TODO sk: implement
		void CLC() noexcept;
		void CLD() noexcept;
		void CLI() noexcept;
		void CLV() noexcept;
		void DEX() noexcept;
		void DEY() noexcept;
		void INX() noexcept;
		void INY() noexcept;
		void NOP() noexcept;
		void PHA();
		void PHP();
		void PLA();
		void PLP();
		void RTI(); //TODO sk: implement
		void RTS(); //TODO sk: implement
		void SEC() noexcept;
		void SED() noexcept;
		void SEI() noexcept;
	private:

	private:
	};
}
