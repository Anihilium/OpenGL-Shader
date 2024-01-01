#pragma once
#include <iostream>
#include <fstream>
#include <cstdarg>
#include <string>
#include <filesystem>
#include <Windows.h>
#include <debugapi.h>


namespace Core::Debug
{
	class Log
	{
	public:
		~Log();
		void OpenFile(const char* filename);
		static std::string Print(const char* format, ...);
	};
	extern std::ofstream mDebugLogFile;
}
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define DEBUG_LOG(str, ...) {std::string message; message += __FILENAME__; message += "("; message += std::to_string(__LINE__); message += "): "; message += Debug::Log::Print(str, __VA_ARGS__); OutputDebugStringA(message.c_str());}