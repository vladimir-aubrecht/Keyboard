#ifndef _MATRIXSCANNER_h
#define _MATRIXSCANNER_h

#include "arduino.h"
#include "IPinDriver.h"
#include "Matrix.h"

class MatrixScanner
{
private:
	IPinDriver* pinDriver;
	uint8_t numberOfRows;
	uint8_t numberOfColumns;

public:
	MatrixScanner(IPinDriver& pinDriver, uint8_t numberOfRows, uint8_t numberOfColumns);

	Matrix* scanMatrix();
};
#endif

