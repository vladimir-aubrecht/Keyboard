#include "KeyboardSDK.h"

KeyboardSDK::KeyboardSDK(MatrixScanner *matrixScanner, MatrixEvaluator *matrixEvaluator, IKeyboardDriver *keyboardDriver, IKeyMapProvider *keymapProvider)
{
	this->matrixScanner = matrixScanner;
	this->matrixEvaluator = matrixEvaluator;
	this->keyboardDriver = keyboardDriver;

	this->keymap = keymapProvider->getKeyMap();
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
	unsigned long startTime = millis();

	Matrix *matrix = this->matrixScanner->scanKeyPressMatrix();

	unsigned long scanTime = millis();
	unsigned long diffTime = millis();
	unsigned long sendKeyTime = millis();

	if (this->previousMatrix != NULL)
	{
		Matrix *pressedKeysMatrix = this->matrixEvaluator->getPressedKeysMatrix(this->previousMatrix, matrix);
		Matrix *releasedKeysMatrix = this->matrixEvaluator->getReleasedKeysMatrix(this->previousMatrix, matrix);

		diffTime = millis();

		this->keyboardDriver->SendKeys(matrix, pressedKeysMatrix, releasedKeysMatrix, keymap);

		sendKeyTime = millis();

		delete pressedKeysMatrix;
		delete releasedKeysMatrix;
		delete this->previousMatrix;
	}

	this->previousMatrix = matrix;

	unsigned long endTime = millis();
	unsigned long scanElapsedTime = scanTime - startTime;
	unsigned long diffElapsedTime = diffTime - scanTime;
	unsigned long sendKeyElapsedTime = sendKeyTime - diffTime;
	unsigned long totalElapsedTime = endTime - startTime;

	/*Serial.print("Scan duration: ");
	Serial.println(scanElapsedTime);

	Serial.print("Diff duration: ");
	Serial.println(diffElapsedTime);

	Serial.print("Send duration: ");
	Serial.println(sendKeyElapsedTime);

	Serial.print("Total duration: ");
	Serial.println(totalElapsedTime);*/
}
