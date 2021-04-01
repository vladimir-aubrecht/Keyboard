#include <stdint.h>
#include <stdbool.h>
#include "wait.h"
#include "util.h"
#include "print.h"
#include "matrix.h"
#include "quantum.h"
#include "expander.h"

static matrix_row_t previous_states[MATRIX_ROWS];

void select_row_custom(uint8_t row)
{
    row = 0xFF & ~(1<<row);
    expander_write(EXPANDER_ADDR1, EXPANDER_REG_GPIOB, row);
}

void unselect_row_custom(uint8_t row)
{
    expander_write(EXPANDER_ADDR1, EXPANDER_REG_GPIOB, 0xFF);
}

void matrix_init_custom(void) {

    for (uint8_t i = 0; i < MATRIX_ROWS; i++)
    {
        previous_states[i] = 0;
    }

    expander_init();
}

uint8_t read_pin_custom(pin_t pin)
{
    if (pin >= EXP1_A0 && pin <= EXP2_B7)
    {
        static uint8_t data = 0;
        uint8_t pin_number = 0;
        if (pin >= EXP2_A0)
        {
            pin_number = (pin - EXP2_A0);
            expander_read(EXPANDER_ADDR1, EXPANDER_REG_GPIOA, &data);
        }
        else if (pin >= EXP1_B0)
        {
            pin_number = (pin - EXP1_B0);
            expander_read(EXPANDER_ADDR0, EXPANDER_REG_GPIOB, &data);
        }
        else
        {
            pin_number = (pin - EXP1_A0);
            expander_read(EXPANDER_ADDR0, EXPANDER_REG_GPIOA, &data);
        }

        uint8_t result = ((data & ( 1 << pin_number )) >> pin_number) == 0 ? 1 : 0;
        return result;
    }
    else
    {
        return readPin(pin);
    }

}
