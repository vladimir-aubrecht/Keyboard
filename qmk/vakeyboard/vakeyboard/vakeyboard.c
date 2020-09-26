#include "vakeyboard.h"
#include <print.h>

void keyboard_post_init_user(void) {
    debug_enable=true;
    debug_matrix=true;
    debug_keyboard=true;
}



bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

/*
    dprintf("row: %02X column: %02X direction: %s time: %u\r\n", record->event.key.row, record->event.key.col, (record->event.pressed ? "down" : "up"), record->event.time);
    dprintf("Expected keycode: %10X\r\n", pgm_read_word(&keymaps[(0)][(1)][(1)]));
    dprintf("Actual keycode: %10X\r\n", keycode);

    dprintf("Layer: %02X\r\n", layer_switch_get_layer(record->event.key));

    action_t action = store_or_get_action(record->event.pressed, record->event.key);
    dprint("Action: ");

    switch (action.kind.id) {
        case ACT_LMODS:
            dprint("ACT_LMODS");
            break;
        case ACT_RMODS:
            dprint("ACT_RMODS");
            break;
        case ACT_LMODS_TAP:
            dprint("ACT_LMODS_TAP");
            break;
        case ACT_RMODS_TAP:
            dprint("ACT_RMODS_TAP");
            break;
        case ACT_USAGE:
            dprint("ACT_USAGE");
            break;
        case ACT_MOUSEKEY:
            dprint("ACT_MOUSEKEY");
            break;
        case ACT_LAYER:
            dprint("ACT_LAYER");
            break;
        case ACT_LAYER_MODS:
            dprint("ACT_LAYER_MODS");
            break;
        case ACT_LAYER_TAP:
            dprint("ACT_LAYER_TAP");
            break;
        case ACT_LAYER_TAP_EXT:
            dprint("ACT_LAYER_TAP_EXT");
            break;
        case ACT_MACRO:
            dprint("ACT_MACRO");
            break;
        case ACT_FUNCTION:
            dprint("ACT_FUNCTION");
            break;
        case ACT_SWAP_HANDS:
            dprint("ACT_SWAP_HANDS");
            break;
        default:
            dprint("UNKNOWN");
            break;
    }
    dprintf("[%X:%02X]", action.kind.param >> 8, action.kind.param & 0xff);
    dprint("\r\n");
*/
    return process_record_user(keycode, record);
}
