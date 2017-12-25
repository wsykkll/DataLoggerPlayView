struct RTK
{
	HEADER stHeader;
	int64_t nGPSTimeStamp;
	double dLatitude;
	double dLongitude;
    float fAltitude;
	float fVelocity;
    float fVelNorth;
    float fVelWest;
    float fHeading;
	float fPosX;
	float fPosY;
    int8_t nNavStatus;
}