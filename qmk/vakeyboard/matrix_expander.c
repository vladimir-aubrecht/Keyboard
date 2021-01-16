#include <stdint.h>
#include <stdbool.h>
#include "wait.h"
#include "util.h"
#include "print.h"
#include "matrix.h"
#include "quantum.h"
#include "expander.h"

static matrix_row_t previous_states[MATRIX_ROWS];

static matrix_row_t read_columns(void);
static matrix_row_t read_columns(void)
{
    static uint8_t matrix_row_a = 0;
    static uint8_t matrix_row_b = 0;
    expander_read(EXPANDER_REG_GPIOA, &matrix_row_a);
    expander_read(EXPANDER_REG_GPIOB, &matrix_row_b);

    return matrix_row_a | (matrix_row_b << 8);
}


void matrix_init_custom(void) {

    for (uint8_t i = 0; i < MATRIX_ROWS; i++)
    {
        previous_states[i] = 0;
    }

    expander_init();
}

uint8_t readPinCustom(pin_t pin)
{
    if (pin >= EXP_A0 && pin <= EXP_B7)
    {
        uint8_t pin_number = 0;
        if (pin >= EXP_B0)
        {
            pin_number = 8 + (pin - EXP_B0);
        }
        else
        {
            pin_number = (pin - EXP_A0);
        }
        matrix_row_t data = read_columns();

        uint8_t result = ((data & ( 1 << pin_number )) >> pin_number) == 0 ? 1 : 0;
        return result;
    }
    else
    {
        return readPin(pin);
    }

}
