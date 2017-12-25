#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdio.h>
#include <string>
#include "global.hpp"
struct MESSAGE
{
	std::string strChannelName;
	long long int nMsgTimeStamp;//micro second;
	long long int nRecvTimeStamp;//micro second;
	long long int nMsgSize;//in bytes;
};
Q_DECLARE_METATYPE(MESSAGE)

struct RECORD_STATUS
{
	float fBandWidth;
	float fBytesWritten;
	float fBytesToWrite;
};
Q_DECLARE_METATYPE(RECORD_STATUS)
#endif // MESSAGE_H