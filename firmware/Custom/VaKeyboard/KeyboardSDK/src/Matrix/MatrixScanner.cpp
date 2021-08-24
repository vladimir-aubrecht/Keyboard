#include "MatrixScanner.h"
#include "Convertors.h"

MatrixScanner::MatrixScanner(IPinDriver& pinDriver, uint8_t numberOfRows, uint8_t numberOfColumns)
{
	this->pinDriver = &pinDriver;
	this->numberOfRows = numberOfRows;
	this->numberOfColumns = numberOfColumns;
}

Matrix* MatrixScanner::scanKeyPressMatrix()
{
	uint32_t* matrixData = new uint32_t[this->numberOfRows];
	Matrix* matrix = new Matrix(matrixData, this->numberOfRows, this->numberOfColumns);

	for (uint8_t row = 0; row < this->numberOfRows; row++)
	{
		matrixData[row] = 0;

		this->pinDriver->writePin(row, LOW);
		delay(100);

		for (uint8_t column = 0; column < this->numberOfColumns; column++)
		{
			uint32_t pin = this->pinDriver->readPin(column);
			matrixData[row] |= (pin << column);
		}

		this->pinDriver->writePin(row, HIGH);
		delay(100);
	}

	/*for (uint8_t column = 0; column < this->numberOfColumns && column < 1; column++)
	{
		this->pinDriver->writePin(column, LOW);

		for (uint8_t row = 0; row < this->numberOfRows && row < 1; row++)
		{
			uint32_t pin = this->pinDriver->readPin(row);
			if (pin > 0)
			{
				Serial.print("row: ");
				Serial.print(row);
				Serial.print(" column: ");
				Serial.println(column);
			}
			matrixData[row] &= ~(1UL << column); // reset bit for column
			matrixData[row] |= (pin << column); // write column bit
		}

		this->pinDriver->writePin(column, HIGH);
	}*/

	char* strMatrix = Convertors::toString(matrix);

	Serial.println(strMatrix);

	delete strMatrix;

	return matrix;
}