#pragma once

#include <arduino.h>
#include "../Drivers/IPinDriver.h"
#include "Matrix.h"

class MatrixScanner
{
private:
	IPinDriver* pinDriver;
	uint8_t numberOfRows;
	uint8_t numberOfColumns;

public:
	MatrixScanner(IPinDriver* pinDriver, uint8_t numberOfRows, uint8_t numberOfColumns);
	Matrix* scanKeyPressMatrix();
};
