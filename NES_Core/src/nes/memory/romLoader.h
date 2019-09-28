#pragma once
#include <string>
#include <filesystem>
#include "nes/memory/memory.h"

namespace nes::memory{
	class RomLoader
	{
	public:
		RomLoader() = default;
		~RomLoader() = default;

		RomLoader(const RomLoader& rhs) = delete;
		RomLoader(RomLoader&& rhs) = delete;
		RomLoader& operator=(const RomLoader& rhs) = delete;
		RomLoader& operator=(RomLoader&& rhs) = delete;

		void loadMemory(const std::string& path, Memory& memory);
	};
}