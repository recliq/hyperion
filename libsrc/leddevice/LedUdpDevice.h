#pragma once

// Qt includes
#include <QObject>
#include <QUdpSocket>

// Leddevice includes
#include <leddevice/LedDevice.h>

///
/// The LedRs232Device implements an abstract base-class for LedDevices using a RS232-device.
///
class LedUdpDevice : public QObject, public LedDevice
{
	Q_OBJECT

public:
	///
	/// Constructs the LedDevice attached to a UDP socket
	///
	/// @param[in] ipAddress The client IP address
	/// @param[in] port The client port number
	///
	LedUdpDevice(const std::string& host, const uint16_t port);

	///
	/// Destructor of the LedDevice; closes the output device if it is open
	///
	virtual ~LedUdpDevice();

	///
	/// Opens and configures the output device
	///
	/// @return Zero on succes else negative
	///
	int open();

protected:
	///
	/// Writes the given bytes to the UDP socket.
	///
	/// @param[in[ size The length of the data
	/// @param[in] data The data
	/// @return Zero on succes else negative
	///
	int writeBytes(const uint8_t *data, const unsigned size);

private:
  const std::string	_host;
  const uint16_t    _port;
	QUdpSocket				_client;

};
