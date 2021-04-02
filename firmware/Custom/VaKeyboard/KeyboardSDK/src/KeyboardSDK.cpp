#include "KeyboardSDK.h"


KeyboardSDK::KeyboardSDK(MatrixScanner &matrixScanner, MatrixEvaluator &matrixEvaluator, KeyboardDriver &keyboardDriver, IKeyMapProvider &keymapProvider)
{
	this->matrixScanner = &matrixScanner;
	this->matrixEvaluator = &matrixEvaluator;
	this->keyboardDriver = &keyboardDriver;
	
	this->keymap = keymapProvider.getKeyMap();
}

KeyboardSDK::~KeyboardSDK()
{
	for (uint8_t row = 0; row < this->previousMatrix->numberOfRows; row++)
	{
		delete[] keymap[row];
	}

	delete[] keymap;

	delete this->previousMatrix;
}

void KeyboardSDK::scan()
{

	Matrix* matrix = this->matrixScanner->scanKeyPressMatrix();

	if (this->previousMatrix != NULL)
	{
		Matrix* pressedKeysMatrix = this->matrixEvaluator->getPressedKeysMatrix(this->previousMatrix, matrix);
		Matrix* releasedKeysMatrix = this->matrixEvaluator->getReleasedKeysMatrix(this->previousMatrix, matrix);

		this->keyboardDriver->SendKeys(pressedKeysMatrix, releasedKeysMatrix, keymap);

		delete pressedKeysMatrix;
		delete releasedKeysMatrix;
		delete this->previousMatrix;
	}

	this->previousMatrix = matrix;
}

