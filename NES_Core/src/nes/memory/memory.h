#pragma once
#include <array>

namespace nes::memory {
	class Memory
	{
	public:
		Memory();
		~Memory() = default;
		Memory(const Memory& rhs) = delete;
		Memory(Memory&& rhs) = delete;
		Memory& operator=(const Memory& rhs) = delete;
		Memory& operator=(Memory&& rhs) = delete;

		int8_t& operator[](uint16_t address);
	private:
		static constexpr int memorySize_ = 0xFFFF + 0x1;
		using MemArray = std::array<int8_t, memorySize_>;
		std::shared_ptr<MemArray> memory_;
	};
}
