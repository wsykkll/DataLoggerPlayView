#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//register struct to qt to enable the struct be transmitted by signals and slots;
	qRegisterMetaType<MESSAGE>("MESSAGE");
	qRegisterMetaType<RECORD_STATUS>("RECORD_STATUS");

	InitializeUi();//initialize ui, especially the table widgets;

	InitializeLCM();//initialize lcm;

	InitializeSignalsAndSlots();//initialize signals and slots;

	m_qTimerUpdateTable.start(200);//start the timer to update the table;
}


/**@brief destructor of the mainwindow;
 *
 *default destructor of the MainWindow;
 *@note
 */
MainWindow::~MainWindow()
{
	//delete ui;
}


/**@brief initialize the ui;
*
* initialize the ui, set up the talbe widgets, including the column size and the header column;
*@return void;
*@note
*/
void MainWindow::InitializeUi()
{
	ui.tableWidgetLCM->setHorizontalHeaderItem(0, new QTableWidgetItem(""));//set the header column;
	ui.tableWidgetLCM->setColumnWidth(0, 25);//set the column width;

	ui.tableWidgetLCM->setHorizontalHeaderItem(1, new QTableWidgetItem("Channel"));
	ui.tableWidgetLCM->setColumnWidth(1, 180);

	ui.tableWidgetLCM->setHorizontalHeaderItem(2, new QTableWidgetItem("MsgCount"));
	ui.tableWidgetLCM->setColumnWidth(2, 120);

	ui.tableWidgetLCM->setHorizontalHeaderItem(3, new QTableWidgetItem("MsgSize(kB)"));
	ui.tableWidgetLCM->setColumnWidth(3, 120);

	ui.tableWidgetLCM->setHorizontalHeaderItem(4, new QTableWidgetItem("FQCY(Hz)"));
	ui.tableWidgetLCM->setColumnWidth(4, 120);

	ui.tableWidgetLCM->setHorizontalHeaderItem(5, new QTableWidgetItem("Period(s)"));
	ui.tableWidgetLCM->setColumnWidth(5, 120);

	ui.tableWidgetLCM->setHorizontalHeaderItem(6, new QTableWidgetItem("Stamp(s)"));
	ui.tableWidgetLCM->setColumnWidth(6, 180);

	ui.tableWidgetLCM->setHorizontalHeaderItem(7, new QTableWidgetItem("Delay(ms)"));
	ui.tableWidgetLCM->setColumnWidth(7, 120);
}


/**@brief initialize lcm;
*
* initialize lcm, including: create CMessageThread object, check the lcm environment, subscribe to all channels, start the receive and write thread;
*@return void;
*@note 1. if the lmc could not be initialize, a messagebox will be shown and the program will exit;
* 2. the threads are created by boost create_thread and bind functions;
* 3. the CMessageThread object must be a pointer, to enable copy of the pointer;
*/
void MainWindow::InitializeLCM()
{
	m_pMessageThread = new CMessageThread;//create object, the object must be pointer;

	//check the lcm environment;
	if (!m_pMessageThread->m_lcm.good())
	{
		QMessageBox msgBox;
		msgBox.setText("Initialize Communication Failure, Please Check the Network Connection !");
		msgBox.exec();
		exit(-1);
	}

	//subscribe to all channels by ".*";
	m_pMessageThread->m_lcm.subscribe(".*", &CMessageThread::ReceiveMessage, m_pMessageThread);

	//create and start receive and write threads;
	thread_group threadGroup;
	threadGroup.create_thread(bind(&CMessageThread::ReceiveThread, m_pMessageThread));
	threadGroup.create_thread(bind(&CMessageThread::WriteThread, m_pMessageThread));

	OnShowStatusMessage("Communication initialize succeed!");
}


/**@brief initialize signals and slots;
*
* initialize signals and slots;
*@return void;
*@note
*/
void MainWindow::InitializeSignalsAndSlots()
{

	//ui related signals and slots;
	connect(ui.pushButtonStartRecord, SIGNAL(clicked(bool)), this, SLOT(OnStartRecord()));
	connect(ui.pushButtonStopRecord, SIGNAL(clicked(bool)), this, SLOT(OnStopRecord()));
	connect(ui.tableWidgetLCM, SIGNAL(cellClicked(int, int)), this, SLOT(OnTableItemClicked(int, int)));
	connect(ui.pushButton_selectAll, SIGNAL(clicked(bool)), this, SLOT(OnSelectAll()));
	connect(ui.pushButton_invertSelect, SIGNAL(clicked(bool)), this, SLOT(OnInvertSelect()));

	//timer to update the table widget;
	connect(&m_qTimerUpdateTable, SIGNAL(timeout()), this, SLOT(OnTimerUpdateTable()));

	//display messages from the CMessageTable, mainly used for debug;
	connect(&m_stMessageTable, SIGNAL(ShowStatusMessage(QString)), this, SLOT(OnShowStatusMessage(QString)));

	//CMessageThread related signals and slots;
	connect(m_pMessageThread, SIGNAL(ShowStatusMessage(QString)), this, SLOT(OnShowStatusMessage(QString)));
	connect(m_pMessageThread, SIGNAL(MessageReceived(MESSAGE)), &m_stMessageTable, SLOT(OnMessageReceived(MESSAGE)));
	connect(m_pMessageThread, SIGNAL(ShowLogFileName(QString)), this, SLOT(OnShowLogFileName(QString)));
	connect(m_pMessageThread, SIGNAL(UpdateRecordStatus(RECORD_STATUS)), this, SLOT(OnUpdateRecordStatus(RECORD_STATUS)));
	connect(m_pMessageThread, SIGNAL(LogFinished()), this, SLOT(OnLogFinished()));
	connect(this, SIGNAL(UpdateRecordList(QString, bool)), m_pMessageThread, SLOT(OnUpdateRecordList(QString, bool)));
	connect(this, SIGNAL(SwitchRecord(bool)), m_pMessageThread, SLOT(OnSwitchRecord(bool)));
}


/**@brief update the table widget at frequency specified by the timer;
*
* update the table widget at frequency specified by the timer, including: set the number of the rows, update each item;
*@return void;
*@note 1. when new channels has been detected, a new row is added to the table;
* 2. each item is set (by setItem function) only when new row is added to the table to avoid qt warning;
* 3. only the message receive stamp could be get, the delay could not be measured;
*/
void MainWindow::OnTimerUpdateTable()
{
	//if new channel is detected, add row to the table;
	if (m_stMessageTable.GetRowWidgetsNum() > ui.tableWidgetLCM->rowCount())
	{
		int j = ui.tableWidgetLCM->rowCount();
		ui.tableWidgetLCM->setRowCount(m_stMessageTable.GetRowWidgetsNum());
		for (; j<m_stMessageTable.GetRowWidgetsNum(); j++)
		{
			ui.tableWidgetLCM->setItem(j, 0, new QTableWidgetItem(QString("")));//set new item as null string;
			ui.tableWidgetLCM->item(j, 0)->setTextAlignment(Qt::AlignCenter);//set item alignment;
			ui.tableWidgetLCM->item(j, 0)->setCheckState(Qt::Unchecked);//set check status;

			ui.tableWidgetLCM->setItem(j, 1, new QTableWidgetItem(QString("")));
			ui.tableWidgetLCM->item(j, 1)->setTextAlignment(Qt::AlignCenter);

			ui.tableWidgetLCM->setItem(j, 2, new QTableWidgetItem(QString("")));
			ui.tableWidgetLCM->item(j, 2)->setTextAlignment(Qt::AlignCenter);

			ui.tableWidgetLCM->setItem(j, 3, new QTableWidgetItem(QString("")));
			ui.tableWidgetLCM->item(j, 3)->setTextAlignment(Qt::AlignCenter);

			ui.tableWidgetLCM->setItem(j, 4, new QTableWidgetItem(QString("")));
			ui.tableWidgetLCM->item(j, 4)->setTextAlignment(Qt::AlignCenter);

			ui.tableWidgetLCM->setItem(j, 5, new QTableWidgetItem(QString("")));
			ui.tableWidgetLCM->item(j, 5)->setTextAlignment(Qt::AlignCenter);

			ui.tableWidgetLCM->setItem(j, 6, new QTableWidgetItem(QString("")));
			ui.tableWidgetLCM->item(j, 6)->setTextAlignment(Qt::AlignCenter);

			ui.tableWidgetLCM->setItem(j, 7, new QTableWidgetItem(QString("")));
			ui.tableWidgetLCM->item(j, 7)->setTextAlignment(Qt::AlignCenter);
		}
	}

	//update each row at specified frequency;
	for (int i = 0; i<m_stMessageTable.GetRowWidgetsNum(); i++)
	{
		ui.tableWidgetLCM->item(i, 1)->setText(m_stMessageTable.m_qListRowWidgets[i]->m_QStrChannelName);
		ui.tableWidgetLCM->item(i, 2)->setText(QString::asprintf("%d", m_stMessageTable.m_qListRowWidgets[i]->m_nMsgCounter));
		ui.tableWidgetLCM->item(i, 3)->setText(QString::asprintf("%.3lf", m_stMessageTable.m_qListRowWidgets[i]->m_nMsgSize / 1000.0));
		ui.tableWidgetLCM->item(i, 4)->setText(QString::asprintf("%.3lf", m_stMessageTable.m_qListRowWidgets[i]->m_fFrequency));
		ui.tableWidgetLCM->item(i, 5)->setText(QString::asprintf("%.6lf", m_stMessageTable.m_qListRowWidgets[i]->m_fPeriod));
		ui.tableWidgetLCM->item(i, 6)->setText(QString::asprintf("%.6lf", m_stMessageTable.m_qListRowWidgets[i]->m_nRecvTimeStamp / 1000000.0));
	}
}


/**@brief slot function to show message on the status bar;
*
* slot function to clear the status bar and show new message on the status bar;
*@param msg [IN]: the message to be showed;
*@return void;
*@note 1. previous message on the status bar will be firstly cleared;
*/
void MainWindow::OnShowStatusMessage(QString msg)
{
	ui.statusBar->clearMessage();
	ui.statusBar->showMessage(msg);
}


/**@brief slot function to update the record status of each channel;
*
* when the item of the table widget is clicked, this function is invoked to update the  record status of each channel;
*@param x [IN]: the row index of the clicked item;
*@param y [IN]: the column of the clicked item;
*@return void;
*@note 1. the row and column index starts from 0;
* 2. the function will also be invoked to update the record list when only click in the first column but not click the checkbox;
*/
void MainWindow::OnTableItemClicked(int x, int y)
{
	//only respond to the log checkbox in the first column;
	if (0 != y)
	{
		return;
	}

	Qt::CheckState checkState = ui.tableWidgetLCM->item(x, y)->checkState();//get check state of the channels;
	if (Qt::Checked == checkState)
	{
		emit UpdateRecordList(m_stMessageTable.m_qListRowWidgets[x]->m_QStrChannelName, true);//emit signal to CMessageThread to add the channel to record list;
		return;
	}
	else
	{
		emit UpdateRecordList(m_stMessageTable.m_qListRowWidgets[x]->m_QStrChannelName, false);//emit signal to CMessageThread to remove the channel from the record list;
		return;
	}
}


/**@brief slot function to start log file when the start button is clicked;
*
* if the start button is clicked, this function will be invoked to: disable the start button, enable the stop button and emit signal to CMessageThread to start record;
*@return void;
*@note 1. the start button is disable and the stop button is enabled;
*/
void MainWindow::OnStartRecord()
{
	ui.pushButtonStartRecord->setEnabled(false);
	ui.pushButtonStopRecord->setEnabled(true);

	emit SwitchRecord(true);//emit signal to CMessageThread to start log file;
}


/**@brief slot function to stop log file when the stop button is clicked;
*
* if the stop button is clicked, this function will be invoked to disable the stop button, and emit signal to CMessageThread to stop recording file;
*@return void;
*@note 1. the start will not be enabled until the CMessageThread has finished writting of all queued messages;
*/
void MainWindow::OnStopRecord()
{
	ui.pushButtonStopRecord->setEnabled(false);
	emit SwitchRecord(false);//emit signal to CMessageThread to stop log file;
}


/**@brief slot function to enable the start button;
*
* only when current log file is finished, the start button will be enabled;
*@return void;
*@note 1. the sigial is emitted by the CMessageThread only when all the queued message are written to the log file and the log file is closed;
*/
void MainWindow::OnLogFinished()
{
	ui.pushButtonStartRecord->setEnabled(true);
}


/**@brief slot function to display current log file name on the line edit;
*
* each time new log file is created, this function will be invoked to display messages on the ui;
*@param strFileName [IN]: current record file name;
*@return void;
*@note 1. each time start button is clicked, a new file is created to log the data;
*/
void MainWindow::OnShowLogFileName(QString strFileName)
{
	ui.lineEditFileName->setText(strFileName);
}


/**@brief slot function to update the record status;
*
* the record status (including bandwidth, bytestowrite, byteswritten) will be updated every 1 second;
*@param recordStatus [IN]: current record status;
*@return void;
*@note 1. the signal is emitted by the CMessageThread;
*/
void MainWindow::OnUpdateRecordStatus(RECORD_STATUS recordStatus)
{
	ui.lineEditBandWidth->setText(QString::asprintf("%.3f", recordStatus.fBandWidth));
	ui.lineEditDataToWrite->setText(QString::asprintf("%.3f", recordStatus.fBytesToWrite));
	ui.lineEditDataWritten->setText(QString::asprintf("%.3f", recordStatus.fBytesWritten));
}

void MainWindow::OnSelectAll()
{
	int _rowCount = ui.tableWidgetLCM->rowCount();
	for (int i = 0; i<_rowCount; i++)
	{
		ui.tableWidgetLCM->item(i, 0)->setCheckState(Qt::Checked);
		emit UpdateRecordList(m_stMessageTable.m_qListRowWidgets[i]->m_QStrChannelName, true);
	}
}

void MainWindow::OnInvertSelect()
{
	int _rowCount = ui.tableWidgetLCM->rowCount();
	for (int i = 0; i<_rowCount; i++)
	{
		if (ui.tableWidgetLCM->item(i, 0)->checkState())
		{
			ui.tableWidgetLCM->item(i, 0)->setCheckState(Qt::Unchecked);
			emit UpdateRecordList(m_stMessageTable.m_qListRowWidgets[i]->m_QStrChannelName, false);
		}
		else
		{
			ui.tableWidgetLCM->item(i, 0)->setCheckState(Qt::Checked);
			emit UpdateRecordList(m_stMessageTable.m_qListRowWidgets[i]->m_QStrChannelName, true);
		}
	}
}
