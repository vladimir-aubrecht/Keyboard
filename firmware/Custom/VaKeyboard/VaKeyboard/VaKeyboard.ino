#include "Convertors.h"
#include "MatrixScanner.h"
#include "Convertors.h"
#include "Drivers/DisplayDriver.h"
#include "Drivers/PinDriver.h"
#include <Keyboard.h>
#include "Layout.h"

PinDriver pinDriver = PinDriver();
DisplayDriver displayDriver = DisplayDriver();
MatrixScanner matrixScanner = MatrixScanner(pinDriver, 6, 16);
Layout layout = Layout();

uint16_t** keymap = NULL;

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
	Matrix* matrix = matrixScanner.scanMatrix();
	char* matrixString = Convertors::toString(matrix);
	
	displayDriver.setText(matrixString);
	Serial.println(matrixString);
	
	for (uint8_t row = 0; row < matrix->numberOfRows; row++)
	{
		for (uint8_t column = 0; column < matrix->numberOfColumns; column++)
		{
			uint16_t currentKey = keymap[row][column];

			bool isSet = (matrix->matrixData[row] >> column) & 1 == 1;

			if (isSet)
			{
				Keyboard.press(currentKey);
			}
			else
			{
				Keyboard.release(currentKey);
			}
		}
	}

	delete matrixString;
	delete matrix;
}
