struct LaneMarkPoints
{
	double x;
	double y;
}

struct LaneMarkPointsList
{
	int16_t    num;
	LaneMarkPoints m_listLaneMarks[10000];
}