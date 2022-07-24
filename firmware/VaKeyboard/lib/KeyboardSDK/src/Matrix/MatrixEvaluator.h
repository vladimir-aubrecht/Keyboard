#pragma once

#include <arduino.h>
#include "Matrix.h"
#include "MatrixDebouncer.h"

class MatrixEvaluator
{
private:
	MatrixDebouncer* matrixDebouncer = NULL;
	Matrix* getStateChangeMatrix(Matrix* oldMatrix, Matrix* newMatrix, uint8_t expectedState);

public:
	MatrixEvaluator(MatrixDebouncer* matrixDebouncer);

	Matrix* getPressedKeysMatrix(Matrix* oldMatrix, Matrix* newMatrix);
	Matrix* getReleasedKeysMatrix(Matrix* oldMatrix, Matrix* newMatrix);
};
