#pragma once

#include "Drivers/IKeyboardDriver.h"
#include "Matrix/MatrixEvaluator.h"
#include "Matrix/Convertors.h"
#include "Matrix/MatrixScanner.h"
#include "Matrix/MatrixEvaluator.h"
#include "IKeyMapProvider.h"
#include "Logger/ILogger.h"
#include "Logger/NullLogger.h"

class KeyboardSDK
{
private:
	MatrixScanner *matrixScanner;
	MatrixEvaluator *matrixEvaluator;
	IKeyboardDriver *keyboardDriver;
	ILogger *logger;

	KeyboardKeycode **keymap;
	Matrix *previousMatrix = NULL;

public:
	KeyboardSDK(MatrixScanner *matrixScanner, MatrixEvaluator *matrixEvaluator, IKeyboardDriver *keyboardDriver, IKeyMapProvider *keymapProvider, ILogger *logger);
	~KeyboardSDK();
	void scan();
};