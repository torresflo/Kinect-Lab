#ifndef SENSOR_KINECTERROR_HPP
#define SENSOR_KINECTERROR_HPP

#include <string>

#include <Windows.h>

#include <KinectCore\ImportExport.hpp>

namespace Kinect
{

enum class KINECTCOREDLL_API Error
{
	NoError = 0,
	DeviceNotConnected,
	DeviceNotReady,
	DeviceNotInitialized,
	DeviceAlreadyInitialized,
	NoMoreItems,
	FrameNoData,
	StreamNotEnabled,
	StreamInUse,
	FrameLimitExceeded,
	FeatureNotInitialized,
	DatabaseNotFound,
	DatabaseVersionMismatch,
	NotConnected,
	NotReady,
	SkeletalEngineBusy,
	NotPowered,
	BadIndex,
	UnknownError
};

Error convertNuiToKinectError(HRESULT result);

KINECTCOREDLL_API std::string toString(Error error);

}

#endif //SENSOR_KINECTERROR_HPP