#pragma once

#include <iostream>
#include <string>

enum class LogType {
	LOG_WARRING = 0,
	LOG_ERROR,
	LOG_MESSAGE,
	LOG_MAX
};

static const char* LogTypeName[4] = {
	"LOG_WARRING",
	"LOG_ERROR",
	"LOG_MESSAGE",

	"LOG_MAX"
};

void PrintLog(LogType&& type, const std::string&& message);

#define LOG(type,message) \
PrintLog( type , message )