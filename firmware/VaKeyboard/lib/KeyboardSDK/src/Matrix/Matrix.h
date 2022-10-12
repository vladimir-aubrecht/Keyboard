#pragma once
#include <arduino.h>

struct Matrix
{
public:
	uint32_t *matrixData;
	uint8_t numberOfRows;
	uint8_t numberOfColumns;

	Matrix(uint8_t numberOfRows, uint8_t numberOfColumns)
	{
		this->matrixData = new uint32_t[numberOfRows];

		for (uint8_t row = 0; row < numberOfRows; row++)
		{
			this->matrixData[row] = 0;
		}

		this->numberOfRows = numberOfRows;
		this->numberOfColumns = numberOfColumns;
	}

	Matrix(uint32_t *matrixData, uint8_t numberOfRows, uint8_t numberOfColumns)
	{
		this->matrixData = matrixData;
		this->numberOfRows = numberOfRows;
		this->numberOfColumns = numberOfColumns;
	}

	~Matrix()
	{
		delete[] matrixData;
	}

	uint8_t getBit(uint8_t row, uint8_t column)
	{
		return (this->matrixData[row] >> column) & 1;
	}
};
