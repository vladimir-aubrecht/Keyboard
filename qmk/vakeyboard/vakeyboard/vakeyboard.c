#include "vakeyboard.h"
#include <print.h>

void keyboard_post_init_user(void) {
    debug_enable=true;
    debug_matrix=false;
    debug_keyboard=true;
}
