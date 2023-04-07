#include "BaseKeyboardDescriptor.h"

BaseKeyboardDescriptor::BaseKeyboardDescriptor(uint8_t numberOfRows, uint8_t numberOfColumns)
{
    this->numberOfRows = numberOfRows;
    this->numberOfColumns = numberOfColumns;
}

uint8_t BaseKeyboardDescriptor::getRowCount()
{
    return this->numberOfRows;
}

uint8_t BaseKeyboardDescriptor::getColumnCount()
{
    return this->numberOfColumns;
}

BaseKeyboardDescriptor::Coordinates **BaseKeyboardDescriptor::getCoordinatesMap()
{
    return this->coordMap;
}

KeyCode ***BaseKeyboardDescriptor::getKeyMap()
{
    return keymaps;
}

FeatureMacro** BaseKeyboardDescriptor::getFeatureMacros()
{
    return this->featureMacros;
}

uint8_t BaseKeyboardDescriptor::getFeatureMacroCount()
{
    return this->featureMacroCount;
}

KeyType BaseKeyboardDescriptor::getKeyType(uint8_t layer, uint8_t row, uint8_t column)
{
    if (layer == 1 && row == 0)	// This is hack as I mostly test on Feather32u4 and I don't have enough of flash storage to send whole map ...
    {
        auto keyCode = this->getKeyMap()[1][row][column];

        switch (keyCode)
        {
        case KK_PREVIOUS:
        case KK_NEXT:
        case KK_PLAY_PAUSE:
        case KK_VOLUME_MUTE:
        case KK_VOLUME_DOWN:
        case KK_VOLUME_UP:
            return KeyType::MEDIA;

        default:
            return KeyType::KEY;
        }
    }

    return KeyType::KEY;
}

BaseKeyboardDescriptor::Coordinates ** BaseKeyboardDescriptor::createCoordinatesMap(KeyCode ***keymaps)
{
	Coordinates ** coordMap = new Coordinates*[0xff - 0x76 + 1];	//registering keys from 0x76 up just becaues I don't have enough of memory on Feather 32u4 for now.

	for (uint8_t layer = 0; layer < 1; layer++)
	{
		for (uint8_t row = 4; row < this->getRowCount(); row++)	//skipping first row just because I don't have enough of memory on Feather 32u4 for now.
		{
			for (uint8_t column = 0; column < this->getColumnCount(); column++)
			{
				Coordinates* coord = new Coordinates(row, column);
				auto key = keymaps[layer][row][column];

				if (key >= 0x76)
				{
					coordMap[(uint8_t)key - 0x76] = coord;
				}
			}	
		}
	}

    return coordMap;
}