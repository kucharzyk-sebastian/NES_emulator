#pragma once
#include <cstdint>
#include <bitset>
#include "thirdparty/magicEnum.h"

//TODO sk: maybe incorporate ProcessorStatus into Registers
namespace nes::cpu::registers {
	enum class ProcessorStatus : uint8_t
	{
		Carry = 0,
		Zero = 1,
		InterruptDisable = 2,
		Decimal = 3,
		Break = 4,
		Unknown = 5,
		Overflow = 6,
		Negative = 7
	};

	struct Registers
	{
		int8_t A;
		int8_t X;
		int8_t Y;
		uint8_t SP;
		uint16_t PC;
		static constexpr size_t PSSize = magic_enum::enum_count<ProcessorStatus>();
		std::bitset<PSSize> PS;

		constexpr Registers() noexcept :
			A(0),
			X(0),
			Y(0),
			SP(0xFF),
			PS(0b00100100),
			PC(0)
		{
		}
	};
}

