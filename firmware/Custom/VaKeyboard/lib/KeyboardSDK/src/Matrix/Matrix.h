#pragma once
#include <arduino.h>

struct Matrix
{
public:
	uint32_t* matrixData;
	uint8_t numberOfRows;
	uint8_t numberOfColumns;

	Matrix(uint32_t* matrixData, uint8_t numberOfRows, uint8_t numberOfColumns)
	{
		this->matrixData = matrixData;
		this->numberOfRows = numberOfRows;
		this->numberOfColumns = numberOfColumns;
	}

	~Matrix()
	{
		delete[] matrixData;
	}
};

