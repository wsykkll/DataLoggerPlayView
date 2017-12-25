struct VCU_VEHILCE_INFO
{
  HEADER stHeader;
  float fSteeringAngle;//in rad, counterclockwise 0~+, clockwise 0~-;
  float fSpeed;//in m/s;
  float fYawRate;//in rad/s;
  float fFrontLeftWheelSpeed;//in m/s;
  float fFrontRightWheelSpeed;//in m/s;
  float fRearLeftWheelSpeed;//in m/s;
  float fRearRightWheelSpeed;//in m/s;
}
