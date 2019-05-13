#ifndef SENSOR_KINECTSKELETON_HPP
#define SENSOR_KINECTSKELETON_HPP

#include <array>

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

enum KINECTCOREDLL_API ClippingFlags
{
	NotClipped = 0x00000000,
	ClippedRight = 0x00000001,
	ClippedLeft = 0x00000002,
	ClippedTop = 0x00000004,
	ClippedBottom = 0x00000008,
};

class KINECTCOREDLL_API Skeleton
{
public:
	static unsigned int getMaxSkeletonCount();
	static unsigned int getPositionsCount();

	Skeleton();
	~Skeleton();

	void update(const NUI_SKELETON_DATA& skeletonDataFrame);

	ClippingFlags getClippingFlags() const;
	bool isClipped() const;

	unsigned int getPlayerEnrollmentIndex() const;

	const Math::Vector3f& getPosition(SkeletonPosition position) const;
	TrackingStatus getTrackingStatus(SkeletonPosition position) const;

private:
	static const unsigned int POSITIONS_COUNT = 20;
	std::array<Math::Vector3f, POSITIONS_COUNT> m_Positions;
	std::array<TrackingStatus, POSITIONS_COUNT> m_TrackingStatus;

	ClippingFlags m_ClippingStatus = ClippingFlags::NotClipped;
	unsigned int m_playerEnrollmentIndex = 0;

	SkeletonPosition convertNuiToSkeletonPosition(NUI_SKELETON_POSITION_INDEX skeletonPosition) const;
	TrackingStatus convertNuiToTrackingStatus(NUI_SKELETON_POSITION_TRACKING_STATE trackingStatus) const;
};

}

#endif //SENSOR_KINECTSKELETON_HPP

