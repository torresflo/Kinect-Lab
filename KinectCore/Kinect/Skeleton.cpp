#include <KinectCore\Kinect\Skeleton.hpp>

#include <Windows.h>
#include <Ole2.h>
#include <NuiApi.h>

namespace Kinect
{

unsigned int Skeleton::getMaxSkeletonCount()
{
	return NUI_SKELETON_COUNT;
}
unsigned int Skeleton::getPositionsCount()
{
	return Skeleton::POSITIONS_COUNT;
}

Skeleton::Skeleton()
{
	std::fill(m_Positions.begin(), m_Positions.end(), Math::Vector3f());
	std::fill(m_TrackingStatus.begin(), m_TrackingStatus.end(), TrackingStatus::NotTracked);
}

Skeleton::~Skeleton()
{}

void Skeleton::update(const NUI_SKELETON_DATA& skeletonData)
{
	m_ClippingStatus = static_cast<ClippingFlags>(skeletonData.dwQualityFlags);
	m_playerEnrollmentIndex = skeletonData.dwEnrollmentIndex;

	for (unsigned int i = 0; i < getPositionsCount(); ++i)
	{
		Vector4 position = skeletonData.SkeletonPositions[i];
		if (skeletonData.eSkeletonPositionTrackingState[i] == NUI_SKELETON_POSITION_TRACKING_STATE::NUI_SKELETON_POSITION_NOT_TRACKED)
		{
			m_Positions[i] = Math::Vector3f();
		}
		else
		{
			m_Positions[i] = Math::Vector3f(position.x, position.y, position.z);
		}
		m_TrackingStatus[i] = convertNuiToTrackingStatus(skeletonData.eSkeletonPositionTrackingState[i]);
	}
}

ClippingFlags Skeleton::getClippingFlags() const
{
	return m_ClippingStatus;
}

bool Skeleton::isClipped() const
{
	return m_ClippingStatus != ClippingFlags::NotClipped;
}

unsigned int Skeleton::getPlayerEnrollmentIndex() const
{
	return m_playerEnrollmentIndex;
}

const Math::Vector3f& Skeleton::getPosition(SkeletonPosition position)
{
	return m_Positions.at(static_cast<unsigned int>(position));
}

TrackingStatus Skeleton::getTrackingStatus(SkeletonPosition position)
{
	return m_TrackingStatus.at(static_cast<unsigned int>(position));
}

SkeletonPosition Skeleton::convertNuiToSkeletonPosition(NUI_SKELETON_POSITION_INDEX skeletonPosition) const
{
	switch (skeletonPosition)
	{
	case NUI_SKELETON_POSITION_INDEX::NUI_SKELETON_POSITION_HIP_CENTER:
		return SkeletonPosition::HipCenter;
	case NUI_SKELETON_POSITION_INDEX::NUI_SKELETON_POSITION_SPINE:
		return SkeletonPosition::Spine;
	case NUI_SKELETON_POSITION_INDEX::NUI_SKELETON_POSITION_SHOULDER_CENTER:
		return SkeletonPosition::ShoulderCenter;
	case NUI_SKELETON_POSITION_INDEX::NUI_SKELETON_POSITION_HEAD:
		return SkeletonPosition::Head;
	case NUI_SKELETON_POSITION_INDEX::NUI_SKELETON_POSITION_SHOULDER_LEFT:
		return SkeletonPosition::ShoulderLeft;
	case NUI_SKELETON_POSITION_INDEX::NUI_SKELETON_POSITION_ELBOW_LEFT:
		return SkeletonPosition::ElbowLeft;
	case NUI_SKELETON_POSITION_INDEX::NUI_SKELETON_POSITION_WRIST_LEFT:
		return SkeletonPosition::WristLeft;
	case NUI_SKELETON_POSITION_INDEX::NUI_SKELETON_POSITION_HAND_LEFT:
		return SkeletonPosition::HandLeft;
	case NUI_SKELETON_POSITION_INDEX::NUI_SKELETON_POSITION_SHOULDER_RIGHT:
		return SkeletonPosition::ShoulderRight;
	case NUI_SKELETON_POSITION_INDEX::NUI_SKELETON_POSITION_ELBOW_RIGHT:
		return SkeletonPosition::ElbowRight;
	case NUI_SKELETON_POSITION_INDEX::NUI_SKELETON_POSITION_WRIST_RIGHT:
		return SkeletonPosition::WristRight;
	case NUI_SKELETON_POSITION_INDEX::NUI_SKELETON_POSITION_HAND_RIGHT:
		return SkeletonPosition::HandRight;
	case NUI_SKELETON_POSITION_INDEX::NUI_SKELETON_POSITION_HIP_LEFT:
		return SkeletonPosition::HipLeft;
	case NUI_SKELETON_POSITION_INDEX::NUI_SKELETON_POSITION_KNEE_LEFT:
		return SkeletonPosition::KneeLeft;
	case NUI_SKELETON_POSITION_INDEX::NUI_SKELETON_POSITION_ANKLE_LEFT:
		return SkeletonPosition::AnkleLeft;
	case NUI_SKELETON_POSITION_INDEX::NUI_SKELETON_POSITION_FOOT_LEFT:
		return SkeletonPosition::FootLeft;
	case NUI_SKELETON_POSITION_INDEX::NUI_SKELETON_POSITION_HIP_RIGHT:
		return SkeletonPosition::HipRight;
	case NUI_SKELETON_POSITION_INDEX::NUI_SKELETON_POSITION_KNEE_RIGHT:
		return SkeletonPosition::KneeRight;
	case NUI_SKELETON_POSITION_INDEX::NUI_SKELETON_POSITION_ANKLE_RIGHT:
		return SkeletonPosition::AnkleRight;
	case NUI_SKELETON_POSITION_INDEX::NUI_SKELETON_POSITION_FOOT_RIGHT:
		return SkeletonPosition::FootRight;
	default:
		return SkeletonPosition::Invalid;
	}
}

TrackingStatus Skeleton::convertNuiToTrackingStatus(NUI_SKELETON_POSITION_TRACKING_STATE trackingStatus) const
{
	switch (trackingStatus)
	{
	case NUI_SKELETON_POSITION_TRACKING_STATE::NUI_SKELETON_POSITION_NOT_TRACKED:
		return TrackingStatus::NotTracked;
	case NUI_SKELETON_POSITION_TRACKING_STATE::NUI_SKELETON_POSITION_INFERRED:
		return TrackingStatus::Inferred;
	case NUI_SKELETON_POSITION_TRACKING_STATE::NUI_SKELETON_POSITION_TRACKED:
		return TrackingStatus::Tracked;
	default:
		return TrackingStatus::Invalid;
	}
}

}