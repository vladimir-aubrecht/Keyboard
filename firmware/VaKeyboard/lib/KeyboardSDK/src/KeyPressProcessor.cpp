#include "KeyPressProcessor.h"

KeyPressProcessor::KeyPressProcessor(MatrixScanner *matrixScanner, MatrixEvaluator *matrixEvaluator, IKeyboardDriver *keyboardDriver, IKeyboardDescriptor *keyboardDescriptor, ActionEvaluator *actionEvaluator, ILogger *logger)
{
	this->matrixScanner = matrixScanner;
	this->matrixEvaluator = matrixEvaluator;
	this->actionEvaluator = actionEvaluator;
	this->keyboardDriver = keyboardDriver;
	this->keyboardDescriptor = keyboardDescriptor;
	//this->logger = logger;
}

void KeyPressProcessor::scan()
{
	// unsigned long startTime = micros();

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
			if (this->keyboardDriver->SendKeys(pressedKeysMatrix, releasedKeysMatrix))
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
	// 	unsigned long endTime = micros();
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
