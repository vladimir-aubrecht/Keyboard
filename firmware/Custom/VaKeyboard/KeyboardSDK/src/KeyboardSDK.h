#ifndef _KEYBOARDSDK_h
#define _KEYBOARDSDK_h

#include "Drivers/KeyboardDriver.h"
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
	KeyboardDriver* keyboardDriver;
	
	uint16_t** keymap;
	Matrix* previousMatrix = NULL;

public:
	KeyboardSDK(MatrixScanner& matrixScanner, MatrixEvaluator& matrixEvaluator, KeyboardDriver& keyboardDriver, IKeyMapProvider& keymapProvider);
	~KeyboardSDK();
	void scan();
};

#endif