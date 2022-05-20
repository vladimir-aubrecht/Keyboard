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

	virtual bool isEnabled() = 0;
};
