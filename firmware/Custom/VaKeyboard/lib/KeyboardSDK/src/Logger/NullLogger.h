#pragma once

#include "ILogger.h"

class NullLogger : public ILogger
{
public:
	virtual void logDebug(const char *message);
	virtual void logWarning(const char *message);
	virtual void logError(const char *message);
	virtual bool isEnabled();

	NullLogger();
};
