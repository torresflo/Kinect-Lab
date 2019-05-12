#ifndef SENSOR_KINECTIMAGE_HPP
#define SENSOR_KINECTIMAGE_HPP

#include <Windows.h>
#include <NuiApi.h>

#include <Common\Container\Array.hpp>
#include <Common\Math\Scalar.hpp>

#include <KinectCore\ImportExport.hpp>
#include <KinectCore\Kinect\Error.hpp>

namespace Kinect
{

enum class ImageResolution
{
	Invalid = -1,
	Resolution80x60 = 0,
	Resolution320x240,
	Resolution640x480,
	Resolution1280x960
};

class AbstractStream
{
public:
	AbstractStream();
	
	Error openStream(INuiSensor* sensor, ImageResolution imageResolution = ImageResolution::Resolution640x480);
	Error updateStream(INuiSensor* sensor);

	bool isStreamOpened() const;
	ImageResolution getImageResolution() const;
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	unsigned int getPixelsCount() const;

protected:
	bool m_IsStreamOpened;
	ImageResolution m_ImageResolution;
	HANDLE m_Stream;
	NUI_IMAGE_FRAME m_ImageFrame;
	NUI_LOCKED_RECT m_LockedRect;

	virtual Error openStreamInternal(INuiSensor* sensor) = 0;
	virtual void updateStreamInternal(INuiSensor* sensor) = 0;
	NUI_IMAGE_RESOLUTION convertImageResolutionToNui(ImageResolution imageResolution) const;
};

class DepthStream : public AbstractStream
{
public:
	Container::Array2D<Math::Scalar32FC3>& getImage();

protected:
	virtual Error openStreamInternal(INuiSensor* sensor) override;
	virtual void updateStreamInternal(INuiSensor* sensor) override;

private:
	Container::Array2D<Math::Scalar32FC3> m_DepthImage; //(X, Y, Z) Float
};

class ColorStream : public AbstractStream
{
public:
	Container::Array2D<Math::Scalar8UC3>& getImage();

protected:
	virtual Error openStreamInternal(INuiSensor* sensor) override;
	virtual void updateStreamInternal(INuiSensor* sensor) override;

private:
	Container::Array2D<Math::Scalar8UC3> m_ColorImage; //(R, G, B) Unsigned char
};

}

#endif //SENSOR_KINECTIMAGE_HPP