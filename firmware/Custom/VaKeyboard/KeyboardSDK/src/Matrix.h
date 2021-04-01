#ifndef _MATRIX_h
#define _MATRIX_h

#include "arduino.h"

struct Matrix
{
public:
	uint16_t* matrixData;
	uint8_t numberOfRows;
	uint8_t numberOfColumns;

	Matrix(uint16_t* matrixData, uint8_t numberOfRows, uint8_t numberOfColumns)
	{
		this->matrixData = matrixData;
		this->numberOfRows = numberOfRows;
		this->numberOfColumns = numberOfColumns;
	}

	~Matrix()
	{
		delete matrixData;
	}
};

#endif