#pragma once

namespace helpers::math {
	template<typename T> 
	inline bool isOverflow(T lhs, T rhs, T result)
	{
		return (lhs < 0 && rhs < 0 && result > 0) || (lhs > 0 && rhs > 0 && result < 0);
	}

	template<typename T>
	inline bool isCarry(T lhs, T rhs)
	{
		return (lhs < 0 && rhs > 0 && rhs >= -lhs) || (rhs < 0 && lhs > 0 && lhs >= -rhs) || (lhs < 0 && rhs < 0);
	}
}