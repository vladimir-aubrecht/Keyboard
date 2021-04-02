#ifndef _MATRIXEVALUATOR_h
#define _MATRIXEVALUATOR_h

#include <arduino.h>
#include "Matrix.h"

class MatrixEvaluator
{
private:
	Matrix* getStateChangeMatrix(Matrix* oldMatrix, Matrix* newMatrix, uint8_t expectedState);

public:
	MatrixEvaluator();

	Matrix* getPressedKeysMatrix(Matrix* oldMatrix, Matrix* newMatrix);
	Matrix* getReleasedKeysMatrix(Matrix* oldMatrix, Matrix* newMatrix);
};
#endif