#pragma once

#include "Drivers/IKeyboardDriver.h"
#include "Matrix/MatrixEvaluator.h"
#include "Matrix/Convertors.h"
#include "Matrix/MatrixScanner.h"
#include "Matrix/MatrixEvaluator.h"
#include "IKeyboardDescriptor.h"
#include "Logger/ILogger.h"
#include "Logger/NullLogger.h"
#include "ActionEvaluator.h"

class KeyboardSDK
{
private:
	MatrixScanner *matrixScanner;
	MatrixEvaluator *matrixEvaluator;
	ActionEvaluator *actionEvaluator;
	IKeyboardDriver *keyboardDriver;
	//ILogger *logger;

	KeyboardKeycode **keymap;
	Matrix *previousMatrix = NULL;

public:
	KeyboardSDK(MatrixScanner *matrixScanner, MatrixEvaluator *matrixEvaluator, IKeyboardDriver *keyboardDriver, IKeyboardDescriptor *keyboardDescriptor, ActionEvaluator *actionEvaluator, ILogger *logger);
	~KeyboardSDK();
	void scan();
};