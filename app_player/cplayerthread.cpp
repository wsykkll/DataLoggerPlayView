#include "cplayerthread.h"

CPlayerThread::CPlayerThread(QObject *parent) : QObject(parent),
    m_bTerminateThreads(true),
    m_fReplaySpeed(1.0),
	m_bFileLoaded(false),
    m_nCurrentEventTimeStamp(0)
{
	//m_msgEndFlag.bEnded = 0;
    m_stAsyncQueue = g_async_queue_new();
	//set a timer to update the MSG UI every 200ms
    m_pUIUpdateTimer = new QTimer;
    connect(m_pUIUpdateTimer, SIGNAL(timeout()), this, SLOT(OnUpdateUI()));
    m_pUIUpdateTimer->start(200);

    m_pLCM = new lcm::LCM("udpm://239.255.76.67:7667?ttl=0");
    if(!m_pLCM->good())
    {
        QMessageBox msgBox;
        msgBox.setText(QString("Could not initialize communication, please check the Ethernet connection!"));
        msgBox.exec();
        delete m_pLCM;
        exit(-1);
    }
	m_pLCM->subscribe("Command", &CPlayerThread::CallbackCmdInfo, this);
}

CPlayerThread::~CPlayerThread()
{
	g_async_queue_unref(m_stAsyncQueue);
}

void CPlayerThread::run()
{
	while (0 == m_pLCM->handle())
	{

	}
}

void CPlayerThread::CallbackCmdInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName)
{
	ControlCmd_t tmp_control;
	tmp_control.decode(recvBuf->data, 0, recvBuf->data_size);
	if (m_bFileLoaded)
	{
		switch (tmp_control.control_cmd)
		{
		case 1:
			
			SetReplayMode(PLAY);
			break;
		case 2:
			SetReplayMode(PAUSE);
			break;
		case 3:
			SetReplayMode(NEXTIMG);
			break;
		case 4:
			SetSeekToTimeStamp(m_nCurrentEventTimeStamp - 50000);
			//GoToTheListTime(m_pPlayerThread->m_listIMGtimestamp);
			SetReplayMode(PREVIOUSIMG);
			break;
		case 5:
			SetSeekToTimeStamp(tmp_control.header.nTimeStamp - 10000);
			SetReplayMode(NEXTIMG);
			Sleep(500);
			break;
		default:
			break;
		}
	}
}

void CPlayerThread::ReadLogFileThread()
{
    lcm::LogEvent* pLogEvent;
    long long int seekToTimeStamp = 0;
    while(!GetTerminateThreadsStatus())
    {
        //check if seek to timestamp needed;
        seekToTimeStamp = GetSeekToTimeStamp();
        if(0 != seekToTimeStamp)
        {
            //seek to timestamp;
            SeekToTimeStamp(seekToTimeStamp);
        }

        //if queue size < maximum, read data and write to queue; else, sleep for 2 ms;
        if(g_async_queue_length(m_stAsyncQueue) < GetMaxQueueSize())
        {
            //read log event from the file;
            pLogEvent = const_cast<lcm::LogEvent*>(m_stLogFile.pLcmLogFile->readNextEvent());
            if(NULL != pLogEvent)
            {
                lcm::LogEvent* tempLogEvent = new lcm::LogEvent;
                tempLogEvent->channel = pLogEvent->channel;
                tempLogEvent->timestamp = pLogEvent->timestamp;
                tempLogEvent->datalen = pLogEvent->datalen;
                tempLogEvent->eventnum = pLogEvent->eventnum;
                tempLogEvent->data = new char[pLogEvent->datalen];
                memcpy(tempLogEvent->data, pLogEvent->data, tempLogEvent->datalen);

                //push to queue;
                g_async_queue_push(m_stAsyncQueue, tempLogEvent);
            }
            else//no more event in the file, sleep to wait for seek to new time stamp;
            {
                //if loop, reset seektotimestamp; else, just sleep;
                if(GetLoop())
                {
                    if(g_async_queue_length(m_stAsyncQueue)<=0)
                    {
                        //reset to start timestamp;
                        SeekToTimeStamp(m_stLogFile.nStartTimeStamp);
                    }
                    else//reset
                    {
                        Sleep(10);//wait until all the data in the queue has been popped;
                    }
                }
                else
                {
                    Sleep(10);
                }
            }
        }
        else
        {
            Sleep(2);//sleep 2ms;
        }
    }
}

void CPlayerThread::PublishEventsThread()
{
    REPLAY_MODE replayMode;
    while(!GetTerminateThreadsStatus())
    {
        replayMode = GetReplayMode();
        if(PLAY == replayMode)//PLAY mode;
        {
            //get new logevent from the queue;
            if(!GetLogEvent())
            {
                Sleep(2);
                continue;
            }
			PlayProcess();
        }

        if(PAUSE == replayMode)//PAUSE mode;
        {
            //sleep for 2ms;
            Sleep(2);
        }

        if(STEP == replayMode)//STEP mode;
        {
            //get new logevent from the queue;
            if(GetLogEvent())
            {
                //publish the event;
                PublishCurrentEvent();
            }
            //switch to PAUSE mode;
            SetReplayMode(PAUSE);
        }

		if (NEXTRTK == replayMode)
		{
			if (!GetLogEvent())
			{
				Sleep(2);
				continue;
			}
			else if (m_pCurrentLogEvent->channel == "GPSFront" || m_pCurrentLogEvent->channel == "RTK_INFO")
			{
				PublishCurrentEvent();
				SetReplayMode(PAUSE);
				continue;
			}
			PlayProcess();
		}

		if (NEXTIMG == replayMode)
		{
			if (!GetLogEvent())
			{
				Sleep(2);
				continue;
			}
			if (m_pCurrentLogEvent->channel == "Video" || m_pCurrentLogEvent->channel == "PRESCAN_IMG")
			{
				PublishCurrentEvent();
				SetReplayMode(PAUSE);
				continue;
			}
			PlayProcess();
		}
		if (PREVIOUSIMG == replayMode)
		{
			if (!GetLogEvent())
			{
				Sleep(2);
				continue;
			}
			if (m_pCurrentLogEvent->channel == "Video")
			{
				PublishCurrentEvent();
				SetReplayMode(PAUSE);
				continue;
			}
			PlayProcess();
		}
		if (PREVIOUSRTK == replayMode)
		{
			if (!GetLogEvent())
			{
				Sleep(2);
				continue;
			}
			if (m_pCurrentLogEvent->channel == "GPSFront")
			{
				PublishCurrentEvent();
				SetReplayMode(PAUSE);
				continue;
			}
			PlayProcess();
		}
    }
}

void CPlayerThread::PlayProcess()
{
	//delay;
	if (!GetQueueCleared())//if queue is not cleared;
	{
		//get the time to delay;
		int nTimeToDelay = (m_nCurrentEventTimeStamp - m_nLastEventTimeStamp) / GetReplaySpeed();
		//delay the specified time;
		PreciseDelay(nTimeToDelay, false);
	}
	else
	{
		//set last time stamp;
		SetQueueCleared(false);
		PreciseDelay(0, true);
	}
	//publish the event;
	PublishCurrentEvent();
}

void CPlayerThread::SetTerminateThreadsStatus(bool status)
{
    m_lockTerminateThreads.lockForWrite();
    m_bTerminateThreads = status;
    m_lockTerminateThreads.unlock();
    return;
}

bool CPlayerThread::GetTerminateThreadsStatus()
{
    bool status = false;
    m_lockTerminateThreads.lockForRead();
    status = m_bTerminateThreads;
    m_lockTerminateThreads.unlock();
    return status;
}

/************************************************************************/
/* 
after load log file, update the seek timestamp to start timestamp
*/
/************************************************************************/
inline long long int CPlayerThread::GetSeekToTimeStamp()
{
    bool updated = false;
    long long int stamp = 0;

    m_stLogFile.lockSeekToStamp.lockForWrite();
    updated = m_stLogFile.bSeekToTimeStampUpdated;
    m_stLogFile.bSeekToTimeStampUpdated = false;
    stamp = m_stLogFile.nSeekToTimeStamp;
    m_stLogFile.lockSeekToStamp.unlock();

    //if seek to timestamp updated, return new stamp;else, return 0;
    return updated ? stamp : 0;
}

/************************************************************************/
/* 
Set the seek time with the slider
*/
/************************************************************************/
void CPlayerThread::SetSeekToTimeStamp(long long int stamp)
{
    m_stLogFile.lockSeekToStamp.lockForWrite();
    m_stLogFile.bSeekToTimeStampUpdated = true;
    m_stLogFile.nSeekToTimeStamp = stamp;
    m_stLogFile.lockSeekToStamp.unlock();

    return;
}

REPLAY_MODE CPlayerThread::GetReplayMode()
{
    REPLAY_MODE mode;
    m_lockReplayMode.lockForRead();
    mode = m_eReplayMode;
    m_lockReplayMode.unlock();
    return mode;
}

void CPlayerThread::SetReplayMode(REPLAY_MODE mode)
{
    m_lockReplayMode.lockForWrite();
    m_eReplayMode = mode;
    m_lockReplayMode.unlock();
    return;
}

void CPlayerThread::SetReplaySpeed(float speed)
{
    m_lockReplaySpeed.lockForWrite();
    m_fReplaySpeed = speed;
    m_lockReplaySpeed.unlock();

    SetMaxQueueSize(m_stLogFile.nBaseQueueSize/speed);
    return;
}

float CPlayerThread::GetReplaySpeed()
{
    float speed = 1.0;
    m_lockReplaySpeed.lockForRead();
    speed = m_fReplaySpeed;
    m_lockReplaySpeed.unlock();
    return speed;
}

int CPlayerThread::GetMaxQueueSize()
{
    int size = 100;
    m_stLogFile.lockQueueSize.lockForRead();
    size = m_stLogFile.nMaxQueueSize;
    m_stLogFile.lockQueueSize.unlock();
    return size;
}

void CPlayerThread::SetMaxQueueSize(int size)
{
    if(size<20)
    {
        size = 20;
    }

    if(size>2000)
    {
        size = 2000;
    }

    m_stLogFile.lockQueueSize.lockForWrite();
    m_stLogFile.nMaxQueueSize = size;
    m_stLogFile.lockQueueSize.unlock();
}

bool CPlayerThread::GetLoop()
{
    bool loop = false;
    m_stLogFile.lockLoop.lockForRead();
    loop = m_stLogFile.bLoop;
    m_stLogFile.lockLoop.unlock();
    return loop;
}

void CPlayerThread::SetLoop(bool loop)
{
    m_stLogFile.lockLoop.lockForWrite();
    m_stLogFile.bLoop = loop;
    m_stLogFile.lockLoop.unlock();
}

/************************************************************************/
/* 
go to the seek time for log file
*/
/************************************************************************/
bool CPlayerThread::SeekToTimeStamp(long long stamp)
{
    //clear queue;
	//DWORD start, stop;
	//start = timeGetTime();
	//printf("Start Time:%ld\n", start);
	ClearQueue();


    //seek the file to stamp;
	int tt = m_stLogFile.pLcmLogFile->seekToTimestamp(stamp);
	//stop = timeGetTime();
	//printf("Stop Time:%ld\n", stop);
	//printf("Using Time:%ld\n", (stop - start));
	if (tt<0)
    {
		return false;
    }
	return true;
    //m_stLogFile.pLcmLogFile->seekToTimestamp(stamp);
}

/************************************************************************/
/*
clear the async queue before load the log file
*/
/************************************************************************/
void CPlayerThread::ClearQueue()
{
    while(1)
    {
        lcm::LogEvent* logEvent = (lcm::LogEvent*)g_async_queue_try_pop(m_stAsyncQueue);
        if(NULL != logEvent)
        {
            delete logEvent->data;
            delete logEvent;
        }
        else
        {
            break;
        }
    }
    SetQueueCleared(true);
}

void CPlayerThread::SetQueueCleared(bool reset)
{
    m_lockQueueCleared.lockForWrite();
    m_bQueueCleared = reset;
    m_lockQueueCleared.unlock();
}

bool CPlayerThread::GetQueueCleared()
{
    bool cleared = false;
    m_lockQueueCleared.lockForRead();
    cleared = m_bQueueCleared;
    m_lockQueueCleared.unlock();
    return cleared;
}

/************************************************************************/
/* 
achieve a function as usleep, more precise in Linux with "select"
*/
/************************************************************************/
void CPlayerThread::PreciseDelay(int microseconds, bool reset)
{
	static struct timeval stTimeToDelay;
	static long long int nLastTimeStamp = GetLocalTimeStampInMicroSec();
	if (reset)
	{
		nLastTimeStamp = GetLocalTimeStampInMicroSec();
	}
	long long int nCurrentTimeStamp = GetLocalTimeStampInMicroSec();
	int nMicroSecondsToDelay = microseconds - (nCurrentTimeStamp - nLastTimeStamp);
	if (nMicroSecondsToDelay > 0)
	{
		MicroSecondSleep(nMicroSecondsToDelay);
		//stTimeToDelay.tv_sec = nMicroSecondsToDelay / 1000000.0f;
		//stTimeToDelay.tv_usec = nMicroSecondsToDelay % 1000000;
		//select(0, null, null, null, &sttimetodelay); 
		//Sleep(1);
	}
	nLastTimeStamp = GetLocalTimeStampInMicroSec();
	return;
}

/************************************************************************/
/* 
a microseconds level delay funtion in Windows
*/
/************************************************************************/
inline void CPlayerThread::MicroSecondSleep(int delayTime)
{
	LARGE_INTEGER Freq = { 0 };
	//if the PC doesn't support high accuracy timer
	if (!QueryPerformanceFrequency(&Freq))
	{
		return Sleep(0);
	}

	LARGE_INTEGER tcStart = { 0 };
	QueryPerformanceCounter(&tcStart);
	LARGE_INTEGER tcEnd = { 0 };
	while (1)
	{
		QueryPerformanceCounter(&tcEnd);
		double time = (((tcEnd.QuadPart - tcStart.QuadPart) * 1000000) / (double)Freq.QuadPart);
		if (time >= delayTime)
		{
			break;
		}
	}
}

bool CPlayerThread::GetLogEvent()
{
    m_pCurrentLogEvent = (lcm::LogEvent*)g_async_queue_try_pop(m_stAsyncQueue);
    if(m_pCurrentLogEvent == NULL)
    {
        return false;
    }
    else
    {
        m_nCurrentEventTimeStamp = m_pCurrentLogEvent->timestamp;
    }

    return true;
}

bool CPlayerThread::GetIMGLogEvent()
{
	while (true)
	{
		m_pCurrentLogEvent = (lcm::LogEvent*)g_async_queue_try_pop(m_stAsyncQueue);
		if (m_pCurrentLogEvent->channel == "Video")
		{
			m_nCurrentEventTimeStamp = m_pCurrentLogEvent->timestamp;
			break;
		}
	}
	return true;
}

bool CPlayerThread::GetRTKLogEvent()
{
	while (true)
	{
		m_pCurrentLogEvent = (lcm::LogEvent*)g_async_queue_try_pop(m_stAsyncQueue);
		if (m_pCurrentLogEvent->channel == "GPSFront")
		{
			m_nCurrentEventTimeStamp = m_pCurrentLogEvent->timestamp;
			break;
		}
	}
	return true;
}


void CPlayerThread::PublishCurrentEvent()
{
    m_nLastEventTimeStamp = m_nCurrentEventTimeStamp;

    //update channel info;
    int index = GetChannelIndex(QString::fromStdString(m_pCurrentLogEvent->channel));
    m_listChannels[index].nCurrentMsgSize = m_pCurrentLogEvent->datalen;
    m_listChannels[index].nCurrentTimeStamp = m_pCurrentLogEvent->timestamp;
    m_listChannels[index].nMsgCount++;
    if(m_listChannels[index].nMsgCount%10==0)
    {
        m_listChannels[index].nDeltaTimeStamp = m_listChannels[index].nCurrentTimeStamp-m_listChannels[index].nPreviousTimeStamp;
        m_listChannels[index].nPreviousTimeStamp = m_listChannels[index].nCurrentTimeStamp;
    }

    if(m_listChannels[index].bBroadCast)
    {
        m_pLCM->publish(m_pCurrentLogEvent->channel, m_pCurrentLogEvent->data, m_pCurrentLogEvent->datalen);
		if (m_listChannels[index].strChannelName == "GPSFront")
		{
			for (QList<QPair<int64_t, METGPSInfo_Lcm> >::iterator it = m_listHeading.begin(); it != m_listHeading.end(); it++)
			{

				if ((it->first) == m_pCurrentLogEvent->timestamp)
				{
					m_msgNextPosture.nTimeStamp = (it + 1)->second.header.nTimeStamp;
					m_msgNextPosture.dLatitude = ((it + 1)->second.GGA_dwLat) / 100;
					m_msgNextPosture.dLongitude = ((it + 1)->second.GGA_dwLon) / 100;
					//m_msgNextHeading.nTimeStamp = (it + 1)->second.header.nTimeStamp;
					m_msgNextPosture.dHeading = (it + 1)->second.TRA_dwHeading;
					m_pLCM->publish("NEXTHEADING", &m_msgNextPosture);
					break;
				}
			}
		}
    }

    //emit ShowStatusMessage(QString::fromStdString(m_pCurrentLogEvent->channel)+QString::number(m_pCurrentLogEvent->timestamp));

    delete m_pCurrentLogEvent->data;
    delete m_pCurrentLogEvent;
}

bool CPlayerThread::CheckFile(QString strFileName)
{
    //open a tempory file verify and traverse the file;
    lcm::LogFile* logFile = new lcm::LogFile(strFileName.toStdString(), "r");
    if(!logFile->good())
    {
        delete logFile;
        return false;
    }

    //try to get one msg to ensure the file is not empty;
    lcm::LogEvent* logEvent;
    logEvent = const_cast<lcm::LogEvent*>(logFile->readNextEvent());
    if(NULL == logEvent)
    {
        delete logFile;
        return false;
    }

    return true;
}

/************************************************************************/
/* 
load the log file before replay; load all the message 
*/
/************************************************************************/
void CPlayerThread::LoadFile(QString strFileName)
{
    //clear queues;
    ClearQueue();

    //clear all channels;
    m_listChannels.clear();

    //update lcm file info;
    if(m_stLogFile.pLcmLogFile != NULL)
    {
        delete m_stLogFile.pLcmLogFile;
    }

    m_stLogFile.pLcmLogFile = new lcm::LogFile(strFileName.toStdString(), "r");

    lcm::LogEvent* logEvent;
    logEvent = const_cast<lcm::LogEvent*>(m_stLogFile.pLcmLogFile->readNextEvent());
    m_stLogFile.nStartTimeStamp = logEvent->timestamp;
    m_stLogFile.nSeekToTimeStamp = m_stLogFile.nStartTimeStamp;
    m_stLogFile.bSeekToTimeStampUpdated = true;
    m_stLogFile.nMsgNumber = 0;
    m_nCurrentEventTimeStamp = m_stLogFile.nStartTimeStamp;

    int index = 0;
    //traverse the file to update channel info;
    while(1)
    {
		QPair<int64_t, METGPSInfo_Lcm> tmp_msg;
		m_stLogFile.nStopTimeStamp = logEvent->timestamp;
		m_stLogFile.nMsgNumber++;

		index = GetChannelIndex(QString::fromStdString(logEvent->channel));
		//update channel info;
		if (!m_listChannels[index].bFirstMsg)
		{
			m_listChannels[index].nLastTimeStamp = logEvent->timestamp;
			m_listChannels[index].nMsgSize += logEvent->datalen;
			m_listChannels[index].nMsgNumber++;
		}
		else
		{
			m_listChannels[index].strChannelName = QString::fromStdString(logEvent->channel);
			m_listChannels[index].nFirstTimeStamp = logEvent->timestamp;
			m_listChannels[index].nCurrentTimeStamp = logEvent->timestamp;
			m_listChannels[index].nPreviousTimeStamp = logEvent->timestamp;
			m_listChannels[index].nLastTimeStamp = logEvent->timestamp;
			m_listChannels[index].nCurrentMsgSize = logEvent->datalen;
			m_listChannels[index].nMsgSize += logEvent->datalen;

			m_listChannels[index].nMsgNumber++;
			m_listChannels[index].bFirstMsg = false;
		}
		m_listChannels[index].timestamplist.append(logEvent->timestamp);
		QString tmp_str = QString::fromStdString(logEvent->channel);
		if (tmp_str == "GPSFront")
		{
			m_msgRTKInfo.decode(logEvent->data, 0, logEvent->datalen);
			tmp_msg.first = logEvent->timestamp;
			tmp_msg.second = m_msgRTKInfo;
			//char fileName[100] = { '\0' };
			//sprintf_s(fileName, "..LogLanelGPS.txt");
			//m_fLaneMarkPointFile.open(fileName, ios::app);
			//m_fLaneMarkPointFile << setiosflags(ios::fixed) << setprecision(10) << m_msgRTKInfo.GGA_dwLat << "\t";
			//m_fLaneMarkPointFile << setiosflags(ios::fixed) << setprecision(10) << m_msgRTKInfo.GGA_dwLon << "\n";
			//m_fLaneMarkPointFile.close();
			m_listHeading.append(tmp_msg);
		}
		logEvent = const_cast<lcm::LogEvent*>(m_stLogFile.pLcmLogFile->readNextEvent());
		if (logEvent == NULL)
		{
			m_listHeading.append(tmp_msg);
			break;
		}
    }

	QList<CHANNEL_INFO>::iterator iter = m_listChannels.begin();
	for (; iter != m_listChannels.end();iter++)
	{
		if (iter->strChannelName == "Video")
		{
			m_listIMGtimestamp = iter->timestamplist;
		}
		if (iter->strChannelName == "GPSFront")
		{
			m_listRTKtimestamp = iter->timestamplist;
		}
	}

	//m_stLogFile.pLcmLogFile = new lcm::LogFile(strFileName.toStdString(), "r");
	//logEvent = const_cast<lcm::LogEvent*>(m_stLogFile.pLcmLogFile->readNextEvent());


    m_stLogFile.nBaseQueueSize = 2*m_stLogFile.nMsgNumber*1000000.0/(m_stLogFile.nStopTimeStamp-m_stLogFile.nStartTimeStamp);
    SetMaxQueueSize(m_stLogFile.nBaseQueueSize);

    for(int i = 0; i<m_listChannels.size(); i++)
    {
		//calculate the period
        m_listChannels[i].fAvgPeriod = (m_listChannels[i].nLastTimeStamp-m_listChannels[i].nFirstTimeStamp)/(m_listChannels[i].nMsgNumber*1000000.0);
		//calculate the frequency
        if(m_listChannels[i].nMsgNumber == 1)
        {
            m_listChannels[i].fAvgFrequency = 0.0;
        }
        else
        {
            m_listChannels[i].fAvgFrequency = m_listChannels[i].nMsgNumber*1000000.0/(m_listChannels[i].nLastTimeStamp-m_listChannels[i].nFirstTimeStamp);
        }

        m_listChannels[i].nAvgMsgSize = double(m_listChannels[i].nMsgSize)/m_listChannels[i].nMsgNumber;
        m_listChannels[i].nPreviousTimeStamp = m_listChannels[i].nFirstTimeStamp;
        m_listChannels[i].nCurrentTimeStamp = m_listChannels[i].nFirstTimeStamp;
    }
	m_bFileLoaded = true;
}

int CPlayerThread::GetChannelIndex(QString strChannelName)
{
    while(1)
    {
        int i = 0;
        for(i=0; i<m_listChannels.size(); i++)
        {
            if(QString::compare(m_listChannels[i].strChannelName, strChannelName) == 0)
            {
                return i;
            }
        }
        CHANNEL_INFO newChannel;
        newChannel.strChannelName = strChannelName;
        m_listChannels.append(newChannel);
        return i;
    }
}

void CPlayerThread::OnUpdateUI()
{
    /*@todo lock to protect data here*/
    emit UpdateCurrentTimeStamp(m_nCurrentEventTimeStamp);
    for(int i=0; i<m_listChannels.size(); i++)
    {
        if(m_listChannels[i].nDeltaTimeStamp != 0)
        {
            m_listChannels[i].fPeriod = m_listChannels[i].nDeltaTimeStamp/10000000.0;
            m_listChannels[i].fFrequency = 10000000.0/m_listChannels[i].nDeltaTimeStamp;
        }
        else
        {
            m_listChannels[i].fPeriod = 0.0;
            m_listChannels[i].fFrequency = 0.0;
        }
        emit UpdateTableRow(i, m_listChannels[i]);
    }
}

void CPlayerThread::OnUpdateChannelBroadCast(int index, bool broadcast)
{
    m_listChannels[index].bBroadCast = broadcast;
}
