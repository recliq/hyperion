
// STL includes
#include <cstring>
#include <cstdio>
#include <iostream>

// hyperion local includes
#include "LedDeviceTpm2net.h"

LedDeviceTpm2net::LedDeviceTpm2net(const std::string& host, const uint16_t port, const uint16_t maxPacketsize) :
	LedUdpDevice(host, port),
	_ledBuffer(0),
	_maxPacketsize(maxPacketsize)
{
	// empty
}

int LedDeviceTpm2net::write(const std::vector<ColorRgb> &ledValues)
{
	int ret;
	uint16_t ledDatasize = 3*ledValues.size();
	uint16_t numPackets = ((7 + 3*ledValues.size()) / _maxPacketsize) + 1;
	uint16_t maxDatasize = ((_maxPacketsize - 7) / 3) * 3;

	uint16_t a;
	for (a=1; a<=numPackets; a++)
	{
		uint16_t datasize = ledDatasize - ((a-1)*maxDatasize) < maxDatasize ? ledDatasize - ((a-1)*maxDatasize) : maxDatasize;

   	_ledBuffer.resize(7 + datasize);
   	_ledBuffer[0] = 0x9C; // block-start byte
   	_ledBuffer[1] = 0xDA; // DATA frame
   	_ledBuffer[2] = (datasize >> 8) & 0xFF; // frame size high byte
   	_ledBuffer[3] = datasize & 0xFF; // frame size low byte
		_ledBuffer[4] = a; // current frame number
		_ledBuffer[5] = numPackets; // total frames
 		_ledBuffer.back() = 0x36; // block-end byte

		std::vector<ColorRgb> _ledData(ledValues.begin() + (a - 1) * maxDatasize / 3, ledValues.begin() + ((a - 1) * maxDatasize + datasize) / 3);

  	memcpy(6 + _ledBuffer.data(), _ledData.data(), datasize);
		ret = writeBytes(_ledBuffer.data(),_ledBuffer.size());
		if (ret != 0)
			return ret;
	}
	return 0;
}

int LedDeviceTpm2net::switchOff()
{
	_ledBuffer.resize(0);
	return 0;
}
