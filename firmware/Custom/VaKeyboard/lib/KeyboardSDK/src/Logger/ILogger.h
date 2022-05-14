#pragma once
class ILogger
{
public:
	virtual void logDebug(const char *message) = 0;
	virtual void logWarning(const char *message) = 0;
	virtual void logError(const char *message) = 0;

	virtual bool isEnabled() = 0;
};
