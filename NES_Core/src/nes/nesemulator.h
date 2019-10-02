#pragma once
#include "nes/memory/romLoader.h"
#include "nes/memory/memory.h"
#include "nes/cpu/registers.h"
#include "nes/cpu/cpu.h"

namespace nes {
	class NESEmulator
	{
	public:
		NESEmulator();
		void run(const std::string& pathToROM);

	private:
		void loadROM();

	private:
		memory::Memory memory_;
		memory::RomLoader romLoader_;
		cpu::registers::Registers registers_;
		cpu::CPU cpu_;
	};
}
