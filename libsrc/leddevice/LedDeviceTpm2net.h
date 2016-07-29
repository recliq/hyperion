#pragma once

// STL includes
#include <string>

// hyperion incluse
#include "LedUdpDevice.h"

///
/// Implementation of the LedDevice interface for writing to network using Tpm2net protocol.
///
class LedDeviceTpm2net : public LedUdpDevice
{
public:
	///
	/// Constructs the LedDevice for network UDP socket using Tpm2net protocol.
	///
	/// @param host The hostname/ip of the target device (eg '192.168.1.11')
	/// @param port The port to send UDP packets to (eg 65506)
	/// @param maxPacketsize The maximum size for a single UDP packet, if the LEDs data is larger
	///                      it will be split into multiple packets.
	///
	LedDeviceTpm2net(const std::string& host, const uint16_t port, const uint16_t maxPacketsize);

	///
	/// Writes the led color values to the led-device
	///
	/// @param ledValues The color-value per led
	/// @return Zero on succes else negative
	///
	virtual int write(const std::vector<ColorRgb> &ledValues);

	/// Switch the leds off
	virtual int switchOff();

private:
	/// The buffer containing the packed RGB values
	std::vector<uint8_t> _ledBuffer;
	/// The max. UDP packetsize
	uint16_t _maxPacketsize;
};
