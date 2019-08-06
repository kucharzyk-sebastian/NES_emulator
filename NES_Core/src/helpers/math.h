#pragma once

namespace helpers::math {
	template<typename T> 
	inline bool isOverflow(T lhs, T rhs, T result) noexcept(noexcept((lhs < 0 && rhs < 0 && result > 0) || (lhs > 0 && rhs > 0 && result < 0)))
	{
		return (lhs < 0 && rhs < 0 && result > 0) || (lhs > 0 && rhs > 0 && result < 0);
	}

	template<typename T>
	inline bool isCarry(T lhs, T rhs) noexcept(noexcept((lhs < 0 && rhs > 0 && rhs >= -lhs) || (rhs < 0 && lhs > 0 && lhs >= -rhs) || (lhs < 0 && rhs < 0)))
	{
		return (lhs < 0 && rhs > 0 && rhs >= -lhs) || (rhs < 0 && lhs > 0 && lhs >= -rhs) || (lhs < 0 && rhs < 0);
	}
}
