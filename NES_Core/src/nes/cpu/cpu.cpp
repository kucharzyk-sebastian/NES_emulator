#include "nes/cpu/cpu.h"
#include "thirdparty/easyloggingcpp/easylogging++.h"
#include <iomanip>

namespace nes::cpu
{
	CPU::CPU(registers::Registers& registers, memory::Memory& memory) :
		registers_(registers),
		memory_(memory),
		executor_(registers_, memory_)
	{
	}

	// TODO sk: maybe switch to map<opcode, function>
	enum OpcodeValues : uint8_t
	{
		BRK_imp = 0x00,
		ORA_ind_X = 0x01,
		ORA_zp = 0x05,
		ASL_zp = 0x06,
		PHP_imp = 0x08,
		ORA_imm = 0x09,
		ASL_acc = 0x0A,
		ORA_abs = 0x0D,
		ASL_abs = 0x0E,
		BPL_rel = 0x10,
		ORA_ind_Y = 0x011,
		ORA_zp_X = 0x15,
		ASL_zp_X = 0x16,
		CLC_imp = 0x18,
		ORA_abs_Y = 0x19,
		ORA_abs_X = 0x1D,
		ASL_abs_X = 0x1E,
		JSR_abs = 0x20,
		AND_ind_X = 0x21,
		BIT_zp = 0x24,
		AND_zp = 0x25,
		ROL_zp = 0x26,
		PLP_imp = 0x28,
		AND_imm = 0x29,
		ROL_acc = 0x2A,
		BIT_abs = 0x2C,
		AND_abs = 0x2D,
		ROL_abs = 0x2E,
		BMI_rel = 0x30,
		AND_ind_Y = 0x31,
		AND_zp_X = 0x35,
		ROL_zp_X = 0x36,
		SEC_imp = 0x38,
		AND_abs_Y = 0x39,
		AND_abs_X = 0x3D,
		ROL_abs_X = 0x3E,
		RTI_imp = 0x40,
		EOR_ind_X = 0x41,
		EOR_zp = 0x45,
		LSR_zp = 0x46,
		PHA_imp = 0x48,
		EOR_imm = 0x49,
		LSR_acc = 0x4A,
		JMP_abs = 0x4C,
		EOR_abs = 0x4D,
		LSR_abs = 0x4E,
		BVC_rel = 0x50,
		EOR_ind_Y = 0x51,
		EOR_zp_X = 0x55,
		LSR_zp_X = 0x56,
		CLI_imp = 0x58,
		EOR_abs_Y = 0x59,
		EOR_abs_X = 0x5D,
		LSR_abs_X = 0x5E,
		RTS_imp = 0x60,
		ADC_ind_X = 0x61,
		ADC_zp = 0x65,
		ROR_zp = 0x66,
		PLA_imp = 0x68,
		ADC_imm = 0x69,
		ROR_acc = 0x6A,
		JMP_ind = 0x6C,
		ADC_abs = 0x6D,
		ROR_abs = 0x6E,
		BVS_rel = 0x70,
		ADC_ind_Y = 0x71,
		ADC_zp_X = 0x75,
		ROR_zp_X = 0x76,
		SEI_imp = 0x78,
		ADC_abs_Y = 0x79,
		ADC_abs_X = 0x7D,
		ROR_abs_X = 0x7E,
		STA_ind_X = 0x81,
		STY_zp = 0x84,
		STA_zp = 0x85,
		STX_zp = 0x86,
		DEY_imp = 0x88,
		TXA_imp = 0x8A,
		STY_abs = 0x8C,
		STA_abs = 0x8D,
		STX_abs = 0x8E,
		BCC_rel = 0x90,
		STA_ind_Y = 0x91,
		STY_zp_X = 0x94,
		STA_zp_X = 0x95,
		STX_zp_Y = 0x96,
		TYA_imp = 0x98,
		STA_abs_X = 0x9D,
		STA_abs_Y = 0x99,
		TXS_imp = 0x9A,
		LDY_imm = 0xA0,
		LDA_ind_X = 0xA1,
		LDX_imm = 0xA2,
		LDY_zp = 0xA4,
		LDA_zp = 0xA5,
		LDX_zp = 0xA6,
		TAY_imp = 0xA8,
		LDA_imm = 0xA9,
		TAX_imp = 0xAA,
		LDY_abs = 0xAC,
		LDA_abs = 0xAD,
		LDX_abs = 0xAE,
		BCS_rel = 0xB0,
		LDA_ind_Y = 0xB1,
		LDY_zp_X = 0xB4,
		LDA_zp_X = 0xB5,
		LDX_zp_Y = 0xB6,
		CLV_imp = 0xB8,
		LDA_abs_Y = 0xB9,
		TSX_imp = 0xBA,
		LDY_abs_X = 0xBC,
		LDA_abs_X = 0xBD,
		LDX_abs_Y = 0xBE,
		CPY_imm = 0xC0,
		CMP_ind_X = 0xC1,
		CPY_zp = 0xC4,
		CMP_zp = 0xC5,
		DEC_zp = 0xC6,
		INY_imp = 0xC8,
		CMP_imm = 0xC9,
		DEX_imp = 0xCA,
		CPY_abs = 0xCC,
		CMP_abs = 0xCD,
		DEC_abs = 0xCE,
		BNE_rel = 0xD0,
		CMP_ind_Y = 0xD1,
		CMP_zp_X = 0xD5,
		DEC_zp_X = 0xD6,
		CLD_imp = 0xD8,
		CMP_abs_Y = 0xD9,
		CMP_abs_X = 0xDD,
		DEC_abs_X = 0xDE,
		CPX_imm = 0xE0,
		SBC_ind_X = 0xE1,
		CPX_zp = 0xE4,
		SBC_zp = 0xE5,
		INC_zp = 0xE6,
		INX_imp = 0xE8,
		SBC_imm = 0xE9,
		NOP_imp = 0xEA,
		CPX_abs = 0xEC,
		SBC_abs = 0xED,
		INC_abs = 0xEE,
		BEQ_rel = 0xF0,
		SBC_ind_Y = 0xF1,
		SBC_zp_X = 0xF5,
		INC_zp_X = 0xF6,
		SED_imp = 0xF8,
		SBC_abs_Y = 0xF9,
		SBC_abs_X = 0xFD,
		INC_abs_X = 0xFE
	};

#include <string>

	void nes::cpu::CPU::performInstruction()
	{
		switch (uint8_t(memory_[registers_.PC]))
		{
			case ADC_imm:
				executor_.ADC(getImmediateValue());
				break;
			case ADC_zp:
				executor_.ADC(getZeroPageAddress());
				break;
			case ADC_zp_X:
				executor_.ADC(getZeroPageXAddress());
				break;
			case ADC_abs:
				executor_.ADC(getAbsoluteAddress());
				break;
			case ADC_abs_X:
				executor_.ADC(getAbsoluteXAddress());
				break;
			case ADC_abs_Y:
				executor_.ADC(getAbsoluteYAddress());
				break;
			case ADC_ind_X:
				executor_.ADC(getIndirectXAddress());
				break;
			case ADC_ind_Y:
				executor_.ADC(getIndirectYAddress());
				break;
			case AND_imm:
				executor_.AND(getImmediateValue());
				break;
			case AND_zp:
				executor_.AND(getZeroPageAddress());
				break;
			case AND_zp_X:
				executor_.AND(getZeroPageXAddress());
				break;
			case AND_abs:
				executor_.AND(getAbsoluteAddress());
				break;
			case AND_abs_X:
				executor_.AND(getAbsoluteXAddress());
				break;
			case AND_abs_Y:
				executor_.AND(getAbsoluteYAddress());
				break;
			case AND_ind_X:
				executor_.AND(getIndirectXAddress());
				break;
			case AND_ind_Y:
				executor_.AND(getIndirectYAddress());
				break;
			case ASL_acc:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.ASL();
				break;
			case ASL_zp:
				executor_.ASL(getZeroPageAddress());
				break;
			case ASL_zp_X:
				executor_.ASL(getZeroPageXAddress());
				break;
			case ASL_abs:
				executor_.ASL(getAbsoluteAddress());
				break;
			case ASL_abs_X:
				executor_.ASL(getAbsoluteXAddress());
				break;
			case BCC_rel:
				executor_.BCC(getRelativeValue());
				break;
			case BCS_rel:
				executor_.BCS(getRelativeValue());
				break;
			case BEQ_rel:
				executor_.BEQ(getRelativeValue());
				break;
			case BIT_zp:
				executor_.BIT(getZeroPageAddress());
				break;
			case BIT_abs:
				executor_.BIT(getAbsoluteAddress());
				break;
			case BMI_rel:
				executor_.BMI(getRelativeValue());
				break;
			case BNE_rel:
				executor_.BNE(getRelativeValue());
				break;
			case BPL_rel:
				executor_.BPL(getRelativeValue());
				break;
			case BRK_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.BRK();
				return;
			case BVC_rel:
				executor_.BVC(getRelativeValue());
				break;
			case BVS_rel:
				executor_.BVS(getRelativeValue());
				break;
			case CLC_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.CLC();
				break;
			case CLD_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.CLD();
				break;
			case CLI_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.CLI();
				break;
			case CLV_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.CLV();
				break;
			case CMP_imm:
				executor_.CMP(getImmediateValue());
				break;
			case CMP_zp:
				executor_.CMP(getZeroPageAddress());
				break;
			case CMP_zp_X:
				executor_.CMP(getZeroPageXAddress());
				break;
			case CMP_abs:
				executor_.CMP(getAbsoluteAddress());
				break;
			case CMP_abs_X:
				executor_.CMP(getAbsoluteXAddress());
				break;
			case CMP_abs_Y:
				executor_.CMP(getAbsoluteYAddress());
				break;
			case CMP_ind_X:
				executor_.CMP(getIndirectXAddress());
				break;
			case CMP_ind_Y:
				executor_.CMP(getIndirectYAddress());
				break;
			case CPX_imm:
				executor_.CPX(getImmediateValue());
				break;
			case CPX_zp:
				executor_.CPX(getZeroPageAddress());
				break;
			case CPX_abs:
				executor_.CPX(getAbsoluteAddress());
				break;
			case CPY_imm:
				executor_.CPY(getImmediateValue());
				break;
			case CPY_zp:
				executor_.CPY(getZeroPageAddress());
				break;
			case CPY_abs:
				executor_.CPY(getAbsoluteAddress());
				break;
			case DEC_zp:
				executor_.DEC(getZeroPageAddress());
				break;
			case DEC_zp_X:
				executor_.DEC(getZeroPageXAddress());
				break;
			case DEC_abs:
				executor_.DEC(getAbsoluteAddress());
				break;
			case DEC_abs_X:
				executor_.DEC(getAbsoluteXAddress());
				break;
			case DEX_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.DEX();
				break;
			case DEY_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.DEY();
				break;
			case EOR_imm:
				executor_.EOR(getImmediateValue());
				break;
			case EOR_zp:
				executor_.EOR(getZeroPageAddress());
				break;
			case EOR_zp_X:
				executor_.EOR(getZeroPageXAddress());
				break;
			case EOR_abs:
				executor_.EOR(getAbsoluteAddress());
				break;
			case EOR_abs_X:
				executor_.EOR(getAbsoluteXAddress());
				break;
			case EOR_abs_Y:
				executor_.EOR(getAbsoluteYAddress());
				break;
			case EOR_ind_X:
				executor_.EOR(getIndirectXAddress());
				break;
			case EOR_ind_Y:
				executor_.EOR(getIndirectYAddress());
				break;
			case INC_zp:
				executor_.INC(getZeroPageAddress());
				break;
			case INC_zp_X:
				executor_.INC(getZeroPageXAddress());
				break;
			case INC_abs:
				executor_.INC(getAbsoluteAddress());
				break;
			case INC_abs_X:
				executor_.INC(getAbsoluteXAddress());
				break;
			case INX_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.INX();
				break;
			case INY_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.INY();
				break;
			case JMP_abs:
				executor_.JMP_absolute(getAbsoluteAddress());
				return;
			case JMP_ind:
				executor_.JMP_indirect(getIndirectAddress());
				return;
			case JSR_abs:
				executor_.JSR(getAbsoluteAddress());
				return;
			case LDA_imm:
				executor_.LDA(getImmediateValue());
				break;
			case LDA_zp:
				executor_.LDA(getZeroPageAddress());
				break;
			case LDA_zp_X:
				executor_.LDA(getZeroPageXAddress());
				break;
			case LDA_abs:
				executor_.LDA(getAbsoluteAddress());
				break;
			case LDA_abs_X:
				executor_.LDA(getAbsoluteXAddress());
				break;
			case LDA_abs_Y:
				executor_.LDA(getAbsoluteYAddress());
				break;
			case LDA_ind_X:
				executor_.LDA(getIndirectXAddress());
				break;
			case LDA_ind_Y:
				executor_.LDA(getIndirectYAddress());
				break;
			case LDX_imm:
				executor_.LDX(getImmediateValue());
				break;
			case LDX_zp:
				executor_.LDX(getZeroPageAddress());
				break;
			case LDX_zp_Y:
				executor_.LDX(getZeroPageYAddress());
				break;
			case LDX_abs:
				executor_.LDX(getAbsoluteAddress());
				break;
			case LDX_abs_Y:
				executor_.LDX(getAbsoluteYAddress());
				break;
			case LDY_imm:
				executor_.LDY(getImmediateValue());
				break;
			case LDY_zp:
				executor_.LDY(getZeroPageAddress());
				break;
			case LDY_zp_X:
				executor_.LDY(getZeroPageXAddress());
				break;
			case LDY_abs:
				executor_.LDY(getAbsoluteAddress());
				break;
			case LDY_abs_X:
				executor_.LDY(getAbsoluteXAddress());
				break;
			case LSR_acc:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.LSR();
				break;
			case LSR_zp:
				executor_.LSR(getZeroPageAddress());
				break;
			case LSR_zp_X:
				executor_.LSR(getZeroPageXAddress());
				break;
			case LSR_abs:
				executor_.LSR(getAbsoluteAddress());
				break;
			case LSR_abs_X:
				executor_.LSR(getAbsoluteXAddress());
				break;
			case NOP_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.NOP();
				return;
			case ORA_imm:
				executor_.ORA(getImmediateValue());
				break;
			case ORA_zp:
				executor_.ORA(getZeroPageAddress());
				break;
			case ORA_zp_X:
				executor_.ORA(getZeroPageXAddress());
				break;
			case ORA_abs:
				executor_.ORA(getAbsoluteAddress());
				break;
			case ORA_abs_X:
				executor_.ORA(getAbsoluteXAddress());
				break;
			case ORA_abs_Y:
				executor_.ORA(getAbsoluteYAddress());
				break;
			case ORA_ind_X:
				executor_.ORA(getIndirectXAddress());
				break;
			case ORA_ind_Y:
				executor_.ORA(getIndirectYAddress());
				break;
			case PHA_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.PHA();
				break;
			case PHP_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.PHP();
				break;
			case PLA_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.PLA();
				break;
			case PLP_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.PLP();
				break;
			case ROL_acc:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.ROL();
				break;
			case ROL_zp:
				executor_.ROL(getZeroPageAddress());
				break;
			case ROL_zp_X:
				executor_.ROL(getZeroPageXAddress());
				break;
			case ROL_abs:
				executor_.ROL(getAbsoluteAddress());
				break;
			case ROL_abs_X:
				executor_.ROL(getAbsoluteXAddress());
				break;
			case ROR_acc:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.ROR();
				break;
			case ROR_zp:
				executor_.ROR(getZeroPageAddress());
				break;
			case ROR_zp_X:
				executor_.ROR(getZeroPageXAddress());
				break;
			case ROR_abs:
				executor_.ROR(getAbsoluteAddress());
				break;
			case ROR_abs_X:
				executor_.ROR(getAbsoluteXAddress());
				break;
			case RTI_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.RTI();
				return;
			case RTS_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.RTS();
				return;
			case SBC_imm:
				executor_.SBC(getImmediateValue());
				break;
			case SBC_zp:
				executor_.SBC(getZeroPageAddress());
				break;
			case SBC_zp_X:
				executor_.SBC(getZeroPageXAddress());
				break;
			case SBC_abs:
				executor_.SBC(getAbsoluteAddress());
				break;
			case SBC_abs_X:
				executor_.SBC(getAbsoluteXAddress());
				break;
			case SBC_abs_Y:
				executor_.SBC(getAbsoluteYAddress());
				break;
			case SBC_ind_X:
				executor_.SBC(getIndirectXAddress());
				break;
			case SBC_ind_Y:
				executor_.SBC(getIndirectYAddress());
				break;
			case SEC_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.SEC();
				break;
			case SED_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.SED();
				break;
			case SEI_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.SEI();
				break;
			case STA_zp:
				executor_.STA(getZeroPageAddress());
				break;
			case STA_zp_X:
				executor_.STA(getZeroPageXAddress());
				break;
			case STA_abs:
				executor_.STA(getAbsoluteAddress());
				break;
			case STA_abs_X:
				executor_.STA(getAbsoluteXAddress());
				break;
			case STA_abs_Y:
				executor_.STA(getAbsoluteYAddress());
				break;
			case STA_ind_X:
				executor_.STA(getIndirectXAddress());
				break;
			case STA_ind_Y:
				executor_.STA(getIndirectYAddress());
				break;
			case STX_zp:
				executor_.STX(getZeroPageAddress());
				break;
			case STX_zp_Y:
				executor_.STX(getZeroPageYAddress());
				break;
			case STX_abs:
				executor_.STX(getAbsoluteAddress());
				break;
			case STY_zp:
				executor_.STY(getZeroPageAddress());
				break;
			case STY_zp_X:
				executor_.STY(getZeroPageXAddress());
				break;
			case STY_abs:
				executor_.STY(getAbsoluteAddress());
				break;
			case TAX_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.TAX();
				break;
			case TAY_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.TAY();
				break;
			case TSX_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.TSX();
				break;
			case TXA_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.TXA();
				break;
			case TXS_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.TXS();
				break;
			case TYA_imp:
				logStatus(registers_.PC, uint8_t(memory_[registers_.PC]), 0, registers_);
				executor_.TYA();
				break;
			default:
				throw std::exception("Not implemented opcode: " + memory_[registers_.PC]);

		}
		++registers_.PC;
	}
	
	int8_t CPU::getImmediateValue()
	{
		int8_t res = memory_[++registers_.PC];
		logStatus(registers_.PC - 1, uint8_t(memory_[registers_.PC - 1]), uint8_t(res), registers_);
		return res;
	}

	int8_t CPU::getRelativeValue()
	{
		int8_t res = memory_[++registers_.PC];
		logStatus(registers_.PC - 1, uint8_t(memory_[registers_.PC - 1]), uint8_t(res), registers_);
		return res;
	}

	uint16_t CPU::getZeroPageAddress()
	{
		uint8_t res = memory_[++registers_.PC];
		logStatus(registers_.PC - 1, uint8_t(memory_[registers_.PC - 1]), res, registers_);
		return res;
	}

	uint16_t CPU::getZeroPageXAddress()
	{
		uint8_t res = uint8_t(memory_[++registers_.PC]) + uint8_t(registers_.X);
		logStatus(registers_.PC - 1, uint8_t(memory_[registers_.PC - 1]), uint8_t(memory_[registers_.PC]), registers_);
		return res;
	}

	uint16_t CPU::getZeroPageYAddress()
	{
		uint8_t res = uint8_t(memory_[++registers_.PC]) + uint8_t(registers_.Y);
		logStatus(registers_.PC - 1, uint8_t(memory_[registers_.PC - 1]), uint8_t(memory_[registers_.PC]), registers_);

		return res;
	}

	uint16_t CPU::getAbsoluteAddress()
	{
		uint16_t res = uint8_t(memory_[++registers_.PC]) + (memory_[++registers_.PC] << CHAR_BIT);
		logStatus(registers_.PC - 2, uint8_t(memory_[registers_.PC - 2]), uint8_t(memory_[registers_.PC - 1]) + (memory_[registers_.PC] << CHAR_BIT), registers_);

		return res;
	}

	uint16_t CPU::getAbsoluteXAddress()
	{
		uint16_t res = uint8_t(memory_[++registers_.PC]) + (memory_[++registers_.PC] << CHAR_BIT) + uint8_t(registers_.X);
		logStatus(registers_.PC - 2, uint8_t(memory_[registers_.PC - 2]), uint8_t(memory_[registers_.PC - 1]) + (memory_[registers_.PC] << CHAR_BIT), registers_);

		return res;
	}

	uint16_t CPU::getAbsoluteYAddress()
	{
		uint16_t res = uint8_t(memory_[++registers_.PC]) + (memory_[++registers_.PC] << CHAR_BIT) + uint8_t(registers_.Y);
		logStatus(registers_.PC - 2, uint8_t(memory_[registers_.PC - 2]), uint8_t(memory_[registers_.PC - 1]) + (memory_[registers_.PC] << CHAR_BIT), registers_);

		return res;
	}

	uint16_t CPU::getIndirectXAddress()
	{
		uint8_t incomingAddress = memory_[++registers_.PC];
		uint16_t newAddress = uint8_t(incomingAddress + uint8_t(registers_.X));
		uint16_t res = uint8_t(memory_[newAddress]) + (memory_[uint8_t(newAddress + 1)] << CHAR_BIT);
		logStatus(registers_.PC - 1, uint8_t(memory_[registers_.PC - 1]), uint8_t(memory_[registers_.PC]), registers_);

		return res;
	}

	uint16_t CPU::getIndirectYAddress()
	{
		uint8_t incomingAddress = memory_[++registers_.PC];
		uint16_t res = uint8_t(memory_[incomingAddress]) + (memory_[uint8_t(incomingAddress + 1)] << CHAR_BIT) + uint8_t(registers_.Y);
		logStatus(registers_.PC - 1, uint8_t(memory_[registers_.PC - 1]), uint8_t(memory_[registers_.PC]), registers_);

		return  res;
	}

	uint16_t CPU::getIndirectAddress()
	{
		uint16_t res = uint8_t(memory_[++registers_.PC]) + (memory_[++registers_.PC] << CHAR_BIT);
		logStatus(registers_.PC - 2, uint8_t(memory_[registers_.PC - 2]), uint8_t(memory_[registers_.PC - 1]) + (memory_[registers_.PC] << CHAR_BIT), registers_);

		return res;
	}

	void CPU::logStatus(uint16_t PC, uint8_t opcode, uint16_t input, const registers::Registers& reg)
	{
		LOG(INFO) << std::hex << std::uppercase
			<< std::setfill('0') << std::setw(4) << PC << "  "
			<< std::setw(2) << int(opcode) << " "
			<< std::setw(4) << input << "  "
			<< "A:" << std::setw(2) << int(uint8_t(reg.A)) << " "
			<< "X:" << std::setw(2) << int(uint8_t(reg.X)) << " "
			<< "Y:" << std::setw(2) << int(uint8_t(reg.Y)) << " "
			<< "P:" << std::setw(2) << int(reg.PS.to_ulong()) << " "
			<< "SP:" << std::setw(2) << int(reg.SP);
	}
}
