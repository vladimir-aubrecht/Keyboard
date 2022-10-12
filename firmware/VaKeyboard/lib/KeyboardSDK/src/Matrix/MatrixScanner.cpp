#include "MatrixScanner.h"
#include "Convertors.h"

MatrixScanner::MatrixScanner(IPinDriver *pinDriver, uint8_t rowCount, uint8_t columnCount, ILogger *logger)
{
	//this->logger = logger;
	this->pinDriver = pinDriver;
	this->rowCount = rowCount;
	this->columnCount = columnCount;

}

Matrix *MatrixScanner::scanKeyPressMatrix()
{
	Matrix *matrix = new Matrix(rowCount, columnCount);
	uint32_t *matrixData = matrix->matrixData;

	for (uint8_t row = 0; row < rowCount; row++)
	{
		matrixData[row] = 0;

		this->pinDriver->writePin(row, LOW);
		this->pinDriver->refreshCache();

		for (uint8_t column = 0; column < columnCount; column++)
		{
			uint32_t pin = this->pinDriver->readPin(column);

			matrixData[row] |= (pin << column);
		}

		this->pinDriver->writePin(row, HIGH);
	}

	// if (this->logger->isEnabled())
	//{
	//  char *sm = Convertors::toString(matrix);
	//  this->logger->logDebug(sm);
	//  delete sm;
	//}

	return matrix;
}