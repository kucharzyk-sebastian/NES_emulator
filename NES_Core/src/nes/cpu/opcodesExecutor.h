#pragma once
#include "nes/cpu/registers.h"
#include "nes/memory/memory.h"

namespace nes::cpu{
	class OpcodesExecutor
	{
	public:
		OpcodesExecutor(registers::Registers& registers, memory::Memory& memory);
		~OpcodesExecutor() = default;
		OpcodesExecutor(const OpcodesExecutor& rhs) = delete;
		OpcodesExecutor(OpcodesExecutor&& rhs) = delete;
		OpcodesExecutor& operator=(const OpcodesExecutor& rhs) = delete;
		OpcodesExecutor& operator=(OpcodesExecutor&& rhs) = delete;

		void ADC(int8_t value) noexcept;
		void ADC(uint16_t address);
		void AND(int8_t value) noexcept;
		void AND(uint16_t address);
		void ASL() noexcept;
		void ASL(uint16_t address);
		void BCC(); // TODO sk: implement
		void BCS(); // TODO sk: implement
		void BEQ(); // TODO sk: implement
		void BIT(uint16_t address);
		void BMI(); // TODO sk: implement
		void BNE(); // TODO sk: implement
		void BPL(); // TODO sk: implement
		void BRK(); // TODO sk: implement
		void BVC(); // TODO sk: implement
		void CLC() noexcept;
		void CLD() noexcept;
		void CLI() noexcept;
		void CLV() noexcept;
		void CMP(int8_t value) noexcept;
		void CMP(uint16_t address);
		void CPX(int8_t value) noexcept;
		void CPX(uint16_t address);
		void CPY(int8_t value) noexcept;
		void CPY(uint16_t address);
		void DEC(uint16_t address);
		void DEX() noexcept;
		void DEY() noexcept;
		void EOR(int8_t value) noexcept;
		void EOR(uint16_t address);
		void INC(uint16_t address);
		void INX() noexcept;
		void INY() noexcept;
		void JMP();  // TODO sk: implement
		void JSR(); // TODO sk: implement
		void LDA(int8_t value) noexcept;
		void LDA(uint16_t address);
		void LDX(int8_t value) noexcept;
		void LDX(uint16_t address);
		void LDY(int8_t value) noexcept;
		void LDY(uint16_t address);
		void LSR() noexcept;
		void LSR(uint16_t address);
		void NOP() noexcept;
		void ORA(int8_t value) noexcept;
		void ORA(uint16_t address);
		void PHA();
		void PHP();
		void PLA();
		void PLP();
		void ROL() noexcept;
		void ROL(uint16_t address);
		void ROR() noexcept;
		void ROR(uint16_t address);
		void RTI(); // TODO sk: implement
		void RTS(); // TODO sk: implement
		void SBC(int8_t value) noexcept;
		void SBC(uint16_t address);
		void SEC() noexcept;
		void SED() noexcept;
		void SEI() noexcept;
		void STA();  // TODO sk: implement
		void STX(); // TODO sk: implement
		void STY(); // TODO sk: implement
		void TAX() noexcept;
		void TAY() noexcept;
		void TSX() noexcept;
		void TXA() noexcept;
		void TXS() noexcept;
		void TYA() noexcept;

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
		int8_t shiftLeftWithFlags(int8_t value) noexcept;
		int8_t decrementWithFlags(int8_t value) noexcept;
		int8_t incrementWithFlags(int8_t value) noexcept;
		int8_t shiftRightWithFlags(int8_t value) noexcept;
		int8_t rotateLeftWithFlags(int8_t value) noexcept;
		int8_t rotateRightWithFlags(int8_t value) noexcept;
		void compareWithFlags(int8_t registerValue, int8_t inputValue) noexcept;
		//todo sk: try to extract PSSize to ProcessorStatus enum
		static void loadWithFlags(int8_t& reg, int8_t value, std::bitset<registers::Registers::PSSize> & flags) noexcept;
	};
}