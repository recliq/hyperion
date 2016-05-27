
// STL includes
#include <cstring>
#include <iostream>

// Qt includes
#include <QTimer>

// Serial includes
//#include <serial/serial.h>

// Local Hyperion includes
#include "LedUdpDevice.h"

LedUdpDevice::LedUdpDevice(const std::string& host, const uint16_t port) :
	_host(host),
	_port(port),
	_client()
{
	//_client = new QUdpSocket(this);
	// empty
}

LedUdpDevice::~LedUdpDevice()
{

}

int LedUdpDevice::open()
{
	_client.connectToHost(_host.c_str(), _port);
	return 0;
}

int LedUdpDevice::writeBytes(const uint8_t *data, const unsigned size)
{
	unsigned i;
	QByteArray udpdata;

	for (i=0; i<size; i++)
	{
		udpdata.append(data[i]);
	}
	try
	{
		_client.write(udpdata);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Unable to write to Udp device (" << e.what() << ")" << std::endl;
		return -1;
	}

	return 0;
}
