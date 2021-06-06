#include "Log/Log.h"

void PrintLog(LogType&& type, const std::string&& message)
{
	{
		std::cout << LogTypeName[(int32_t)type] << " : " << message << std::endl;
	}
}
