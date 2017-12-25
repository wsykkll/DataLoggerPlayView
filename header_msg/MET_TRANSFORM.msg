struct TRANSFORM
{
  HEADER stHeader;
  byte bReseted;//if the transform is reseted, 0x01; else, 0x00;
  int64_t nRTKTimeStamp;//the timestamp of ins message, in micro-seconds; the same as INERTIAL.stHeader.nTimeStamp, SPATIAL_FOG.stHeader.nTimeStamp;
  
  float gfTransformVehicle2World[4][4];//row major;
  float gfVehiclePoseInWorld[6];//x (in meters), y (in meters), z (in meters), yaw (in radian), pitch (in radian), roll (in radian);
  
  float gfTransformCamera2Vehicle[4][4];
  float gfCameraPoseInVehicle[6];//x (in meters), y (in meters), z (in meters), yaw (in radian), pitch (in radian), roll (in radian);
  
  float gfTransformFrontMWR2Vehicle[4][4];
  float gfFrontMWRPoseInVehicle[6];// x (in meters), y (in meters), z (in meters), yaw (in radian), pitch (in radian), roll (in radian);
  
  float gfTransformLeftSRR2Vehicle[4][4];
  float gfLeftSRRPoseInVehicle[6];//x (in meters), y (in meters), z (in meters), yaw (in radian), pitch (in radian), roll (in radian);
  
  float gfTransformRightSRR2Vehicle[4][4];
  float gfRightSRRPoseInVehicle[6];//x (in meters), y (in meters), z (in meters), yaw (in radian), pitch (in radian), roll (in radian);
  
  float gfVehicleVelocityInWorld[3];// vehicle velocity in world coordinate, in m/s., vx, vy, vz.
  
  boolean bVCUDRValid;
  float gfTransformVehicle2WorldVCUDR[4][4];//row major;
  float gfVehiclePoseInWorldVCUDR[6];//x (in meters), y (in meters), z (in meters), yaw (in radian), pitch (in radian), roll (in radian);
  float gfVehicleVelocityInWorldVCUDR[3];// vehicle velocity in world coordinate, in m/s., vx, vy, vz.
}