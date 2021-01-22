#include <stdbool.h>
#include "action.h"
#include "i2c_master.h"
#include "expander.h"
#include "debug.h"

#define I2C_TIMEOUT 200

void expander_config(uint8_t expander_address, bool is_A_input_expander, bool is_B_input_expander);
void expander_scan(uint8_t expander_address, bool is_A_input_expander, bool is_B_input_expander);

void expander_init(void)
{
  i2c_init();
  expander_scan(EXPANDER_ADDR0, true, true);
  expander_scan(EXPANDER_ADDR1, true, false);
}

void expander_scan(uint8_t expander_address, bool is_A_input_expander, bool is_B_input_expander)
{
  uint8_t ret = i2c_start(expander_address | I2C_WRITE, I2C_TIMEOUT);
  if (ret == 0) {
    i2c_stop();
    dprintf("attached\n");
    expander_config(expander_address, is_A_input_expander, is_B_input_expander);
    clear_keyboard();
  }
}

void expander_config(uint8_t expander_address, bool is_A_input_expander, bool is_B_input_expander)
{
  // polarity
  expander_write(expander_address, EXPANDER_REG_IPOLA, 0xFF);
  expander_write(expander_address, EXPANDER_REG_IPOLB, 0xFF);

  // turn on pull-ups
  expander_write(expander_address, EXPANDER_REG_GPPUA, 0xFF);
  expander_write(expander_address, EXPANDER_REG_GPPUB, 0xFF);

  // set everything to input
  expander_write(expander_address, EXPANDER_REG_IODIRA, is_A_input_expander ? 0xFF : 0x0);
  expander_write(expander_address, EXPANDER_REG_IODIRB, is_B_input_expander ? 0xFF : 0x0);
}

uint8_t expander_write(uint8_t expander_address, uint8_t reg, uint8_t data)
{
  uint8_t ret;
  ret = i2c_start(expander_address | I2C_WRITE, I2C_TIMEOUT);
  if (ret) goto stop;
  ret = i2c_write(reg, I2C_TIMEOUT);
  if (ret) goto stop;
  ret = i2c_write(data, I2C_TIMEOUT);
 stop:
  i2c_stop();
  return ret;
}

uint8_t expander_read(uint8_t expander_address, uint8_t reg, uint8_t *data)
{
  uint8_t ret;
  ret = i2c_start(expander_address | I2C_WRITE, I2C_TIMEOUT);
  if (ret) goto stop;
  ret = i2c_write(reg, I2C_TIMEOUT);
  if (ret) goto stop;
  ret = i2c_start(expander_address | I2C_READ, I2C_TIMEOUT);
  if (ret) goto stop;
  *data = i2c_read_nack(I2C_TIMEOUT);
 stop:
  i2c_stop();
  return ret;
}
