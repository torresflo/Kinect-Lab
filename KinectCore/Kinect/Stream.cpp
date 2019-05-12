#include <KinectCore\Kinect\Stream.hpp>

namespace Kinect
{

///////////////// AbstractStream /////////////////

AbstractStream::AbstractStream()
	:m_IsStreamOpened(false), m_ImageResolution(ImageResolution::Invalid)
{
}

Error AbstractStream::openStream(INuiSensor * sensor, ImageResolution imageResolution)
{
	m_ImageResolution = imageResolution;
	Error error = Error::BadIndex;
	if (sensor != nullptr
		&& m_ImageResolution != ImageResolution::Invalid)
	{
		error = openStreamInternal(sensor);
		if (error == Error::NoError)
		{
			m_IsStreamOpened = true;
		}
	}
	return error;
}

Error AbstractStream::updateStream(INuiSensor * sensor)
{
	Error error = Error::BadIndex;
	if (sensor != nullptr)
	{
		HRESULT result = sensor->NuiImageStreamGetNextFrame(m_Stream, 0, &m_ImageFrame);
		if (result == S_OK)
		{
			INuiFrameTexture* texture = m_ImageFrame.pFrameTexture;
			result = texture->LockRect(0, &m_LockedRect, NULL, 0);

			if (result == S_OK
				&& m_LockedRect.Pitch != 0)
			{
				updateStreamInternal(sensor);
			}
			texture->UnlockRect(0);
			result = sensor->NuiImageStreamReleaseFrame(m_Stream, &m_ImageFrame);
		}
		error = convertNuiToKinectError(result);
	}
	return error;
}

bool AbstractStream::isStreamOpened() const
{
	return m_IsStreamOpened;
}

ImageResolution AbstractStream::getImageResolution() const
{
	return m_ImageResolution;
}

unsigned int AbstractStream::getWidth() const
{
	unsigned int width = 0;
	switch (m_ImageResolution)
	{
	case ImageResolution::Resolution80x60:
		width = 80;
		break;
	case ImageResolution::Resolution320x240:
		width = 320;
		break;
	case ImageResolution::Resolution640x480:
		width = 640;
		break;
	case ImageResolution::Resolution1280x960:
		width = 1280;
		break;
	case ImageResolution::Invalid:
	default:
		break;
	}
	return width;
}

unsigned int AbstractStream::getHeight() const
{
	unsigned int height = 0;
	switch (m_ImageResolution)
	{
	case ImageResolution::Resolution80x60:
		height = 60;
		break;
	case ImageResolution::Resolution320x240:
		height = 240;
		break;
	case ImageResolution::Resolution640x480:
		height = 480;
		break;
	case ImageResolution::Resolution1280x960:
		height = 960;
		break;
	case ImageResolution::Invalid:
	default:
		break;
	}
	return height;
}

unsigned int AbstractStream::getPixelsCount() const
{
	return getWidth() * getHeight();
}

NUI_IMAGE_RESOLUTION AbstractStream::convertImageResolutionToNui(ImageResolution imageResolution) const
{
	switch (imageResolution)
	{
	case ImageResolution::Resolution80x60:
		return NUI_IMAGE_RESOLUTION::NUI_IMAGE_RESOLUTION_80x60;
	case ImageResolution::Resolution320x240:
		return NUI_IMAGE_RESOLUTION::NUI_IMAGE_RESOLUTION_320x240;
	case ImageResolution::Resolution640x480:
		return NUI_IMAGE_RESOLUTION::NUI_IMAGE_RESOLUTION_640x480;
	case ImageResolution::Resolution1280x960:
		return NUI_IMAGE_RESOLUTION::NUI_IMAGE_RESOLUTION_1280x960;
	case ImageResolution::Invalid:
	default:
		return NUI_IMAGE_RESOLUTION::NUI_IMAGE_RESOLUTION_INVALID;
	}
}

///////////////// DepthStream /////////////////

Container::Array2D<Math::Scalar32FC3>& DepthStream::getImage()
{
	return m_DepthImage;
}

Error DepthStream::openStreamInternal(INuiSensor * sensor)
{
	Container::ArrayDimensions<2> dimensions(getWidth(), getHeight());
	m_DepthImage.resize(dimensions, Math::Scalar32FC3(0));

	HRESULT result = sensor->NuiImageStreamOpen(NUI_IMAGE_TYPE::NUI_IMAGE_TYPE_DEPTH_AND_PLAYER_INDEX, convertImageResolutionToNui(m_ImageResolution), 0, 2, NULL, &m_Stream);
	return convertNuiToKinectError(result);
}

void DepthStream::updateStreamInternal(INuiSensor * sensor)
{
	const unsigned short* start = reinterpret_cast<const unsigned short*>(m_LockedRect.pBits);
	float* depthImagePointer = reinterpret_cast<float*>(m_DepthImage.getData());

	unsigned int height = getHeight();
	unsigned int width = getWidth();

	Vector4 position;
	for (unsigned int j = 0; j < height; ++j)
	{
		for (unsigned int i = 0; i < width; ++i)
		{
			position = NuiTransformDepthImageToSkeleton(i, j, *start);
			*depthImagePointer++ = position.x / position.w;
			*depthImagePointer++ = position.y / position.w;
			*depthImagePointer++ = position.z / position.w;
			*start++;
		}
	}
}

///////////////// ColorStream /////////////////

Container::Array2D<Math::Scalar8UC3>& ColorStream::getImage()
{
	return m_ColorImage;
}

Error ColorStream::openStreamInternal(INuiSensor * sensor)
{
	Container::ArrayDimensions<2> dimensions(getWidth(), getHeight());
	m_ColorImage.resize(dimensions, Math::Scalar8UC3(0));

	HRESULT result = sensor->NuiImageStreamOpen(NUI_IMAGE_TYPE::NUI_IMAGE_TYPE_COLOR, convertImageResolutionToNui(m_ImageResolution), 0, 2, NULL, &m_Stream);
	return convertNuiToKinectError(result);
}

void ColorStream::updateStreamInternal(INuiSensor * sensor)
{
	const unsigned char* start = static_cast<const unsigned char*>(m_LockedRect.pBits);
	unsigned char* colorImagePointer = reinterpret_cast<unsigned char*>(m_ColorImage.getData());

	unsigned int height = getHeight();
	unsigned int width = getWidth();
	long x = 0, y = 0;

	for (unsigned int j = 0; j < height; ++j)
	{
		for (unsigned int i = 0; i < width; ++i)
		{
			x = i;
			y = j;

			const unsigned char* color = start + (x + width * y) * 4;
			*colorImagePointer++ = color[2];
			*colorImagePointer++ = color[1];
			*colorImagePointer++ = color[0];
		}
	}
}

}
