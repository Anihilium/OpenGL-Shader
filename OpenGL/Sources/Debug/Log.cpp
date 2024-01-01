#include <Debug/Log.hpp>

namespace Core::Debug
{
	static std::ofstream mDebugLogFile;

	Log::~Log()
	{
		mDebugLogFile.close();
	}

	void Log::OpenFile(const char* filename)
	{
		mDebugLogFile.open(filename);
	}

	std::string Log::Print(const char* format, ...)
	{
		std::string fileContent;

		va_list arguments;
		va_start(arguments, format);

		int i = 0;
		while (format[i] != '\0')
		{
			if (format[i] == '\\')
			{
				++i;
				fileContent += format[i];
			}
			else if (format[i] == '%')
			{
				++i;
				switch (format[i])
				{
				case 'd':
					fileContent += std::to_string(va_arg(arguments, int));
					break;
				case 'f':
					fileContent += std::to_string(va_arg(arguments, double));
					break;
				case 's':
					fileContent += va_arg(arguments, const char*);
					break;
				case 'c':
					fileContent += va_arg(arguments, char);
					break;
				default:
					break;
				}
			}
			else
			{
				fileContent += format[i];
			}
			++i;
		}

		va_end(arguments);

		if (mDebugLogFile)
			mDebugLogFile << fileContent;

		std::cout << fileContent;

		return fileContent;
	}
}