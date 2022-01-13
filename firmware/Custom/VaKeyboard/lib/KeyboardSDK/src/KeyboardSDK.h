#pragma once

#include "Drivers/IKeyboardDriver.h"
#include "Matrix/MatrixEvaluator.h"
#include "Matrix/Convertors.h"
#include "Matrix/MatrixScanner.h"
#include "Matrix/MatrixEvaluator.h"
#include "IKeyMapProvider.h"

class KeyboardSDK
{
private:
	MatrixScanner* matrixScanner;
	MatrixEvaluator* matrixEvaluator;
	IKeyboardDriver* keyboardDriver;
	
	uint16_t** keymap;
	Matrix* previousMatrix = NULL;

public:
	KeyboardSDK(MatrixScanner* matrixScanner, MatrixEvaluator* matrixEvaluator, IKeyboardDriver* keyboardDriver, IKeyMapProvider* keymapProvider);
	~KeyboardSDK();
	void scan();
};