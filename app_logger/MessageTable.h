#pragma once
#include "qobject.h"
#include "MessageRow.h"

class CMessageTable :
	public QObject
{
	Q_OBJECT
public:
	explicit CMessageTable(QObject *parent = 0);
	~CMessageTable();

	QList<CMessageRow*>m_qListRowWidgets;
	int m_nRowWidgetsNum;

	int GetRowWidgetsNum();
	int GetChannelIndexByName(QString str);
signals:
	void ShowStatusMessage(QString);

	public slots:
	void OnMessageReceived(MESSAGE msg);
};

