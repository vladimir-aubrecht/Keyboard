#include "Logger.h"

void Logger::logDebug(const char *message)
{
	Serial.println(message);
}

void Logger::logWarning(const char *message)
{
	Serial.println(message);
}

void Logger::logError(const char *message)
{
	Serial.println(message);
}

bool Logger::isEnabled()
{
	return true;
}