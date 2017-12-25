#ifndef CPLAYERTHREAD_H
#define CPLAYERTHREAD_H

#include <QObject>
#include <QMessageBox>
#include <QList>
#include <QTimer>
#include <QPair>
#include <QReadWriteLock>
#include "global.hpp"
#include "channelinfo.h"
#include "ControlCmd_t.hpp"
#include "TrafficSignTable_t.hpp"
#include "METGPSInfo_Lcm.hpp"
//#include "HEADING.hpp"
#include "POSTURE.hpp"
using namespace std;

//#pragma comment( lib,"winmm.lib" )


class CPlayerThread : public QObject
{
    Q_OBJECT
public:
    explicit CPlayerThread(QObject *parent = 0);
	~CPlayerThread();

	void run();
	void CallbackCmdInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName);
	bool m_bFileLoaded;

    bool m_bTerminateThreads;
    QReadWriteLock m_lockTerminateThreads;

    float m_fReplaySpeed;
    QReadWriteLock m_lockReplaySpeed;

    QList<CHANNEL_INFO> m_listChannels;
	QList<int64_t> m_listIMGtimestamp;
	QList<int64_t> m_listRTKtimestamp;

	//QList<double> m_listHeading;
	QList<QPair<int64_t, METGPSInfo_Lcm> > m_listHeading;

	METGPSInfo_Lcm m_msgRTKInfo;

    struct ST_LOG_FILE
    {
        bool bSeekToTimeStampUpdated;
        long long int nSeekToTimeStamp;
        QReadWriteLock lockSeekToStamp;

        int nBaseQueueSize;//updated when new file is loaded;
        int nMaxQueueSize;//maxQueueSize = baseQueueSize/replaySpeed;
        QReadWriteLock lockQueueSize;

        bool bLoop;//set to true if loop is needed;
        QReadWriteLock lockLoop;

        lcm::LogFile* pLcmLogFile;

        long long int nStartTimeStamp;
        long long int nStopTimeStamp;

        long long int nMsgNumber;//how many message in the file;

        ST_LOG_FILE()
        {
            bSeekToTimeStampUpdated = false;
            nSeekToTimeStamp = 0;

            nBaseQueueSize = 10;
            nMaxQueueSize = 10;

            nStartTimeStamp = 0;
            nStopTimeStamp = 0;
            bLoop = false;

            nMsgNumber = 0;
            pLcmLogFile = NULL;
        }
    };
    ST_LOG_FILE m_stLogFile;

    REPLAY_MODE m_eReplayMode;
    QReadWriteLock m_lockReplayMode;

    GAsyncQueue* m_stAsyncQueue;
	//ENDFLAG m_msgEndFlag;

    bool m_bQueueCleared;
    QReadWriteLock m_lockQueueCleared;

    long long int m_nLastEventTimeStamp;
    long long int m_nCurrentEventTimeStamp;

	TrafficSignTable_t m_msgTest;

    lcm::LogEvent* m_pCurrentLogEvent;

    QTimer* m_pUIUpdateTimer;

    lcm::LCM* m_pLCM;
    inline bool GetTerminateThreadsStatus();
    void SetTerminateThreadsStatus(bool status);

	//HEADING m_msgNextHeading;
	POSTURE m_msgNextPosture;

    void ReadLogFileThread();
    void PublishEventsThread();

    inline long long int GetSeekToTimeStamp();
    void SetSeekToTimeStamp(long long int stamp);

    void SetReplayMode(REPLAY_MODE mode);
    inline REPLAY_MODE GetReplayMode();

    inline float GetReplaySpeed();
    void SetReplaySpeed(float speed);

    inline int GetMaxQueueSize();
    void SetMaxQueueSize(int size);

    inline bool GetLoop();
    void SetLoop(bool loop);

    inline bool GetQueueCleared();
    inline void SetQueueCleared(bool reset);

	inline void MicroSecondSleep(int delayTime);

    bool SeekToTimeStamp(long long int stamp);
    void ClearQueue();
	void PreciseDelay(int microseconds, bool reset);

    bool GetLogEvent();
	bool GetIMGLogEvent();
	bool GetRTKLogEvent();

    void PublishCurrentEvent();
    bool CheckFile(QString strFileName);
    void LoadFile(QString strFileName);
    int GetChannelIndex(QString strChannelName);

	void PlayProcess();
	ofstream m_fLaneMarkPointFile;
public slots:
    void OnUpdateUI();
    void OnUpdateChannelBroadCast(int index, bool broadcast);
signals:
    void ShowStatusMessage(QString str);
    void UpdateCurrentTimeStamp(long long int timestamp);
    void UpdateTableRow(int index, CHANNEL_INFO channel);
};

#endif // CPLAYERTHREAD_H
