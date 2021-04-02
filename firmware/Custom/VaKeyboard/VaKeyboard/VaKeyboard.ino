#include "KeyboardSDK.h"
#include "Drivers/DisplayDriver.h"
#include "Drivers/PinDriver.h"
#include "Layout.h"

const uint8_t numberOfRows = 6;
const uint8_t numberOfColumns = 17;

PinDriver pinDriver = PinDriver();
KeyboardDriver keyboardDriver = KeyboardDriver();
DisplayDriver displayDriver = DisplayDriver();
MatrixScanner matrixScanner = MatrixScanner(pinDriver, numberOfRows, numberOfColumns);
MatrixEvaluator matrixEvaluator = MatrixEvaluator();
Layout layout = Layout(numberOfRows, numberOfColumns);

uint16_t** keymap = NULL;
Matrix* previousMatrix = NULL;

void setup()
{
	Serial.begin(9600);

	displayDriver.initialise();
	pinDriver.initialise();

	Keyboard.begin();

	keymap = layout.getKeymaps();

	Serial.println("\nSetup is done!");
}

void loop()
{
	Matrix* matrix = matrixScanner.scanKeyPressMatrix();
	
	//char* matrixString = Convertors::toString(matrix);
	//Serial.println(matrixString);

	if (previousMatrix != NULL)
	{
		Matrix* pressedKeysMatrix = matrixEvaluator.getPressedKeysMatrix(previousMatrix, matrix);
		Matrix* releasedKeysMatrix = matrixEvaluator.getReleasedKeysMatrix(previousMatrix, matrix);

		keyboardDriver.SendKeys(pressedKeysMatrix, releasedKeysMatrix, keymap);

		delete pressedKeysMatrix;
		delete releasedKeysMatrix;
	}

	//delete[] matrixString;

	delete previousMatrix;
	previousMatrix = matrix;
}