#include "Convertors.h"

char *Convertors::toString(Matrix *matrix)
{
	uint8_t stringRowLength = matrix->numberOfColumns + 1;
	uint8_t stringLength = matrix->numberOfRows * stringRowLength + 1;
	char *matrixString = new char[stringLength];

	for (uint8_t rowIndex = 0; rowIndex < matrix->numberOfRows; rowIndex++)
	{
		uint32_t row = matrix->matrixData[rowIndex];

		for (uint8_t columnIndex = 0; columnIndex < matrix->numberOfColumns; columnIndex++)
		{
			char bit = ((row >> columnIndex) & 1) == 1 ? '1' : '0';
			matrixString[rowIndex * stringRowLength + columnIndex] = bit;
		}

		matrixString[rowIndex * stringRowLength + matrix->numberOfColumns] = '\n';
	}

	matrixString[stringLength - 1] = '\0';

	return matrixString;
}
