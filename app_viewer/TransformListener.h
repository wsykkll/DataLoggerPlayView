#pragma once
#include "global.hpp"
#include "TRANSFORM.hpp"

class TransformListener
{
public:
	TransformListener();
	~TransformListener();

	void PushbackNewTransform(const TRANSFORM* transform);
	const bool GetStampedTransform(const unsigned long long timstamp, TRANSFORM& transform);
	const bool GetNewestTransform(TRANSFORM& transform);
	const bool GetLatestTimeStamp(unsigned long long& timestamp);

private:
	mutex m_mtuTransform;
	std::vector<TRANSFORM> m_vecTransform;
	void CopyTransform(const unsigned int src, TRANSFORM& dest) const;
	void BinarySearch(const unsigned long long timestamp, unsigned int& leftIndex, unsigned int& rightIndex);
	void InterpolateTransform(const unsigned long long timestamp, const unsigned int leftIndex, const unsigned int rightIndex, TRANSFORM& transform) const;
	void CalculateTransformMatrix(const float x, const float y, const float z, const float yaw, const float pitch, const float roll, float(&transform)[4][4]) const;
};

