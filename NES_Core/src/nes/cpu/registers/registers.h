#pragma once
#include <cstdint>
#include <bitset>

namespace nes::cpu::registers {
	enum class ProcessorStatus : uint8_t
	{
		Carry = 0,
		Zero = 1,
		InterruptDisable = 2,
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
		static constexpr uint8_t PSSize = 8;
		std::bitset<PSSize> PS;

		constexpr Registers() noexcept :
			A(0),
			X(0),
			Y(0),
			SP(0xFF),
			PS(0b00110100),
			PC(0)
		{
		}
	};
}

