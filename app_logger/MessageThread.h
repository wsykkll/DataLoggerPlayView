#pragma once
#include "qobject.h"
#include <QString>
#include <QList>
#include <QTimer>

#include "message.h"
#include "global.hpp"
#include "METRadarObject_Lcm.hpp"
//#include <mutex>

class CMessageThread :
	public QObject
{
	Q_OBJECT
public:
	explicit CMessageThread(QObject *parent = 0);
	~CMessageThread();

	void ReceiveMessage(const lcm::ReceiveBuffer *rbuf, const std::string &channel);
	void ReceiveThread();
	void WriteThread();

	lcm::LCM m_lcm;
	MESSAGE m_stMsg;
	lcm::LogFile* m_pLCMLogFile;
	bool m_bQueueData;//if true, queue data; else, stop queue data;
	bool m_bLogData;//if true, file is ok, write data to file;
	QList<QString> m_qListRecordChannelName;

	GAsyncQueue* m_stGAsyncQueue;
	inline bool IsRecorded(QString strChannelName);
	mutex m_mtuRecordStatus;
	GMutex* m_mutRecord;
	QTimer m_qTimer;

	long long int m_nQueueDataSize;
	long long int m_nDataWritten;
	long long int m_nLastDataWritten;

signals:
	void ShowStatusMessage(QString str);
	void ShowLogFileName(QString str);
	void MessageReceived(MESSAGE);//emit new signal when new message is received;
	void UpdateRecordStatus(RECORD_STATUS);
	void LogFinished();
	public slots:
	void OnUpdateRecordList(QString strChannelName, bool record);
	void OnSwitchRecord(bool);
	void OnTimerUpdateRecordStatus();
};

