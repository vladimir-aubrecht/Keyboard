#include <stdbool.h>
#include "action.h"
#include "i2c_master.h"
#include "expander.h"
#include "debug.h"

#define I2C_TIMEOUT 200
static uint8_t expander_status = 0;

void expander_config(void);

void expander_init(void)
{
  i2c_init();
  expander_scan();
}

void expander_scan(void)
{
  uint8_t ret = i2c_start(EXPANDER_ADDR | I2C_WRITE, I2C_TIMEOUT);
  if (ret == 0) {
    i2c_stop();
    if (expander_status == 0) {
      dprintf("attached\n");
      expander_status = 1;
      expander_config();
      clear_keyboard();
    }
  }
  else {
    if (expander_status == 1) {
      dprintf("detached\n");
      expander_status = 0;
      clear_keyboard();
    }
  }
  //dprintf("%d\n", expander_status);
}

void expander_config(void)
{
  expander_write(EXPANDER_REG_IPOLA, 0xFF);
  expander_write(EXPANDER_REG_GPPUA, 0xFF);
  expander_write(EXPANDER_REG_IODIRB, 0xFF);
}

uint8_t expander_write(uint8_t reg, uint8_t data)
{
  if (expander_status == 0) {
    return 0;
  }
  uint8_t ret;
  ret = i2c_start(EXPANDER_ADDR | I2C_WRITE, I2C_TIMEOUT);
  if (ret) goto stop;
  ret = i2c_write(reg, I2C_TIMEOUT);
  if (ret) goto stop;
  ret = i2c_write(data, I2C_TIMEOUT);
 stop:
  i2c_stop();
  return ret;
}

uint8_t expander_read(uint8_t reg, uint8_t *data)
{
  if (expander_status == 0) {
    return 0;
  }
  uint8_t ret;
  ret = i2c_start(EXPANDER_ADDR | I2C_WRITE, I2C_TIMEOUT);
  if (ret) goto stop;
  ret = i2c_write(reg, I2C_TIMEOUT);
  if (ret) goto stop;
  ret = i2c_start(EXPANDER_ADDR | I2C_READ, I2C_TIMEOUT);
  if (ret) goto stop;
  *data = i2c_read_nack(I2C_TIMEOUT);
 stop:
  i2c_stop();
  return ret;
}
