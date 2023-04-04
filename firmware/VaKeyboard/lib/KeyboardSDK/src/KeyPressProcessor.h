#pragma once

#include "HAL/IKeyboardDriver.h"
#include "Matrix/MatrixEvaluator.h"
#include "Matrix/Convertors.h"
#include "Matrix/MatrixScanner.h"
#include "Matrix/MatrixEvaluator.h"
#include "BaseKeyboardDescriptor.h"
#include "Logger/ILogger.h"
#include "Logger/NullLogger.h"
#include "ActionEvaluator.h"

class KeyPressProcessor
{
private:
	MatrixScanner *matrixScanner;
	MatrixEvaluator *matrixEvaluator;
	ActionEvaluator *actionEvaluator;
	IKeyboardDriver *keyboardDriver;
	BaseKeyboardDescriptor *keyboardDescriptor;
	//ILogger *logger;

	Matrix *previousMatrix = NULL;

public:
	KeyPressProcessor(MatrixScanner *matrixScanner, MatrixEvaluator *matrixEvaluator, IKeyboardDriver *keyboardDriver, BaseKeyboardDescriptor *keyboardDescriptor, ActionEvaluator *actionEvaluator, ILogger *logger);
	void scan();
};