#pragma once
#include <cstdint>

namespace helpers::math { 
	inline bool isOverflow(int8_t lhs, int8_t rhs) noexcept
	{
		int sum = int(lhs) + rhs;
		return (sum < INT8_MIN) || (sum > INT8_MAX);
	}

	inline bool isCarry(uint8_t lhs, uint8_t rhs) noexcept
	{
		return (int(lhs) + rhs) > UINT8_MAX;
	}
}
