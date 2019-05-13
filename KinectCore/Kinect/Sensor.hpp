#ifndef SENSOR_KINECTSENSOR_HPP
#define SENSOR_KINECTSENSOR_HPP

#include <vector>

#include <Common\Math\Scalar.hpp>
#include <Common\Container\Array.hpp>

#include <KinectCore\ImportExport.hpp>
#include <KinectCore\Kinect\Skeleton.hpp>
#include <KinectCore\Kinect\Error.hpp>

struct INuiSensor;

namespace Kinect
{

class DepthStream;
class ColorStream;

class KINECTCOREDLL_API Sensor
{
public:
	static int getSensorsCount();

	Sensor();
	~Sensor();

	Error init(int index = 0);
	bool isInitialized() const;
	Error update();
	int getDeviceIndex() const;

	Container::Array2D<Math::Scalar8UC3>& getColorImage();
	Container::Array2D<Math::Scalar32FC3>& getDepthImage();
	Container::Array2D<unsigned short>& getPlayersIndex();

	static int getMinimumAngle();
	static int getMaximumAngle();
	int getAngle() const;
	void setAngle(int angle);

	const std::vector<Skeleton>& getSkeletons() const;

private:
	bool m_IsInitialized;

	int m_DeviceIndex;
	INuiSensor *m_Sensor;

	ColorStream* m_ColorStream;
	DepthStream* m_DepthStream;

	std::vector<Skeleton> m_Skeletons;

	Error updateAllDataFromDevice();
};

}

#endif //SENSOR_KINECTSENSOR_HPP

