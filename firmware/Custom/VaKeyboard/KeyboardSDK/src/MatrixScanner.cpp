#include "MatrixScanner.h"


MatrixScanner::MatrixScanner(IPinDriver& pinDriver, uint8_t numberOfRows, uint8_t numberOfColumns)
{
	this->pinDriver = &pinDriver;
	this->numberOfRows = numberOfRows;
	this->numberOfColumns = numberOfColumns;
}

Matrix* MatrixScanner::scanMatrix()
{
	uint16_t* matrixData = new uint16_t[this->numberOfRows];
	Matrix* matrix = new Matrix(matrixData, this->numberOfRows, this->numberOfColumns);

	for (uint8_t row = 0; row < this->numberOfRows; row++)
	{
		matrixData[row] = 0;

		this->pinDriver->writePin(row, LOW);
	
		for (uint8_t column = 0; column < this->numberOfColumns; column++)
		{
			uint8_t pin = this->pinDriver->readPin(column);
			
			matrixData[row] |= (pin << column);
		}

		this->pinDriver->writePin(row, HIGH);
	}

	return matrix;
}