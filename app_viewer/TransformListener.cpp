#include "TransformListener.h"

TransformListener::TransformListener()
{

}

TransformListener::~TransformListener()
{
	m_vecTransform.clear();
}

/************************************************************************/
/* 
push the transform to the transform vector
*/
/************************************************************************/
void TransformListener::PushbackNewTransform(const TRANSFORM* transform)
{
	m_mtuTransform.lock();
	TRANSFORM stTransform;
	memcpy(&stTransform, transform, sizeof(TRANSFORM));

	if (!stTransform.bReseted)
	{
		m_vecTransform.push_back(stTransform);
	}
	else
	{
		m_vecTransform.clear();
		m_vecTransform.push_back(stTransform);
	}

	if (m_vecTransform.size() >= 501)
	{
		m_vecTransform.erase(m_vecTransform.begin());
	}
	m_mtuTransform.unlock();
}


/************************************************************************/
/*                                                                      */
/************************************************************************/
const bool TransformListener::GetStampedTransform(const unsigned long long timestamp, TRANSFORM& transform)
{
	m_mtuTransform.lock();
	if (m_vecTransform.size() == 0)
	{
		m_mtuTransform.unlock();
		return false;
	}

	unsigned int firstIndex, lastIndex;
	firstIndex = 0;
	lastIndex = m_vecTransform.size() - 1;

	if (timestamp < m_vecTransform.data()[firstIndex].nRTKTimeStamp - 100000)
	{
		m_mtuTransform.unlock();
		return false;
	}

	if (timestamp > m_vecTransform.data()[lastIndex].nRTKTimeStamp + 100000)
	{
		m_mtuTransform.unlock();
		return false;
	}

	if (timestamp <= m_vecTransform.data()[firstIndex].nRTKTimeStamp)
	{
		//copy first to transform;
		CopyTransform(firstIndex, transform);
		//fprintf(stderr,"First %ld %ld %ld\n",timestamp,m_vecTransform.data() [firstIndex].stHeader.nTimeStamp,m_vecTransform.data() [lastIndex].stHeader.nTimeStamp);
		m_mtuTransform.unlock();
		return true;
	}

	if (timestamp >= m_vecTransform.data()[lastIndex].nRTKTimeStamp)
	{
		//copy last to transform;
		CopyTransform(lastIndex, transform);
		//fprintf(stderr,"Last %ld %ld %ld\n",timestamp,m_vecTransform.data() [firstIndex].stHeader.nTimeStamp,m_vecTransform.data() [lastIndex].stHeader.nTimeStamp);
		m_mtuTransform.unlock();
		return true;
	}

	//binary search;
	unsigned int nLeftIndex = 0, nRightIndex = 0;
	BinarySearch(timestamp, nLeftIndex, nRightIndex);

	//interpolate transform;
	InterpolateTransform(timestamp, nLeftIndex, nRightIndex, transform);

	m_mtuTransform.unlock();
	return true;
}

/************************************************************************/
/*       
copy one transform to another
*/
/************************************************************************/
inline void TransformListener::CopyTransform(const unsigned int src, TRANSFORM &dest) const
{
	memcpy(&dest, &(m_vecTransform.data()[src]), sizeof(TRANSFORM));
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void TransformListener::BinarySearch(const unsigned long long timestamp, unsigned int& leftIndex, unsigned int& rightIndex
	)
{
	leftIndex = 0;
	rightIndex = m_vecTransform.size() - 1;
	unsigned int centerIndex = 0;
	while (rightIndex - leftIndex > 1)
	{
		centerIndex = (leftIndex + rightIndex) / 2;
		if (timestamp >= m_vecTransform.data()[centerIndex].nRTKTimeStamp)//.stHeader.nTimeStamp )
		{
			leftIndex = centerIndex;
			continue;
		}
		if (timestamp <= m_vecTransform.data()[centerIndex].nRTKTimeStamp)//.stHeader.nTimeStamp )
		{
			rightIndex = centerIndex;
			continue;
		}
	}
	return;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
inline void TransformListener::InterpolateTransform(const unsigned long long timestamp, const unsigned int leftIndex, const
	unsigned int rightIndex, TRANSFORM& transform) const
{
	//    float fLeftRatio = ( timestamp-m_vecTransform.data() [leftIndex].stHeader.nTimeStamp ) *1.0f/ (
	//                m_vecTransform.data() [rightIndex].stHeader.nTimeStamp-m_vecTransform.data()
	//                [leftIndex].stHeader.nTimeStamp );
	float fLeftRatio = (timestamp - m_vecTransform.data()[leftIndex].nRTKTimeStamp) *1.0f / (
		m_vecTransform.data()[rightIndex].nRTKTimeStamp - m_vecTransform.data()
		[leftIndex].nRTKTimeStamp);
	float fRightRatio = 1.0f - fLeftRatio;

	memcpy(&transform, &(m_vecTransform.data()[leftIndex]), sizeof(TRANSFORM));

	//interpolate vehicle pose in world;
	transform.gfVehiclePoseInWorld[0] = m_vecTransform.data()[leftIndex].gfVehiclePoseInWorld[0] * fLeftRatio
		+ m_vecTransform.data()[rightIndex].gfVehiclePoseInWorld[0] * fRightRatio;
	transform.gfVehiclePoseInWorld[1] = m_vecTransform.data()[leftIndex].gfVehiclePoseInWorld[1] * fLeftRatio
		+ m_vecTransform.data()[rightIndex].gfVehiclePoseInWorld[1] * fRightRatio;
	transform.gfVehiclePoseInWorld[2] = m_vecTransform.data()[leftIndex].gfVehiclePoseInWorld[2] * fLeftRatio
		+ m_vecTransform.data()[rightIndex].gfVehiclePoseInWorld[2] * fRightRatio;

	if (m_vecTransform.data()[leftIndex].gfVehiclePoseInWorld[3] > (m_vecTransform.data()[rightIndex].gfVehiclePoseInWorld[3] + PI))
	{
		transform.gfVehiclePoseInWorld[3] = m_vecTransform.data()[leftIndex].gfVehiclePoseInWorld[3] * fLeftRatio
			+ (m_vecTransform.data()[rightIndex].gfVehiclePoseInWorld[3] + PI_DOUBLE) * fRightRatio;
		transform.gfVehiclePoseInWorld[3] = (transform.gfVehiclePoseInWorld[3] > PI_DOUBLE) ? (transform.gfVehiclePoseInWorld[3] - PI_DOUBLE) : transform.gfVehiclePoseInWorld[3];
	}
	else if ((m_vecTransform.data()[leftIndex].gfVehiclePoseInWorld[3] + PI) < m_vecTransform.data()[rightIndex].gfVehiclePoseInWorld[3])
	{
		transform.gfVehiclePoseInWorld[3] = (m_vecTransform.data()[leftIndex].gfVehiclePoseInWorld[3] + PI_DOUBLE) * fLeftRatio
			+ m_vecTransform.data()[rightIndex].gfVehiclePoseInWorld[3] * fRightRatio;
		transform.gfVehiclePoseInWorld[3] = (transform.gfVehiclePoseInWorld[3] > PI_DOUBLE) ? (transform.gfVehiclePoseInWorld[3] - PI_DOUBLE) : transform.gfVehiclePoseInWorld[3];
	}
	else
	{
		transform.gfVehiclePoseInWorld[3] = m_vecTransform.data()[leftIndex].gfVehiclePoseInWorld[3] * fLeftRatio
			+ m_vecTransform.data()[rightIndex].gfVehiclePoseInWorld[3] * fRightRatio;
	}


	transform.gfVehiclePoseInWorld[4] = m_vecTransform.data()[leftIndex].gfVehiclePoseInWorld[4] * fLeftRatio
		+ m_vecTransform.data()[rightIndex].gfVehiclePoseInWorld[4] * fRightRatio;
	transform.gfVehiclePoseInWorld[5] = m_vecTransform.data()[leftIndex].gfVehiclePoseInWorld[5] * fLeftRatio
		+ m_vecTransform.data()[rightIndex].gfVehiclePoseInWorld[5] * fRightRatio;

	//interpolate vehicle velocity in world;
	transform.gfVehicleVelocityInWorld[0] = m_vecTransform.data()[leftIndex].gfVehicleVelocityInWorld[0] * fLeftRatio
		+ m_vecTransform.data()
		[rightIndex].gfVehicleVelocityInWorld[0] * fRightRatio;
	transform.gfVehicleVelocityInWorld[1] = m_vecTransform.data()[leftIndex].gfVehicleVelocityInWorld[1] * fLeftRatio
		+ m_vecTransform.data()
		[rightIndex].gfVehicleVelocityInWorld[1] * fRightRatio;
	transform.gfVehicleVelocityInWorld[2] = m_vecTransform.data()[leftIndex].gfVehicleVelocityInWorld[2] * fLeftRatio
		+ m_vecTransform.data()
		[rightIndex].gfVehicleVelocityInWorld[2] * fRightRatio;

	//calculate transform matrix from vehicle to world;
	CalculateTransformMatrix(transform.gfVehiclePoseInWorld[0],
		transform.gfVehiclePoseInWorld[1],
		transform.gfVehiclePoseInWorld[2],
		transform.gfVehiclePoseInWorld[3],
		transform.gfVehiclePoseInWorld[4],
		transform.gfVehiclePoseInWorld[5],
		transform.gfTransformVehicle2World);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void TransformListener::CalculateTransformMatrix(const float x, const float y, const float z, const float yaw, const
	float pitch, const float roll, float(&transform)[4][4]) const
{
	float cosyaw = cos(yaw);
	float sinyaw = sin(yaw);
	float cospitch = cos(pitch);
	float sinpitch = sin(pitch);
	float cosroll = cos(roll);
	float sinroll = sin(roll);
	transform[0][0] = cosyaw*cospitch;
	transform[0][1] = cosyaw*sinroll*sinpitch - cosroll*sinyaw;
	transform[0][2] = sinyaw*sinroll + cosyaw*cosroll*sinpitch;
	transform[0][3] = x;

	transform[1][0] = cospitch*sinyaw;
	transform[1][1] = cosyaw*cosroll + sinyaw*sinroll*sinpitch;
	transform[1][2] = cosroll*sinyaw*sinpitch - cosyaw*sinroll;
	transform[1][3] = y;

	transform[2][0] = -sinpitch;
	transform[2][1] = cospitch*sinroll;
	transform[2][2] = cosroll*cospitch;
	transform[2][3] = z;

	transform[3][0] = 0.0f;
	transform[3][1] = 0.0f;
	transform[3][2] = 0.0f;
	transform[3][3] = 1.0f;
	return;
}

/************************************************************************/
/* 
if receive the TRANSFORM msg,copy the newest TRANSFORM msg to transform
*/
/************************************************************************/
const bool TransformListener::GetNewestTransform(TRANSFORM &transform)
{
	m_mtuTransform.lock();
	if (m_vecTransform.size() == 0)
	{
		m_mtuTransform.unlock();
		return false;
	}

	memcpy(&transform, &(m_vecTransform.data()[m_vecTransform.size() - 1]), sizeof(TRANSFORM));
	m_mtuTransform.unlock();
	return true;
}

const bool TransformListener::GetLatestTimeStamp(unsigned long long& timestamp)
{
	TRANSFORM stTransform;
	if (this->GetNewestTransform(stTransform))
	{
		timestamp = stTransform.nRTKTimeStamp;//.stHeader.nTimeStamp;
		//timestamp = stTransform.stHeader.nTimeStamp;
		return true;
	}
	else
	{
		return false;
	}
}
