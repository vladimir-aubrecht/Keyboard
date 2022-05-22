#pragma once

#include "../Drivers/IPinDriver.h"
#include "Matrix.h"
#include "Logger/ILogger.h"
#include "Logger/NullLogger.h"

class MatrixScanner
{
private:
	ILogger *logger;
	IPinDriver *pinDriver;
	uint8_t numberOfRows;
	uint8_t numberOfColumns;

public:
	MatrixScanner(IPinDriver *pinDriver, uint8_t numberOfRows, uint8_t numberOfColumns, ILogger *logger);
	Matrix *scanKeyPressMatrix();
};