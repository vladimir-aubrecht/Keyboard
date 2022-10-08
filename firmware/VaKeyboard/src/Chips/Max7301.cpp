#include "Max7301.h"

Max7301::Max7301(uint8_t csPin)
{
    this->csPin = csPin;
}

void Max7301::begin()
{
    pinMode(SCK, OUTPUT);
    pinMode(MOSI, OUTPUT);
    pinMode(MISO, INPUT_PULLUP);

    pinMode(this->csPin, OUTPUT);
    digitalWrite(this->csPin, HIGH);
    digitalWrite(SCK, LOW);

    delay(100);
}

byte transferByte(byte data_out)
{
    byte current_bit, result;
    result = 0;
    delayMicroseconds(1);
    for(current_bit = 0; current_bit < 8; current_bit++)
    {
        digitalWrite(SCK, LOW);
        result = (result << 1) | digitalRead(MISO);
        digitalWrite(MOSI, data_out & 1);
        data_out >>= 1;
        digitalWrite(SCK, HIGH);
        delayMicroseconds(1);
    }
    return result;
}
unsigned char reverse(unsigned char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}
uint8_t Max7301::transferWord(uint8_t cmdByte, uint8_t dataByte)
{
    digitalWrite(SCK, LOW);
    digitalWrite(this->csPin, LOW);
    
    transferByte(reverse(cmdByte));
    uint8_t data = transferByte(reverse(dataByte));
    
    digitalWrite(this->csPin, HIGH);
    digitalWrite(SCK, LOW);

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
    delay(2000);
    this->write(0x04, 1);
}