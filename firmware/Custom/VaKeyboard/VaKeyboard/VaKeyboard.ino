#include "Convertors.h"
#include "MatrixScanner.h"
#include "DisplayDriver.h"
#include "PinDriver.h"
#include "Convertors.h"
#include <Keyboard.h>

PinDriver pinDriver = PinDriver();
DisplayDriver displayDriver = DisplayDriver();
MatrixScanner matrixScanner = MatrixScanner(pinDriver, 6, 16);

void setup()
{
	Serial.begin(9600);

	displayDriver.initialise();
	pinDriver.initialise();

	Serial.println("\nSetup is done!");
}

void loop()
{
	Matrix* matrix = matrixScanner.scanMatrix();
	char* matrixString = Convertors::toString(matrix);
	
	displayDriver.setText(matrixString);
	Serial.println(matrixString);
	
	delete matrixString;
	delete matrix;
}
