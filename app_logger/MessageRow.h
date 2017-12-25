#pragma once
#include <qobject.h>
#include <qtablewidget.h>
#include "message.h"
#include "global.hpp"

class CMessageRow :
	public QObject
{
	Q_OBJECT
public:
	explicit CMessageRow(QString strChannelName, QObject *parent = 0);
	~CMessageRow();

	QString m_QStrChannelName;
	long long int m_nMsgTimeStamp;//the newest message timestamp, not used right now;
	long long int m_nRecvTimeStamp;//the time when the newest message is received;
	long long int m_nMsgSize;
	int m_nMsgCounter;
	float m_fFrequency;
	float m_fPeriod;
	long long int m_nLastTimeStamp;
	long long int m_nCurrentTimeStamp;

	void UpdateMsg(MESSAGE msg);
signals:

	public slots :
};

