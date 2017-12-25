#ifndef CHANNELINFO_H
#define CHANNELINFO_H
#include "global.hpp"
#include <QString>

struct CHANNEL_INFO
{
    QString strChannelName;

    long long int nFirstTimeStamp;
    long long int nLastTimeStamp;
    long long int nCurrentTimeStamp;
    long long int nPreviousTimeStamp;
    long long int nDeltaTimeStamp;

    float fAvgFrequency;
    float fFrequency;

    float fAvgPeriod;
    float fPeriod;

    int nAvgMsgSize;
    long long int nMsgSize;
    int nCurrentMsgSize;

    long long int nMsgCount;
    long long int nMsgNumber;

    bool bFirstMsg;
    bool bBroadCast;

	QList<int64_t> timestamplist;

    CHANNEL_INFO()//default constructor;
    {
        bFirstMsg = true;
        bBroadCast = true;

        nFirstTimeStamp = 0;
        nLastTimeStamp = 0;
        nCurrentTimeStamp = 0;
        nPreviousTimeStamp = 0;
        nDeltaTimeStamp = 0;

        fAvgFrequency = 0.0;
        fFrequency = 0.0;

        fAvgPeriod = 0.0;
        fPeriod = 0.0;

        nAvgMsgSize = 0.0;
        nMsgSize = 0.0;
        nCurrentMsgSize = 0.0;

        nMsgNumber = 0;
        nMsgCount = 0;
    }
};
Q_DECLARE_METATYPE(CHANNEL_INFO)

enum REPLAY_MODE{PLAY, STEP, PAUSE, FINISHED, TERMINATED, NEXTRTK, NEXTIMG,PREVIOUSRTK,PREVIOUSIMG};
#endif // CHANNELINFO_H

