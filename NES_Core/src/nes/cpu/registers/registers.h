#pragma once
#include <cstdint>
#include <bitset>

namespace nes::cpu::registers {
	enum class ProcessorStatus : uint8_t
	{
		Carry = 0,
		Zero = 1,
		Interrupt = 2,
		Decimal = 3,
		Break = 4,
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
		std::bitset<8> PS;

		//TODO sk: verify default values of registers and create unit tests for defaults
		constexpr Registers() noexcept :
			A(0),
			X(0),
			Y(0),
			SP(0),
			PS(0b00110100),
			PC(0)
		{
		}
	};
}

