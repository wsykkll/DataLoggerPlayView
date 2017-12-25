#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include "ui_mainwindow.h"
#include "message.h"
#include "MessageTable.h"
#include "MessageThread.h"
#include "global.hpp"

//#include <boost/thread/thread.hpp>

//using namespace boost;

//namespace Ui{
//	class MainWindow;
//}
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow ui;
	CMessageTable m_stMessageTable;
	CMessageThread* m_pMessageThread;
	QTimer m_qTimerUpdateTable;//timer to update table;

	void InitializeUi();
	void InitializeSignalsAndSlots();
	void InitializeLCM();

signals:
	void UpdateRecordList(QString str, bool record);
	void SwitchRecord(bool);

	public slots:
	void OnTimerUpdateTable();

	void OnStartRecord();
	void OnStopRecord();
	void OnLogFinished();
	void OnSelectAll();
	void OnInvertSelect();

	void OnShowStatusMessage(QString msg);
	void OnTableItemClicked(int x, int y);

	void OnShowLogFileName(QString strFileName);
	void OnUpdateRecordStatus(RECORD_STATUS recordStatus);
};

#endif // MAINWINDOW_H
