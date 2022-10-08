#ifdef WROOM32
#include "BluetoothKeyboardDriver.h"
#include "BleKeyboard.h"
BluetoothKeyboardDriver::BluetoothKeyboardDriver(
	IBatteryDriver *batteryDriver,
	IKeyboardDescriptor *keyboardDescriptor,
	ILogger *logger)
{
	this->keyboardDescriptor = keyboardDescriptor;
	//this->logger = logger;
	this->batteryDriver = batteryDriver;
	Init();
}
void BluetoothKeyboardDriver::ResetPairing()
{
	Init();
}
void BluetoothKeyboardDriver::Init()
{
	bleKeyboard->begin();
}
bool BluetoothKeyboardDriver::SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix)
{
	bool isPress = false;
	if (this->bleKeyboard->isConnected())
	{
		this->currentStateMatrix = this->UpdateStateMatrix(this->currentStateMatrix, pressedKeysMatrix, releasedKeysMatrix);

		uint8_t layout = this->keyboardDescriptor->getSelectedLayer(currentStateMatrix);
		auto keymap = this->keyboardDescriptor->getKeyMap()[layout];

		for (uint8_t row = 0; row < pressedKeysMatrix->numberOfRows; row++)
		{
			for (uint8_t column = 0; column < pressedKeysMatrix->numberOfColumns; column++)
			{
				uint8_t isPressed = pressedKeysMatrix->getBit(row, column);
				uint8_t isReleased = releasedKeysMatrix->getBit(row, column);
				uint8_t recognizedKey = (uint8_t)keymap[row][column];
				if (isPressed)
				{
					isPress = true;
					bleKeyboard->write(recognizedKey);	// performing also immediate release, temporal hack.
				}
			}
		}
		return isPress;
	}
	else
	{
		// this->logger->logWarning(F("Keyboard not connected :("));
		return false;
	}
}
Matrix *BluetoothKeyboardDriver::UpdateStateMatrix(Matrix *stateMatrix, Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix)
{
	if (stateMatrix == NULL)
	{
		stateMatrix = new Matrix(pressedKeysMatrix->numberOfRows, pressedKeysMatrix->numberOfColumns);
	}
	for (uint8_t row = 0; row < stateMatrix->numberOfRows; row++)
	{
		for (uint8_t column = 0; column < stateMatrix->numberOfColumns; column++)
		{
			uint8_t isPressed = pressedKeysMatrix->getBit(row, column);
			uint8_t isReleased = releasedKeysMatrix->getBit(row, column);
			if (isPressed)
			{
				stateMatrix->matrixData[row] |= (((uint32_t)1) << column);
			}
			else if (isReleased)
			{
				stateMatrix->matrixData[row] &= ~(((uint32_t)1) << column);
			}
		}
	}
	return stateMatrix;
}
void BluetoothKeyboardDriver::ResetState()
{
	this->currentStateMatrix = NULL;
}
#endif