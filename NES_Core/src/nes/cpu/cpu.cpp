#include "nes/cpu/cpu.h"

namespace nes::cpu
{
	CPU::CPU(registers::Registers& registers, memory::Memory& memory) :
		registers_(registers),
		memory_(memory),
		executor_(registers_, memory_)
	{
	}

	// TODO sk: maybe switch to map<opcode, function>
	enum OpcodeValues : int8_t
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

	void nes::cpu::CPU::performInstruction()
	{
		switch (memory_[registers_.PC])
		{
			case ADC_imm:
				executor_.ADC(extractImmediatevalueWithProgramCounter());
				break;
			case ADC_zp:
				executor_.ADC(extractZeroPageAddressWithProgramCounter());
				break;
			case ADC_zp_X:
				executor_.ADC(extractZeroPageXAddressWithProgramCounter());
				break;
			case ADC_abs:
				executor_.ADC(extractAbsoluteAddressWithProgramCounter());
				break;
			case ADC_abs_X:
				executor_.ADC(extractAbsoluteXAddressWithProgramCounter());
				break;
			case ADC_abs_Y:
				executor_.ADC(extractAbsoluteYAddressWithProgramCounter());
				break;
			case ADC_ind_X:
				executor_.ADC(extractIndirectXAddressWithProgramCounter());
				break;
			case ADC_ind_Y:
				executor_.ADC(extractIndirectYAddressWithProgramCounter());
				break;
			case AND_imm:
				executor_.AND(extractImmediatevalueWithProgramCounter());
				break;
			case AND_zp:
				executor_.AND(extractZeroPageAddressWithProgramCounter());
				break;
			case AND_zp_X:
				executor_.AND(extractZeroPageXAddressWithProgramCounter());
				break;
			case AND_abs:
				executor_.AND(extractAbsoluteAddressWithProgramCounter());
				break;
			case AND_abs_X:
				executor_.AND(extractAbsoluteXAddressWithProgramCounter());
				break;
			case AND_abs_Y:
				executor_.AND(extractAbsoluteYAddressWithProgramCounter());
				break;
			case AND_ind_X:
				executor_.AND(extractIndirectXAddressWithProgramCounter());
				break;
			case AND_ind_Y:
				executor_.AND(extractIndirectYAddressWithProgramCounter());
				break;
			case ASL_acc:
				executor_.ASL();
				break;
			case ASL_zp:
				executor_.ASL(extractZeroPageAddressWithProgramCounter());
				break;
			case ASL_zp_X:
				executor_.ASL(extractZeroPageXAddressWithProgramCounter());
				break;
			case ASL_abs:
				executor_.ASL(extractAbsoluteAddressWithProgramCounter());
				break;
			case ASL_abs_X:
				executor_.ASL(extractAbsoluteXAddressWithProgramCounter());
				break;
			case BCC_rel:
				executor_.BCC(extractRelativevalueWithProgramCounter());
				break;
			case BCS_rel:
				executor_.BCS(extractRelativevalueWithProgramCounter());
				break;
			case BEQ_rel:
				executor_.BEQ(extractRelativevalueWithProgramCounter());
				break;
			case BIT_zp:
				executor_.BIT(extractZeroPageAddressWithProgramCounter());
				break;
			case BIT_abs:
				executor_.BIT(extractAbsoluteAddressWithProgramCounter());
				break;
			case BMI_rel:
				executor_.BMI(extractRelativevalueWithProgramCounter());
				break;
			case BNE_rel:
				executor_.BNE(extractRelativevalueWithProgramCounter());
				break;
			case BPL_rel:
				executor_.BPL(extractRelativevalueWithProgramCounter());
				break;
			case BRK_imp:
				executor_.BRK();
				return;
			case BVC_rel:
				executor_.BVC(extractRelativevalueWithProgramCounter());
				break;
			case BVS_rel:
				executor_.BVS(extractRelativevalueWithProgramCounter());
				break;
			case CLC_imp:
				executor_.CLC();
				break;
			case CLD_imp:
				executor_.CLD();
				break;
			case CLI_imp:
				executor_.CLI();
				break;
			case CLV_imp:
				executor_.CLV();
				break;
			case CMP_imm:
				executor_.CMP(extractImmediatevalueWithProgramCounter());
				break;
			case CMP_zp:
				executor_.CMP(extractZeroPageAddressWithProgramCounter());
				break;
			case CMP_zp_X:
				executor_.CMP(extractZeroPageXAddressWithProgramCounter());
				break;
			case CMP_abs:
				executor_.CMP(extractAbsoluteAddressWithProgramCounter());
				break;
			case CMP_abs_X:
				executor_.CMP(extractAbsoluteXAddressWithProgramCounter());
				break;
			case CMP_abs_Y:
				executor_.CMP(extractAbsoluteYAddressWithProgramCounter());
				break;
			case CMP_ind_X:
				executor_.CMP(extractIndirectXAddressWithProgramCounter());
				break;
			case CMP_ind_Y:
				executor_.CMP(extractIndirectYAddressWithProgramCounter());
				break;
			case CPX_imm:
				executor_.CPX(extractImmediatevalueWithProgramCounter());
				break;
			case CPX_zp:
				executor_.CPX(extractZeroPageAddressWithProgramCounter());
				break;
			case CPX_abs:
				executor_.CPX(extractAbsoluteAddressWithProgramCounter());
				break;
			case CPY_imm:
				executor_.CPY(extractImmediatevalueWithProgramCounter());
				break;
			case CPY_zp:
				executor_.CPY(extractZeroPageAddressWithProgramCounter());
				break;
			case CPY_abs:
				executor_.CPY(extractAbsoluteAddressWithProgramCounter());
				break;
			case DEC_zp:
				executor_.DEC(extractZeroPageAddressWithProgramCounter());
				break;
			case DEC_zp_X:
				executor_.DEC(extractZeroPageXAddressWithProgramCounter());
				break;
			case DEC_abs:
				executor_.DEC(extractAbsoluteAddressWithProgramCounter());
				break;
			case DEC_abs_X:
				executor_.DEC(extractAbsoluteXAddressWithProgramCounter());
				break;
			case DEX_imp:
				executor_.DEX();
				break;
			case DEY_imp:
				executor_.DEY();
				break;
			case EOR_imm:
				executor_.EOR(extractImmediatevalueWithProgramCounter());
				break;
			case EOR_zp:
				executor_.EOR(extractZeroPageAddressWithProgramCounter());
				break;
			case EOR_zp_X:
				executor_.EOR(extractZeroPageXAddressWithProgramCounter());
				break;
			case EOR_abs:
				executor_.EOR(extractAbsoluteAddressWithProgramCounter());
				break;
			case EOR_abs_X:
				executor_.EOR(extractAbsoluteXAddressWithProgramCounter());
				break;
			case EOR_abs_Y:
				executor_.EOR(extractAbsoluteYAddressWithProgramCounter());
				break;
			case EOR_ind_X:
				executor_.EOR(extractIndirectXAddressWithProgramCounter());
				break;
			case EOR_ind_Y:
				executor_.EOR(extractIndirectYAddressWithProgramCounter());
				break;
			case INC_zp:
				executor_.INC(extractZeroPageAddressWithProgramCounter());
				break;
			case INC_zp_X:
				executor_.INC(extractZeroPageXAddressWithProgramCounter());
				break;
			case INC_abs:
				executor_.INC(extractAbsoluteAddressWithProgramCounter());
				break;
			case INC_abs_X:
				executor_.INC(extractAbsoluteXAddressWithProgramCounter());
				break;
			case INX_imp:
				executor_.INX();
				break;
			case INY_imp:
				executor_.INY();
				break;
			case JMP_abs:
				executor_.JMP_absolute(extractAbsoluteAddressWithProgramCounter());
				return;
			case JMP_ind:
				executor_.JMP_indirect(extractIndirectAddressWithProgramCounter());
				return;
			case JSR_abs:
				executor_.JSR(extractAbsoluteAddressWithProgramCounter());
				return;
			case LDA_imm:
				executor_.LDA(extractImmediatevalueWithProgramCounter());
				break;
			case LDA_zp:
				executor_.LDA(extractZeroPageAddressWithProgramCounter());
				break;
			case LDA_zp_X:
				executor_.LDA(extractZeroPageXAddressWithProgramCounter());
				break;
			case LDA_abs:
				executor_.LDA(extractAbsoluteAddressWithProgramCounter());
				break;
			case LDA_abs_X:
				executor_.LDA(extractAbsoluteXAddressWithProgramCounter());
				break;
			case LDA_abs_Y:
				executor_.LDA(extractAbsoluteYAddressWithProgramCounter());
				break;
			case LDA_ind_X:
				executor_.LDA(extractIndirectXAddressWithProgramCounter());
				break;
			case LDA_ind_Y:
				executor_.LDA(extractIndirectYAddressWithProgramCounter());
				break;
			case LDX_imm:
				executor_.LDX(extractImmediatevalueWithProgramCounter());
				break;
			case LDX_zp:
				executor_.LDX(extractZeroPageAddressWithProgramCounter());
				break;
			case LDX_zp_Y:
				executor_.LDX(extractZeroPageYAddressWithProgramCounter());
				break;
			case LDX_abs:
				executor_.LDX(extractAbsoluteAddressWithProgramCounter());
				break;
			case LDX_abs_Y:
				executor_.LDX(extractAbsoluteYAddressWithProgramCounter());
				break;
			case LDY_imm:
				executor_.LDY(extractImmediatevalueWithProgramCounter());
				break;
			case LDY_zp:
				executor_.LDY(extractZeroPageAddressWithProgramCounter());
				break;
			case LDY_zp_X:
				executor_.LDY(extractZeroPageXAddressWithProgramCounter());
				break;
			case LDY_abs:
				executor_.LDY(extractAbsoluteAddressWithProgramCounter());
				break;
			case LDY_abs_X:
				executor_.LDY(extractAbsoluteXAddressWithProgramCounter());
				break;
			case LSR_acc:
				executor_.LSR();
				break;
			case LSR_zp:
				executor_.LSR(extractZeroPageAddressWithProgramCounter());
				break;
			case LSR_zp_X:
				executor_.LSR(extractZeroPageXAddressWithProgramCounter());
				break;
			case LSR_abs:
				executor_.LSR(extractAbsoluteAddressWithProgramCounter());
				break;
			case LSR_abs_X:
				executor_.LSR(extractAbsoluteXAddressWithProgramCounter());
				break;
			case NOP_imp:
				executor_.NOP();
				return;
			case ORA_imm:
				executor_.ORA(extractImmediatevalueWithProgramCounter());
				break;
			case ORA_zp:
				executor_.ORA(extractZeroPageAddressWithProgramCounter());
				break;
			case ORA_zp_X:
				executor_.ORA(extractZeroPageXAddressWithProgramCounter());
				break;
			case ORA_abs:
				executor_.ORA(extractAbsoluteAddressWithProgramCounter());
				break;
			case ORA_abs_X:
				executor_.ORA(extractAbsoluteXAddressWithProgramCounter());
				break;
			case ORA_abs_Y:
				executor_.ORA(extractAbsoluteYAddressWithProgramCounter());
				break;
			case ORA_ind_X:
				executor_.ORA(extractIndirectXAddressWithProgramCounter());
				break;
			case ORA_ind_Y:
				executor_.ORA(extractIndirectYAddressWithProgramCounter());
				break;
			case PHA_imp:
				executor_.PHA();
				break;
			case PHP_imp:
				executor_.PHP();
				break;
			case PLA_imp:
				executor_.PLA();
				break;
			case PLP_imp:
				executor_.PLP();
				break;
			case ROL_acc:
				executor_.ROL();
				break;
			case ROL_zp:
				executor_.ROL(extractZeroPageAddressWithProgramCounter());
				break;
			case ROL_zp_X:
				executor_.ROL(extractZeroPageXAddressWithProgramCounter());
				break;
			case ROL_abs:
				executor_.ROL(extractAbsoluteAddressWithProgramCounter());
				break;
			case ROL_abs_X:
				executor_.ROL(extractAbsoluteXAddressWithProgramCounter());
				break;
			case ROR_acc:
				executor_.ROR();
				break;
			case ROR_zp:
				executor_.ROR(extractZeroPageAddressWithProgramCounter());
				break;
			case ROR_zp_X:
				executor_.ROR(extractZeroPageXAddressWithProgramCounter());
				break;
			case ROR_abs:
				executor_.ROR(extractAbsoluteAddressWithProgramCounter());
				break;
			case ROR_abs_X:
				executor_.ROR(extractAbsoluteXAddressWithProgramCounter());
				break;
			case RTI_imp:
				executor_.RTI();
				return;
			case RTS_imp:
				executor_.RTS();
				return;
			case SBC_imm:
				executor_.SBC(extractImmediatevalueWithProgramCounter());
				break;
			case SBC_zp:
				executor_.SBC(extractZeroPageAddressWithProgramCounter());
				break;
			case SBC_zp_X:
				executor_.SBC(extractZeroPageXAddressWithProgramCounter());
				break;
			case SBC_abs:
				executor_.SBC(extractAbsoluteAddressWithProgramCounter());
				break;
			case SBC_abs_X:
				executor_.SBC(extractAbsoluteXAddressWithProgramCounter());
				break;
			case SBC_abs_Y:
				executor_.SBC(extractAbsoluteYAddressWithProgramCounter());
				break;
			case SBC_ind_X:
				executor_.SBC(extractIndirectXAddressWithProgramCounter());
				break;
			case SBC_ind_Y:
				executor_.SBC(extractIndirectYAddressWithProgramCounter());
				break;
			case SEC_imp:
				executor_.SEC();
				break;
			case SED_imp:
				executor_.SED();
				break;
			case SEI_imp:
				executor_.SEI();
				break;
			case STA_zp:
				executor_.STA(extractZeroPageAddressWithProgramCounter());
				break;
			case STA_zp_X:
				executor_.STA(extractZeroPageXAddressWithProgramCounter());
				break;
			case STA_abs:
				executor_.STA(extractAbsoluteAddressWithProgramCounter());
				break;
			case STA_abs_X:
				executor_.STA(extractAbsoluteXAddressWithProgramCounter());
				break;
			case STA_abs_Y:
				executor_.STA(extractAbsoluteYAddressWithProgramCounter());
				break;
			case STA_ind_X:
				executor_.STA(extractIndirectXAddressWithProgramCounter());
				break;
			case STA_ind_Y:
				executor_.STA(extractIndirectYAddressWithProgramCounter());
				break;
			case STX_zp:
				executor_.STX(extractZeroPageAddressWithProgramCounter());
				break;
			case STX_zp_Y:
				executor_.STX(extractZeroPageYAddressWithProgramCounter());
				break;
			case STX_abs:
				executor_.STX(extractAbsoluteAddressWithProgramCounter());
				break;
			case STY_zp:
				executor_.STY(extractZeroPageAddressWithProgramCounter());
				break;
			case STY_zp_X:
				executor_.STY(extractZeroPageXAddressWithProgramCounter());
				break;
			case STY_abs:
				executor_.STY(extractAbsoluteAddressWithProgramCounter());
				break;
			case TAX_imp:
				executor_.TAX();
				break;
			case TAY_imp:
				executor_.TAY();
				break;
			case TSX_imp:
				executor_.TSX();
				break;
			case TXA_imp:
				executor_.TXA();
				break;
			case TXS_imp:
				executor_.TXS();
				break;
			case TYA_imp:
				executor_.TYA();
				break;
			default:
				throw std::exception("Not implemented opcode: " + memory_[registers_.PC]);

		}
		++registers_.PC;
	}
	
	int8_t CPU::extractImmediatevalueWithProgramCounter()
	{
		return memory_[++registers_.PC];
	}

	int8_t CPU::extractRelativevalueWithProgramCounter()
	{
		return memory_[++registers_.PC];
	}

	uint16_t CPU::extractZeroPageAddressWithProgramCounter()
	{
		return uint8_t(memory_[++registers_.PC]);
	}

	uint16_t CPU::extractZeroPageXAddressWithProgramCounter()
	{
		return uint8_t(uint8_t(memory_[++registers_.PC]) + uint8_t(registers_.X));
	}

	uint16_t CPU::extractZeroPageYAddressWithProgramCounter()
	{
		return uint8_t(uint8_t(memory_[++registers_.PC]) + uint8_t(registers_.Y));
	}

	uint16_t CPU::extractAbsoluteAddressWithProgramCounter()
	{
		return uint8_t(memory_[++registers_.PC]) + (memory_[++registers_.PC] << CHAR_BIT);
	}

	uint16_t CPU::extractAbsoluteXAddressWithProgramCounter()
	{
		return uint8_t(memory_[++registers_.PC]) + (memory_[++registers_.PC] << CHAR_BIT) + uint8_t(registers_.X);
	}

	uint16_t CPU::extractAbsoluteYAddressWithProgramCounter()
	{
		return uint8_t(memory_[++registers_.PC]) + (memory_[++registers_.PC] << CHAR_BIT) + uint8_t(registers_.Y);
	}

	uint16_t CPU::extractIndirectXAddressWithProgramCounter()
	{
		uint8_t incomingAddress = memory_[++registers_.PC];
		uint16_t newAddress = uint8_t(incomingAddress + uint8_t(registers_.X));
		return uint8_t(memory_[newAddress]) + (memory_[newAddress + 1] << CHAR_BIT);
	}

	uint16_t CPU::extractIndirectYAddressWithProgramCounter()
	{
		uint8_t incomingAddress = memory_[++registers_.PC];
		return  uint8_t(memory_[incomingAddress]) + (memory_[incomingAddress + 1] << CHAR_BIT) + uint8_t(registers_.Y);
	}

	uint16_t CPU::extractIndirectAddressWithProgramCounter()
	{
		return uint8_t(memory_[++registers_.PC]) + (memory_[++registers_.PC] << CHAR_BIT);
	}

}
