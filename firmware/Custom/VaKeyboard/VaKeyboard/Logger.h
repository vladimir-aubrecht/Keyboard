#pragma once

#include <Arduino.h>
#include <Adafruit_MCP23X17.h>
#include "ILogger.h"

class Logger : public ILogger
{
public:
	virtual void logDebug(char* message);
	virtual void logWarning(char* message);
	virtual void logError(char* message);
};
