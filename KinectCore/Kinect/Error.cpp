#include <KinectCore\Kinect\Error.hpp>

#include <NuiApi.h>

namespace Kinect
{
Error convertNuiToKinectError(HRESULT result)
{
	switch (result)
	{
	case S_OK:
		return Error::NoError;
	case E_NUI_DEVICE_NOT_CONNECTED:
		return Error::DeviceNotConnected;
	case E_NUI_DEVICE_NOT_READY:
		return Error::DeviceNotReady;
	case E_NUI_ALREADY_INITIALIZED:
		return Error::DeviceAlreadyInitialized;
	case E_NUI_NO_MORE_ITEMS:
		return Error::NoMoreItems;
	case E_NUI_FRAME_NO_DATA:
		return Error::FrameNoData;
	case E_NUI_STREAM_NOT_ENABLED:
		return Error::StreamNotEnabled;
	case E_NUI_IMAGE_STREAM_IN_USE:
		return Error::StreamInUse;
	case E_NUI_FRAME_LIMIT_EXCEEDED:
		return Error::FrameLimitExceeded;
	case E_NUI_FEATURE_NOT_INITIALIZED:
		return Error::FeatureNotInitialized;
	case E_NUI_DATABASE_NOT_FOUND:
		return Error::DatabaseNotFound;
	case E_NUI_DATABASE_VERSION_MISMATCH:
		return Error::DatabaseVersionMismatch;
	case E_NUI_NOTCONNECTED:
		return Error::NotConnected;
	case E_NUI_NOTREADY:
		return Error::NotReady;
	case E_NUI_SKELETAL_ENGINE_BUSY:
		return Error::SkeletalEngineBusy;
	case E_NUI_NOTPOWERED:
		return Error::NotPowered;
	case E_NUI_BADIINDEX:
		return Error::BadIndex;
	default:
		return Error::UnknownError;
	}
}

std::string toString(Error error)
{
	switch (error)
	{
	case Error::NoError:
		return "No error";
	case Error::DeviceNotConnected:
		return "Device not connected";
	case Error::DeviceNotReady:
		return "Device not ready";
	case Error::DeviceAlreadyInitialized:
		return "Device already initialized";
	case Error::DeviceNotInitialized:
		return "Device not initialized";
	case Error::NoMoreItems:
		return "No more items";
	case Error::FrameNoData:
		return "Frame with no data";
	case Error::StreamNotEnabled:
		return "Streal not enabled/opened";
	case Error::StreamInUse:
		return "Stream in use";
	case Error::FrameLimitExceeded:
		return "Frame limit exceeeded";
	case Error::FeatureNotInitialized:
		return "Feature not initialized";
	case Error::DatabaseNotFound:
		return "Database not found";
	case Error::DatabaseVersionMismatch:
		return "Database version mismatch";
	case Error::NotConnected:
		return "Not connected";
	case Error::NotReady:
		return "Not ready";
	case Error::SkeletalEngineBusy:
		return "Skeletal engine busy";
	case Error::NotPowered:
		return "Not powered";
	case Error::BadIndex:
		return "Bad index";
	case Error::UnknownError:
	default:
		return "Unknown error";
	}
}

}
