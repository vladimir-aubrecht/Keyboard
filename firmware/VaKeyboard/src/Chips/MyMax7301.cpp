#include "MyMax7301.h"

MyMax7301::MyMax7301(uint8_t csPin)
{
    this->csPin = csPin;
    this->spiSettings = SPISettings(16000000, MSBFIRST, SPI_MODE0);
}

void MyMax7301::begin()
{
    pinMode(SCK, OUTPUT);
    pinMode(MOSI, OUTPUT);
    pinMode(MISO, INPUT_PULLUP);

    //SPI.begin();
    //SPI.setClockDivider(SPI_CLOCK_DIV4);

    pinMode(this->csPin, OUTPUT);
    digitalWrite(this->csPin, HIGH);
    delay(100);
}

byte transferMax7301Byte(byte data_out)
{
    byte current_bit, result;
    result = 0;
    //must clock each bit
    for(current_bit = 0; current_bit < 8; current_bit++)
    {
        //SCLK falling edge, MAX7301 changes output
        digitalWrite(SCK, LOW);
        //shift data from DOUT pin read into result
        
        result = (result << 1) | digitalRead(MISO);

        //9600 baud is about 104 microseconds per pulse
        //so wait half of that time between edges
        delayMicroseconds(520000);
        digitalWrite(SCK, HIGH);
        //SCLK rising edge, Arduino changes output
        //shift data out of data_out onto DIN pin
        digitalWrite(MOSI, data_out & 0x80);
        data_out <<= 1;
        //wait the other half of the 104 microseconds
 
        delayMicroseconds(520000);
    }
    //last falling edge of SCLK
    digitalWrite(SCK, LOW);
    
    //read last bit from DOUT pin
    result = (result << 1) | digitalRead(MISO);

    return result;
}

uint8_t MyMax7301::readGPIORegister(uint8_t address)
{
    uint8_t data = 0;

    address |= 0x80;
    //SPI.beginTransaction(this->spiSettings);
    digitalWrite(this->csPin, LOW);
    transferMax7301Byte(address), HEX;
    Serial.println("R: Value of write: ");
    Serial.println(transferMax7301Byte(0x00), BIN);
    digitalWrite(this->csPin, HIGH);
    
    digitalWrite(this->csPin, LOW);
    Serial.println("R: Address of read: ");
    Serial.println(transferMax7301Byte(0x00), HEX);
    data = transferMax7301Byte(0x00);
    Serial.println("R: Registry value: ");
    Serial.println(data, BIN);
    digitalWrite(this->csPin, HIGH);
    //SPI.endTransaction();

    return data;
}

void MyMax7301::writeGPIORegister(uint8_t address, uint8_t value)
{
    address &= ~0x80;

    //SPI.beginTransaction(this->spiSettings);
    digitalWrite(this->csPin, LOW);
    transferMax7301Byte(address);
    transferMax7301Byte(value);

    digitalWrite(this->csPin, HIGH);
    //SPI.endTransaction();
}