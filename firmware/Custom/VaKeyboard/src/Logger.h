#pragma once

#include <Arduino.h>
#include "Logger/ILogger.h"

class Logger : public ILogger
{
public:
	virtual void logDebug(const char *message);
	virtual void logWarning(const char *message);
	virtual void logError(const char *message);
	virtual bool isEnabled();
};
