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

bool NullLogger::isEnabled()
{
    return false;
}