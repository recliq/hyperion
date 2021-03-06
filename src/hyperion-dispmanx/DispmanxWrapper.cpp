
// Hyperion-Dispmanx includes
#include "DispmanxWrapper.h"

DispmanxWrapper::DispmanxWrapper(const unsigned grabWidth, const unsigned grabHeight, const unsigned updateRate_Hz) :
    _timer(this),
    _grabber(grabWidth, grabHeight)
{
    _timer.setSingleShot(false);
    _timer.setInterval(updateRate_Hz);

    // Connect capturing to the timeout signal of the timer
    connect(&_timer, SIGNAL(timeout()), this, SLOT(capture()));
}

const Image<ColorRgb> & DispmanxWrapper::getScreenshot()
{
	capture();
	return _screenshot_rgb;
}

void DispmanxWrapper::start()
{
    _timer.start();
}

void DispmanxWrapper::stop()
{
    _timer.stop();
}

void DispmanxWrapper::capture()
{
	_grabber.grabFrame(_screenshot);
	_screenshot.toRgb(_screenshot_rgb);

	emit sig_screenshot(_screenshot_rgb);
}
