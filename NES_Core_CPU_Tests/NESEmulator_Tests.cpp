#include "CppUnitTest.h"
#include "nes/nesEmulator.h"
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>
#include <functional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NESEmulator_Tests
{
	TEST_CLASS(NESEmulator_Tests)
	{
	public:
		nes::NESEmulator nes_;


		NESEmulator_Tests() :
			nes_()
		{
		}

		TEST_METHOD(nestest_rom_gives_proper_output)
		{
			// TODO sk: get rid of hardcoded paths
			std::string correctOutputPath = "C:\\dev\\NES_Emulator\\NES_Core_CPU_Tests\\test_data\\nestes_correct_output.log";
			std::string resultTestPath = "C:\\dev\\NES_Emulator\\build\\bin\\Win32\\NES_Core_CPU_Tests\\NES_CORE.log";
			std::string nestestRom = "C:\\dev\\NES_Emulator\\NES_Core_CPU_Tests\\test_data\\nestest.nes";
			
			try
			{
				nes_.run(nestestRom);
			}
			catch (const std::exception& e)
			{

			}

			std::ifstream f1(correctOutputPath, std::ifstream::binary | std::ifstream::ate);
			std::ifstream f2(resultTestPath, std::ifstream::binary | std::ifstream::ate);

			if (f1.fail() || f2.fail()) {
				throw std::exception("Cannot open test files");
			}

			Assert::AreEqual(long(f1.tellg()), long(f2.tellg()));
			Assert::AreEqual(long(f1.tellg()), long(f2.tellg()));
			f1.seekg(0, std::ifstream::beg);
			f2.seekg(0, std::ifstream::beg);
			Assert::IsTrue(std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
				std::istreambuf_iterator<char>(),
				std::istreambuf_iterator<char>(f2.rdbuf())));
			f1.close();
			f2.close();
		}
	};
}

