#pragma once

#include "Logger/ILogger.h"

class Logger : public ILogger
{
public:
	virtual void logDebug(const char *message);
	virtual void logWarning(const char *message);
	virtual void logError(const char *message);

	virtual void logDebug(const __FlashStringHelper *message);
	virtual void logWarning(const __FlashStringHelper *message);
	virtual void logError(const __FlashStringHelper *message);

	virtual bool isEnabled();
};
