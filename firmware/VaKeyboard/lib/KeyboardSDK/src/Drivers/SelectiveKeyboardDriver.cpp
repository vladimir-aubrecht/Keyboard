#include "SelectiveKeyboardDriver.h"

SelectiveKeyboardDriver::SelectiveKeyboardDriver(IKeyboardDriver *keyboard1, IKeyboardDriver *keyboard2)
{
    this->keyboard1 = keyboard1;
    this->keyboard2 = keyboard2;
    this->currentKeyboard = this->keyboard1;
}

void SelectiveKeyboardDriver::ResetPairing()
{
    this->currentKeyboard->ResetPairing();
}
bool SelectiveKeyboardDriver::SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix)
{
    return this->currentKeyboard->SendKeys(pressedKeysMatrix, releasedKeysMatrix);
}

IKeyboardDriver *SelectiveKeyboardDriver::SwapKeyboards()
{
    if (this->currentKeyboard == this->keyboard1)
    {
        this->currentKeyboard = this->keyboard2;
    }
    else
    {
        this->currentKeyboard = this->keyboard1;
    }

    this->ResetState();

    return this->currentKeyboard;
}

void SelectiveKeyboardDriver::ResetState()
{
    this->currentKeyboard->ResetState();
}