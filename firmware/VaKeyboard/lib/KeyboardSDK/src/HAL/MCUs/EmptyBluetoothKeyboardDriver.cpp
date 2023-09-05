#include "EmptyBluetoothKeyboardDriver.h"

EmptyBluetoothKeyboardDriver::EmptyBluetoothKeyboardDriver()
{
}

void EmptyBluetoothKeyboardDriver::ResetPairing()
{

}

void EmptyBluetoothKeyboardDriver::Init()
{
	
}

bool EmptyBluetoothKeyboardDriver::SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix)
{
	return false;
}

void EmptyBluetoothKeyboardDriver::ResetState()
{

}

EmptyBluetoothKeyboardDriver* EmptyBluetoothKeyboardDriver::Create(IBatteryDriver* batteryDriver, BaseKeyboardDescriptor *keyboardDescriptor, ILogger *logger)
{
    return NULL;
}

EmptyBluetoothKeyboardDriver* EmptyBluetoothKeyboardDriver::GetInstance()
{
	return NULL;
}