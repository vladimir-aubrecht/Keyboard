#include "Logger.h"

void Logger::logDebug(char* message)
{
	Serial.println(message);
}

void Logger::logWarning(char* message)
{
	Serial.println(message);
}

void Logger::logError(char* message)
{
	Serial.println(message);
}