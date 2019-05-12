#include <Ole2.h>
#include <NuiApi.h>

#include <Common\Math\Utils.hpp>
#include <Common\Utils\MemoryHelper.hpp>

#include <KinectCore\Kinect\Sensor.hpp>
#include <KinectCore\Kinect\Stream.hpp>

namespace Kinect
{
int Sensor::getSensorsCount()
{
	int count;
	NuiGetSensorCount(&count);
	return count;
}

Sensor::Sensor()
	:m_IsInitialized(false), m_DeviceIndex(-1), m_Sensor(nullptr), m_ColorStream(new ColorStream()), m_DepthStream(new DepthStream())
{
	m_Skeletons.reserve(6);
}

Sensor::~Sensor()
{
	if (m_Sensor != nullptr)
	{
		m_Sensor->NuiShutdown();
	}

	SafeDelete(m_ColorStream);
	SafeDelete(m_DepthStream);
}

Error Sensor::init(int index)
{
	if (isInitialized())
	{
		return Error::DeviceAlreadyInitialized;
	}

	HRESULT result = NuiCreateSensorByIndex(index, &m_Sensor);
	if (result == S_OK)
	{
		result = m_Sensor->NuiInitialize(NUI_INITIALIZE_FLAG_USES_COLOR | NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX | NUI_INITIALIZE_FLAG_USES_SKELETON);
		if (result == S_OK)
		{
			result = m_Sensor->NuiSkeletonTrackingEnable(NULL, 0);
			if (result == S_OK)
			{
				m_ColorStream->openStream(m_Sensor);
				m_DepthStream->openStream(m_Sensor);

				m_IsInitialized = true;
				m_DeviceIndex = index;
			}
		}
	}

	return convertNuiToKinectError(result);
}

bool Sensor::isInitialized() const
{
	return m_IsInitialized;
}

int Sensor::getMinimumAngle()
{
	return NUI_CAMERA_ELEVATION_MINIMUM;
}

int Sensor::getMaximumAngle()
{
	return NUI_CAMERA_ELEVATION_MAXIMUM;
}

Error Sensor::update()
{
	Error error = updateAllDataFromDevice();
	return error;
}

int Sensor::getDeviceIndex() const
{
	return m_DeviceIndex;
}

Container::Array2D<Math::Scalar8UC3>& Sensor::getColorImage()
{
	return m_ColorStream->getImage();
}

Container::Array2D<Math::Scalar32FC3>& Sensor::getDepthImage()
{
	return m_DepthStream->getImage();
}

int Sensor::getAngle()
{
	long angle;
	NuiCameraElevationGetAngle(&angle);

	return static_cast<int>(angle);
}

void Sensor::setAngle(int angle)
{
	angle = Math::Utils::clamp(angle, Sensor::getMinimumAngle(), Sensor::getMaximumAngle());
	NuiCameraElevationSetAngle(angle);
}

Error Sensor::updateAllDataFromDevice()
{
	Error error = Error::NoError;

	error = m_DepthStream->updateStream(m_Sensor);
	if (error == Error::NoError)
	{
		error = m_ColorStream->updateStream(m_Sensor);
	}

	return error;
}

}

