#include "Max7301.h"

#define ENABLE_FAST_WRITE 1

Max7301::Max7301(uint8_t csPin, uint8_t mosiPin, uint8_t sclkPin, uint8_t misoPin)
{
    this->sclkPin = sclkPin;
    this->mosiPin = mosiPin;
    this->csPin = csPin;
    this->misoPin = misoPin;
}

void Max7301::begin()
{
    pinMode(this->mosiPin, OUTPUT);
    pinMode(this->sclkPin, OUTPUT);
    pinMode(this->misoPin, INPUT_PULLUP);

    pinMode(this->csPin, OUTPUT);
    digitalWrite(this->csPin, HIGH);
    digitalWrite(this->sclkPin, LOW);

    delay(10);
}

byte Max7301::transferByte(byte data_out)
{
    byte current_bit, result;
    result = 0;

    for(current_bit = 0; current_bit < 8; current_bit++)
    {
        #if defined(FEATHER32U4) && defined(ENABLE_FAST_WRITE)
        PORTB &= B11011111;
        #else
        digitalWrite(this->sclkPin, LOW);
        #endif

        //uint8_t readBit = (PINC >> PC7) & 1;
        result = (result << 1) | digitalRead(this->misoPin);

        #if defined(FEATHER32U4) && defined(ENABLE_FAST_WRITE)
        PORTB &= B10111111;
        PORTB |= (data_out & 0x80) >> 1; // D10 is bit 6 MOSI, D9 is bit 5 CLK, D11 is bit 7 CS. Significantly faster version of: digitalWrite(this->mosiPin, data_out & 0x80);
        #else
        digitalWrite(this->mosiPin, data_out & 0x80);
        #endif

        data_out <<= 1;
        
        #if defined(FEATHER32U4) && defined(ENABLE_FAST_WRITE)
        PORTB |= B00100000;
        #else
        digitalWrite(this->sclkPin, HIGH);
        #endif
    }

    return result;
}

uint8_t Max7301::transferWord(uint8_t cmdByte, uint8_t dataByte)
{
    #if defined(FEATHER32U4) && defined(ENABLE_FAST_WRITE)
    PORTB &= B01111111;
    #else
    digitalWrite(this->csPin, LOW);
    #endif
    
    transferByte(cmdByte);
    uint8_t data = transferByte(dataByte);
    
    #if defined(FEATHER32U4) && defined(ENABLE_FAST_WRITE)
    PORTB |= B10000000; 
    PORTB &= B11011111;
    #else
    digitalWrite(this->csPin, HIGH);
    digitalWrite(this->sclkPin, LOW);
    #endif

    return data;
}

uint8_t Max7301::read(uint8_t address)
{
    uint8_t data = 0;
    address |= 0x80;
    transferWord(address, 0x00);
    data = transferWord(0x00, 0x00);
    return data;
}

void Max7301::write(uint8_t address, uint8_t value)
{
    address &= ~0x80;
    transferWord(address, value);
}

void Max7301::enable()
{
    delay(500);
    this->write(0x04, 1);
}