#pragma once
#include <limits>

namespace helpers::math { 
	inline bool isOverflow(int8_t lhs, int8_t rhs, int8_t result, bool isSubtraction = false) noexcept
	{
		if (isSubtraction)
			rhs = -rhs;
		return (lhs <= 0 && rhs <= 0 && result > 0) || (lhs >= 0 && rhs >= 0 && result < 0);
	}

	inline bool isCarry(uint8_t lhs, uint8_t rhs) noexcept
	{
		return (int(lhs) + rhs) > UINT8_MAX;
	}

	inline bool isCarry(int8_t lhs, int8_t rhs) noexcept
	{
		return isCarry(uint8_t(lhs), uint8_t(rhs));
	}
}
