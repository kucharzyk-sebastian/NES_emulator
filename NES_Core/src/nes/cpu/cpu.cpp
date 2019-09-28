#include "nes/cpu/cpu.h"

namespace nes::cpu
{
	CPU::CPU(registers::Registers& registers, memory::Memory& memory) :
		registers_(registers),
		memory_(memory),
		executor_(registers_, memory_)
	{
	}
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
		BPL_imp = 0x10,
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
		ROL = 0x2E,
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
		STA_abs_Y = 0x9D,
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
		SBS_ind_Y = 0xF1,
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
				executor_.ADC(memory_[++registers_.PC]);
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
		}
		++registers_.PC;
	}
	
	uint16_t CPU::extractZeroPageAddressWithProgramCounter()
	{
		return uint8_t(memory_[++registers_.PC]);
	}

	uint16_t CPU::extractZeroPageXAddressWithProgramCounter()
	{
		return uint8_t(memory_[++registers_.PC]) + uint8_t(registers_.X);
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
		uint16_t newAddress = incomingAddress + uint8_t(registers_.X);
		return uint8_t(memory_[newAddress]) + (memory_[newAddress + 1] << CHAR_BIT);
	}

	uint16_t CPU::extractIndirectYAddressWithProgramCounter()
	{
		uint8_t incomingAddress = memory_[++registers_.PC];
		return  uint8_t(memory_[incomingAddress]) + (memory_[incomingAddress + 1] << CHAR_BIT) + uint8_t(registers_.Y);
	}

}
