#include "KeyboardSDK.h"

KeyboardSDK::KeyboardSDK(MatrixScanner *matrixScanner, MatrixEvaluator *matrixEvaluator, IKeyboardDriver *keyboardDriver, IKeyMapProvider *keymapProvider, ActionEvaluator *actionEvaluator, ILogger *logger)
{
	this->matrixScanner = matrixScanner;
	this->matrixEvaluator = matrixEvaluator;
	this->actionEvaluator = actionEvaluator;
	this->keyboardDriver = keyboardDriver;
	//this->logger = logger ?: new NullLogger();

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
	// unsigned long startTime = millis();

	Matrix *matrix = this->matrixScanner->scanKeyPressMatrix();

	// unsigned long scanTime = millis();
	// unsigned long diffTime = millis();
	// unsigned long sendKeyTime = millis();

	if (this->previousMatrix != NULL)
	{
		Matrix *pressedKeysMatrix = this->matrixEvaluator->getPressedKeysMatrix(this->previousMatrix, matrix);
		Matrix *releasedKeysMatrix = this->matrixEvaluator->getReleasedKeysMatrix(this->previousMatrix, matrix);

		// diffTime = millis();

		if (!this->actionEvaluator->evaluateMatrixActions(matrix) && !this->actionEvaluator->evaluateTimerAction())
		{
			if (this->keyboardDriver->SendKeys(pressedKeysMatrix, releasedKeysMatrix, keymap))
			{
				this->actionEvaluator->updateTimerActionsTime();
			}
		}

		// sendKeyTime = millis();

		delete pressedKeysMatrix;
		delete releasedKeysMatrix;
		delete this->previousMatrix;
	}

	this->previousMatrix = matrix;

	// if (this->logger->isEnabled())
	// {
	// 	unsigned long endTime = millis();
	// 	unsigned long scanElapsedTime = scanTime - startTime;
	// 	unsigned long diffElapsedTime = diffTime - scanTime;
	// 	unsigned long sendKeyElapsedTime = sendKeyTime - diffTime;
	// 	unsigned long totalElapsedTime = endTime - startTime;

	// 	this->logger->logDebug((String("Scan duration: ") + String(scanElapsedTime)).c_str());
	// 	this->logger->logDebug((String("Diff duration: ") + String(diffElapsedTime)).c_str());
	// 	this->logger->logDebug((String("Send duration: ") + String(sendKeyElapsedTime)).c_str());
	// 	this->logger->logDebug((String("Total duration: ") + String(totalElapsedTime)).c_str());
	// }
}
