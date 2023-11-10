#include "Logger.h"

inline void Logger::logDebug(const char *message)
{
	Serial.println(message);
}

inline void Logger::logWarning(const char *message)
{
	Serial.println(message);
}

inline void Logger::logError(const char *message)
{
	Serial.println(message);
}

inline void Logger::logDebug(const __FlashStringHelper *message)
{
	Serial.println(message);
}
inline void Logger::logWarning(const __FlashStringHelper *message)
{
	Serial.println(message);
}
inline void Logger::logError(const __FlashStringHelper *message)
{
	Serial.println(message);
}

inline bool Logger::isEnabled()
{
	return true;
}