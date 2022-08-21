#include "Max7301.h"

Max7301::Max7301(uint8_t csPin)
{
    this->csPin = csPin;
    this->spiSettings = SPISettings(16000000, MSBFIRST, SPI_MODE2);
}

void Max7301::begin()
{
    pinMode(SCK, OUTPUT);
    pinMode(MOSI, OUTPUT);
    pinMode(MISO, INPUT_PULLUP);

    //SPI.begin();

    pinMode(this->csPin, OUTPUT);
    digitalWrite(this->csPin, HIGH);
    delay(100);
}

byte transferByte(byte data_out)
{
    byte current_bit, result;
    result = 0;
    
    for(current_bit = 0; current_bit < 8; current_bit++)
    {
        digitalWrite(SCK, LOW);
     
        result = (result << 1) | digitalRead(MISO);

        delayMicroseconds(52);

        digitalWrite(SCK, HIGH);
        digitalWrite(MOSI, data_out & 0x80);
        data_out <<= 1;
 
        delayMicroseconds(52);
    }

    return result;
}

uint8_t Max7301::transferWord(uint8_t higherByte, uint8_t lowerByte)
{
    transferByte(higherByte);
    uint8_t data = transferByte(lowerByte);

    digitalWrite(SCK, LOW);
    delayMicroseconds(2);
    digitalWrite(SCK, HIGH);

    return data;

/*
    // max7301 is using different edges for write/read, and SPI class is half of clock off.
    SPI.beginTransaction(this->spiSettings);
    uint16_t word = (higherByte << 8) | lowerByte;
    uint16_t data = SPI.transfer16(word);
    SPI.endTransaction();

    return data & 0xff;
    */
}

uint8_t Max7301::read(uint8_t address)
{
    uint8_t data = 0;

    address |= 0x80;

    digitalWrite(this->csPin, LOW);
    transferWord(address, 0x00);
    digitalWrite(this->csPin, HIGH);

    digitalWrite(this->csPin, LOW);
    data = transferWord(0x00, 0x00);
    digitalWrite(this->csPin, HIGH);

    return data;
}

void Max7301::write(uint8_t address, uint8_t value)
{
    address &= ~0x80;

    digitalWrite(this->csPin, LOW);
    transferWord(address, value);
    digitalWrite(this->csPin, HIGH);
}

void Max7301::enable()
{
    delay(2000);
    this->write(0x04, 1);
}