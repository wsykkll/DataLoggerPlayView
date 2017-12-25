struct PRESCAN_LINE
{
	boolean bValid;
	float fLength;
	float fX0;
	float fX1;
	float fX2;
	float fX3;
	float fY0;
	float fY1;
	float fY2;
	float fY3;
	int8_t nLineLabel;
	int8_t nGroupID;
}

struct PRESCAN_LANES
{
	HEADER stHeader;
	PRESCAN_LINE gLines[20];
}