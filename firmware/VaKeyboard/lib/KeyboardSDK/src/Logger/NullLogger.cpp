#include "NullLogger.h"

NullLogger::NullLogger()
{
}

void NullLogger::logDebug(const char *message)
{
}

void NullLogger::logWarning(const char *message)
{
}

void NullLogger::logError(const char *message)
{
}

void NullLogger::logDebug(const __FlashStringHelper *message)
{
}
void NullLogger::logWarning(const __FlashStringHelper *message)
{
}
void NullLogger::logError(const __FlashStringHelper *message)
{
}

bool NullLogger::isEnabled()
{
    return false;
}