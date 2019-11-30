#pragma once
#include <cstdint>

namespace helpers::math { 
	inline bool isOverflow(int8_t lhs, int8_t rhs) noexcept
	{
		int sum = int(lhs) + rhs;
		return (sum < INT8_MIN) || (sum > INT8_MAX);
	}

	// TODO sk: add unit tests for this
	inline bool isOverflow(int8_t first, int8_t second, int8_t third) noexcept
	{
		int sum = int(first) + second + third;
		return (sum < INT8_MIN) || (sum > INT8_MAX);
	}

	inline bool isCarry(uint8_t lhs, uint8_t rhs) noexcept
	{
		return (int(lhs) + rhs) > UINT8_MAX;
	}

	inline bool isCarry(uint8_t first, uint8_t second, uint8_t third) noexcept
	{
		return (int(first) + second + third) > UINT8_MAX;
	}
}
