#pragma once
class ILogger
{
public:
	virtual void logDebug(char* message) = 0;
	virtual void logWarning(char* message) = 0;
	virtual void logError(char* message) = 0;
};

