#ifndef SENSOR_KINECTSKELETON_HPP
#define SENSOR_KINECTSKELETON_HPP

#include <vector>

#include <KinectCore\ImportExport.hpp>
#include <Common\Math\Vector.hpp>

struct _NUI_SKELETON_DATA;
typedef _NUI_SKELETON_DATA NUI_SKELETON_DATA;
enum _NUI_SKELETON_POSITION_INDEX;
typedef _NUI_SKELETON_POSITION_INDEX NUI_SKELETON_POSITION_INDEX;
enum _NUI_SKELETON_POSITION_TRACKING_STATE;
typedef _NUI_SKELETON_POSITION_TRACKING_STATE NUI_SKELETON_POSITION_TRACKING_STATE;

class Sensor;

namespace Kinect
{

enum class KINECTCOREDLL_API SkeletonPosition
{
	Invalid = -1,
	HipCenter = 0,
	Spine,
	ShoulderCenter,
	Head,
	ShoulderLeft,
	ElbowLeft,
	WristLeft,
	HandLeft,
	ShoulderRight,
	ElbowRight,
	WristRight,
	HandRight,
	HipLeft,
	KneeLeft,
	AnkleLeft,
	FootLeft,
	HipRight,
	KneeRight,
	AnkleRight,
	FootRight
};

enum class KINECTCOREDLL_API TrackingStatus
{
	Invalid = -1,
	NotTracked = 0,
	Inferred,
	Tracked
};

class KINECTCOREDLL_API Skeleton
{
public:
	static unsigned int getPositionsCount();

	Skeleton();
	~Skeleton();

	void update(const NUI_SKELETON_DATA& skeletonFrame);

	const Math::Vector3f& getPosition(SkeletonPosition position);
	TrackingStatus getTrackingStatus(SkeletonPosition position);

private:
	std::vector<Math::Vector3f> m_Positions;
	std::vector<TrackingStatus> m_TrackingStatus;

	SkeletonPosition convertNuiToSkeletonPosition(NUI_SKELETON_POSITION_INDEX skeletonPosition) const;
	TrackingStatus convertNuiToTrackingStatus(NUI_SKELETON_POSITION_TRACKING_STATE trackingStatus) const;
};

}

#endif //SENSOR_KINECTSKELETON_HPP

