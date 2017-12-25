struct TRANSFORM
{
  HEADER stHeader;
  byte bReseted;//if the transform is reseted, 0x01; else, 0x00;
  int64_t nINSTimeStamp;//the timestamp of ins message, in micro-seconds; the same as INERTIAL.stHeader.nTimeStamp, SPATIAL_FOG.stHeader.nTimeStamp;
  
  float gfTransformVehicle2World[4][4];//row major;
  float gfVehiclePoseInWorld[6];//x (in meters), y (in meters), z (in meters), yaw (in radian), pitch (in radian), roll (in radian);
  
  float gfTransformVelodyne2Vehicle[4][4];
  float gfVelodynePoseInVehicle[6];//x (in meters), y (in meters), z (in meters), yaw (in radian), pitch (in radian), roll (in radian);
  
  float gfTransformESR2Vehicle[4][4];
  float gfESRPoseInVehicle[6];//x (in meters), y (in meters), z (in meters), yaw (in radian), pitch (in radian), roll (in radian);
  
  float gfTransformMobileye2Vehicle[4][4];
  float gfMobileyePoseInVehicle[6];//x (in meters), y (in meters), z (in meters), yaw (in radian), pitch (in radian), roll (in radian);
  
  float gfTransformFrontLux2Vehicle[4][4];
  float gfFrontLuxPoseInVehicle[6];//x (in meters), y (in meters), z (in meters), yaw (in radian), pitch (in radian), roll (in radian);
  
  float gfTransformLeftLux2Vehicle[4][4];
  float gfLeftLuxPoseInVehicle[6];//x (in meters), y (in meters), z (in meters), yaw (in radian), pitch (in radian), roll (in radian);
  
  float gfTransformBackLux2Vehicle[4][4];
  float gfBackLuxPoseInVehicle[6];//x (in meters), y (in meters), z (in meters), yaw (in radian), pitch (in radian), roll (in radian);
  
  float gfTransformRightLux2Vehicle[4][4];
  float gfRightLuxPoseInVehicle[6];//x (in meters), y (in meters), z (in meters), yaw (in radian), pitch (in radian), roll (in radian);
  
  float gfTransformIBEO2Vehicle[4][4];
  float gfIBEOPoseInVehicle[6];//x (in meters), y (in meters), z (in meters), yaw (in radian), pitch (in radian), roll (in radian);
  
  float gfTransformFrontMWR2Vehicle[4][4];
  float gfFrontMWRPoseInVehicle[6];// x (in meters), y (in meters), z (in meters), yaw (in radian), pitch (in radian), roll (in radian);
  
  float gfTransformLeftMWR2Vehicle[4][4];
  float gfLeftMWRPoseInVehicle[6];//x (in meters), y (in meters), z (in meters), yaw (in radian), pitch (in radian), roll (in radian);
  
  float gfTransformRightMWR2Vehicle[4][4];
  float gfRightMWRPoseInVehicle[6];//x (in meters), y (in meters), z (in meters), yaw (in radian), pitch (in radian), roll (in radian);
  
  float gfVehicleVelocityInWorld[3];// vehicle velocity in world coordinate, in m/s., vx, vy, vz.
  
  boolean bVCUDRValid;
  float gfTransformVehicle2WorldVCUDR[4][4];//row major;
  float gfVehiclePoseInWorldVCUDR[6];//x (in meters), y (in meters), z (in meters), yaw (in radian), pitch (in radian), roll (in radian);
  float gfVehicleVelocityInWorldVCUDR[3];// vehicle velocity in world coordinate, in m/s., vx, vy, vz.
}