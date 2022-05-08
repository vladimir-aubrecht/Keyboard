#include "MatrixScanner.h"
#include "Convertors.h"

MatrixScanner::MatrixScanner(IPinDriver *pinDriver, uint8_t numberOfRows, uint8_t numberOfColumns)
{
	this->pinDriver = pinDriver;
	this->numberOfRows = numberOfRows;
	this->numberOfColumns = numberOfColumns;
}

Matrix *MatrixScanner::scanKeyPressMatrix()
{
	Matrix *matrix = new Matrix(this->numberOfRows, this->numberOfColumns);
	uint32_t *matrixData = matrix->matrixData;

	for (uint8_t row = 0; row < this->numberOfRows; row++)
	{
		matrixData[row] = 0;

		this->pinDriver->writePin(row, LOW);

		this->pinDriver->refreshCache();
		for (uint8_t column = 0; column < this->numberOfColumns; column++)
		{
			uint32_t pin = this->pinDriver->readPin(column);

			matrixData[row] |= (pin << column);
		}

		this->pinDriver->writePin(row, HIGH);
	}

	/*char *sm = Convertors::toString(matrix);
	Serial.println(sm);
	delete sm;*/

	return matrix;
}