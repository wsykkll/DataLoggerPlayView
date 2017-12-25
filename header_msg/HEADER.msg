struct HEADER
{
  int64_t nTimeStamp;//global timestamp in microsecond;
  byte nFrameID;//frame id: get the id from lcm_channel.h enum COORINDATE_FRMAE_ID;
  int16_t nCounter;//(static_cast<unsigned int>(nCounter)+1)%65535;
}