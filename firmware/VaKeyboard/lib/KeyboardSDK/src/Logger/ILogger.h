#pragma once

#include <Arduino.h>

class ILogger
{
public:
	virtual void logDebug(const char *message) = 0;
	virtual void logWarning(const char *message) = 0;
	virtual void logError(const char *message) = 0;

	virtual void logDebug(const __FlashStringHelper *message) = 0;
	virtual void logWarning(const __FlashStringHelper *message) = 0;
	virtual void logError(const __FlashStringHelper *message) = 0;

	void logDebug(uint8_t argument)
	{
		char buffer[3];
		sprintf(buffer, "%x", argument);

		logDebug(buffer);
	}

	void logWarning(uint8_t argument)
	{
		char buffer[3];
		sprintf(buffer, "%x", argument);

		logWarning(buffer);
	}

	void logError(uint8_t argument)
	{
		char buffer[3];
		sprintf(buffer, "%x", argument);

		logError(buffer);
	}

	virtual bool isEnabled() = 0;
};
