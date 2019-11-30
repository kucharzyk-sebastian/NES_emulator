#include "nesemulator.h"
#include "thirdparty/easyloggingcpp/easylogging++.h"

INITIALIZE_EASYLOGGINGPP

namespace nes {
	NESEmulator::NESEmulator() :
		registers_(),
		memory_(),
		cpu_(registers_, memory_),
		romLoader_()
	{
	}

	void NESEmulator::run(const std::string& pathToROM)
	{
		romLoader_.loadMemory(pathToROM, memory_);
		el::Configurations conf("config_file.conf");
		el::Loggers::reconfigureAllLoggers(conf);
		registers_.PC = uint16_t(0xC000);
		while (true)
			cpu_.performInstruction();
	}
}
