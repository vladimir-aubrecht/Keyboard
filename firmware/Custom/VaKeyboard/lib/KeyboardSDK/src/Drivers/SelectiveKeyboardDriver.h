#pragma once
#include "IKeyboardDriver.h"

class SelectiveKeyboardDriver : public IKeyboardDriver
{
private:
    IKeyboardDriver *keyboard1;
    IKeyboardDriver *keyboard2;
    IKeyboardDriver *currentKeyboard;

public:
    SelectiveKeyboardDriver(IKeyboardDriver *keyboard1, IKeyboardDriver *keyboard2);

    virtual void ResetPairing();
    virtual void ResetState();
    virtual void SendKeys(Matrix *pressedKeysMatrix, Matrix *releasedKeysMatrix, KeyboardKeycode **keymapProvider);
    virtual void SwapKeyboards();
};