#include "MatrixEvaluator.h"


MatrixEvaluator::MatrixEvaluator(MatrixDebouncer* matrixDebouncer)
{
	this->matrixDebouncer = matrixDebouncer;
}

Matrix* MatrixEvaluator::getStateChangeMatrix(Matrix* previousMatrix, Matrix* currentMatrix, uint8_t expectedState)
{
	uint32_t* matrixData = new uint32_t[previousMatrix->numberOfRows];

	for (uint8_t row = 0; row < previousMatrix->numberOfRows; row++)
	{
		matrixData[row] = 0;

		for (uint8_t column = 0; column < previousMatrix->numberOfColumns; column++)
		{
			uint8_t oldBit = previousMatrix->getBit(row, column);
			uint8_t newBit = currentMatrix->getBit(row, column);

			if (oldBit != newBit && newBit == expectedState)
			{
				if (this->matrixDebouncer->isDebounced(row, column))
				{
					//key was newly pressed
					matrixData[row] |= ((uint32_t)1) << column;
				}
			}
		}
	}

	return new Matrix(matrixData, previousMatrix->numberOfRows, previousMatrix->numberOfColumns);
}

Matrix* MatrixEvaluator::getPressedKeysMatrix(Matrix* previousMatrix, Matrix* currentMatrix)
{
	return this->getStateChangeMatrix(previousMatrix, currentMatrix, 1);
}

Matrix* MatrixEvaluator::getReleasedKeysMatrix(Matrix* previousMatrix, Matrix* currentMatrix)
{
	return this->getStateChangeMatrix(previousMatrix, currentMatrix, 0);
}