#include "EmptyBluetoothKeyboardDriver.h"

BluetoothKeyboardDriver::BluetoothKeyboardDriver(
	IBatteryDriver *batteryDriver,
	BaseKeyboardDescriptor *keyboardDescriptor,
	ILogger *logger)
{
}

void BluetoothKeyboardDriver::ResetPairing()
{

}

void BluetoothKeyboardDriver::Init()
{
	
}

bool BluetoothKeyboardDriver::SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix)
{
	return false;
}

void BluetoothKeyboardDriver::ResetState()
{

}

BluetoothKeyboardDriver* BluetoothKeyboardDriver::Create(IBatteryDriver* batteryDriver, BaseKeyboardDescriptor *keyboardDescriptor, ILogger *logger)
{
    return NULL;
}

BluetoothKeyboardDriver* BluetoothKeyboardDriver::GetInstance()
{
	return NULL;
}