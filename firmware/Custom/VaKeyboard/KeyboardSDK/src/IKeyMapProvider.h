#ifndef _IKeyMapProvider_h
#define _IKeyMapProvider_h

#include <Arduino.h>

class IKeyMapProvider
{
public:
	virtual uint16_t** getKeyMap() = 0;
};
#endif