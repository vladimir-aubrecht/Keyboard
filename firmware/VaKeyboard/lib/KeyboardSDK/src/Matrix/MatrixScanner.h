#pragma once

#include "HAL/IPinDriver.h"
#include "Matrix.h"
#include "Logger/ILogger.h"
#include "Logger/NullLogger.h"
#include "IKeyboardDescriptor.h"

class MatrixScanner
{
private:
	//ILogger *logger;
	IPinDriver *pinDriver = NULL;
	uint8_t rowCount = 0;
	uint8_t columnCount = 0;

public:
	MatrixScanner(IPinDriver *pinDriver, uint8_t rowCount, uint8_t columnCount, ILogger *logger);
	Matrix *scanKeyPressMatrix();
};