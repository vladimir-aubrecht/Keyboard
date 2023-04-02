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

class KeyPressProcessor
{
private:
	MatrixScanner *matrixScanner;
	MatrixEvaluator *matrixEvaluator;
	ActionEvaluator *actionEvaluator;
	IKeyboardDriver *keyboardDriver;
	IKeyboardDescriptor *keyboardDescriptor;
	//ILogger *logger;

	Matrix *previousMatrix = NULL;

public:
	KeyPressProcessor(MatrixScanner *matrixScanner, MatrixEvaluator *matrixEvaluator, IKeyboardDriver *keyboardDriver, IKeyboardDescriptor *keyboardDescriptor, ActionEvaluator *actionEvaluator, ILogger *logger);
	void scan();
};