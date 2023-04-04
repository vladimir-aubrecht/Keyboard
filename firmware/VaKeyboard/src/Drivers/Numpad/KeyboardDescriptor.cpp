#if defined(NUMPAD)

#include "KeyboardDescriptor.h"

KeyboardDescriptor::KeyboardDescriptor(uint8_t numberOfRows, uint8_t numberOfColumns) : BaseKeyboardDescriptor(numberOfRows, numberOfColumns)
{
	this->keymaps = this->createKeyMap();
	this->coordMap = this->createCoordinatesMap(this->keymaps);
}

KeyCode *** KeyboardDescriptor::createKeyMap()
{
	KeyCode ***keymap = new KeyCode **[this->getLayersCount()];

	keymap[0] = new KeyCode *[this->numberOfRows];
	keymap[0][0] = new KeyCode[this->numberOfColumns]{KK_NUM_LOCK, KK_PAD_DIVIDE, KK_PAD_MULTIPLY, KK_PAD_SUBTRACT};
	keymap[0][1] = new KeyCode[this->numberOfColumns]{KK_PAD_7, KK_PAD_8, KK_PAD_9, KK_RESERVED};
	keymap[0][2] = new KeyCode[this->numberOfColumns]{KK_PAD_4, KK_PAD_5, KK_PAD_6, KK_PAD_ADD};
	keymap[0][3] = new KeyCode[this->numberOfColumns]{KK_PAD_1, KK_PAD_2, KK_PAD_3, KK_RESERVED};
	keymap[0][4] = new KeyCode[this->numberOfColumns]{KK_PAD_0, KK_RESERVED, KK_PAD_DOT, KK_PAD_ENTER};

	return keymap;
}

uint8_t KeyboardDescriptor::getSelectedLayer(Matrix *pressedKeysMatrix)
{
	return 0;
}

uint8_t KeyboardDescriptor::getLayersCount()
{
	return 1;
}

#endif