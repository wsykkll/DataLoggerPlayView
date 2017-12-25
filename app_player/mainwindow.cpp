#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
m_nFirstEventTimeStamp(0),
m_nLastEventTimeStamp(1000000),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

    m_pPlayerThread = new CPlayerThread;

    InitializeUI();
    InitializeSignalsAndSlots();
	boost::thread m_threadSubscribe(bind(&CPlayerThread::run, m_pPlayerThread));
	//InitializeLCM();
}

//void MainWindow::InitializeLCM()
//{
//	m_pLCM = new lcm::LCM("udpm://239.255.76.67:7667?ttl=1");
//	if (!m_pLCM->good())
//	{
//		QMessageBox msgBox;
//		msgBox.setText(QString("Can not initialize the LCM!"));
//		msgBox.exec();
//		delete m_pLCM;
//		return;
//	}
//	m_pLCM->subscribe("Command", &MainWindow::CallbackComandInfo, this);
//	return;
//}
//
//void MainWindow::run()
//{
//	while (0 == m_pLCM->handle())
//	{
//
//	}
//}

void MainWindow::InitializeUI()
{
    ui->tableWidgetLCM->setHorizontalHeaderItem(0, new QTableWidgetItem(""));//set the header column;
    ui->tableWidgetLCM->setColumnWidth(0, 25);//set the column width;

    ui->tableWidgetLCM->setHorizontalHeaderItem(1, new QTableWidgetItem("Channel"));
    ui->tableWidgetLCM->setColumnWidth(1, 180);

    ui->tableWidgetLCM->setHorizontalHeaderItem(2, new QTableWidgetItem("MsgCount"));
    ui->tableWidgetLCM->setColumnWidth(2, 120);

    ui->tableWidgetLCM->setHorizontalHeaderItem(3, new QTableWidgetItem("MsgSize(kB)"));
    ui->tableWidgetLCM->setColumnWidth(3, 120);

    ui->tableWidgetLCM->setHorizontalHeaderItem(4, new QTableWidgetItem("FQCY(Hz)"));
    ui->tableWidgetLCM->setColumnWidth(4, 120);

    ui->tableWidgetLCM->setHorizontalHeaderItem(5, new QTableWidgetItem("Period(s)"));
    ui->tableWidgetLCM->setColumnWidth(5, 120);

    ui->tableWidgetLCM->setHorizontalHeaderItem(6, new QTableWidgetItem("Stamp(s)"));
    ui->tableWidgetLCM->setColumnWidth(6, 160);

    ui->tableWidgetLCM->setHorizontalHeaderItem(7, new QTableWidgetItem("MsgNumber"));
    ui->tableWidgetLCM->setColumnWidth(7, 120);

    ui->tableWidgetLCM->setHorizontalHeaderItem(8, new QTableWidgetItem("FirstStamp(s)"));
    ui->tableWidgetLCM->setColumnWidth(8, 160);

    ui->tableWidgetLCM->setHorizontalHeaderItem(9, new QTableWidgetItem("LastStamp(s)"));
    ui->tableWidgetLCM->setColumnWidth(9, 160);

    ui->tableWidgetLCM->setHorizontalHeaderItem(10, new QTableWidgetItem("MsgSize(MB)"));
    ui->tableWidgetLCM->setColumnWidth(10, 120);

    ui->tableWidgetLCM->setHorizontalHeaderItem(11, new QTableWidgetItem("AvgMsgSize(kB)"));
    ui->tableWidgetLCM->setColumnWidth(11, 120);

    ui->tableWidgetLCM->setHorizontalHeaderItem(12, new QTableWidgetItem("AvgFrequency"));
    ui->tableWidgetLCM->setColumnWidth(12, 120);

    ui->tableWidgetLCM->setHorizontalHeaderItem(13, new QTableWidgetItem("AvgPeriod(s)"));
    ui->tableWidgetLCM->setColumnWidth(13, 120);

    ui->tableWidgetLCM->setHorizontalHeaderItem(14, new QTableWidgetItem("TimeSpan(s)"));
    ui->tableWidgetLCM->setColumnWidth(14, 120);
}

void MainWindow::InitializeSignalsAndSlots()
{
    connect(ui->pushButtonPlay, SIGNAL(clicked(bool)), this, SLOT(OnPushButtonPlayClicked()));
    connect(ui->pushButtonPause, SIGNAL(clicked(bool)), this, SLOT(OnPushButtonPauseClicked()));
    connect(ui->pushButtonStep, SIGNAL(clicked(bool)), this, SLOT(OnPushButtonStepClicked()));
    connect(ui->pushButtonGoto, SIGNAL(clicked(bool)), this, SLOT(OnPushButtonGoToClicked()));
    connect(ui->pushButtonSetSpeed, SIGNAL(clicked(bool)), this, SLOT(OnPushButtonSetSpeedClicked()));
    connect(ui->pushButtonLoadFile, SIGNAL(clicked(bool)), this, SLOT(OnPushButtonLoadFileClicked()));
    connect(ui->horizontalSliderTime, SIGNAL(sliderMoved(int)), this, SLOT(OnTimeSliderMoved(int)));
    connect(ui->tableWidgetLCM, SIGNAL(cellClicked(int,int)), this, SLOT(OnTableItemClicked(int, int)));
    connect(ui->checkBoxLoop, SIGNAL(stateChanged(int)), this, SLOT(OnCheckBoxLoopStateChanged(int)));
	connect(ui->pushButton_nextRTK, SIGNAL(clicked(bool)), this, SLOT(OnPushButtonNextRTKClicked()));
	connect(ui->pushButton_nextIMG, SIGNAL(clicked(bool)), this, SLOT(OnPushButtonNextIMGClicked()));
	connect(ui->pushButton_PreviousRTK, SIGNAL(clicked(bool)), this, SLOT(OnPushButtonPreviousRTKClicked()));
	connect(ui->pushButton_PreviousIMG, SIGNAL(clicked(bool)), this, SLOT(OnPushButtonPreviousIMGClicked()));

    connect(this, SIGNAL(UpdateChannelBroadCast(int,bool)), m_pPlayerThread, SLOT(OnUpdateChannelBroadCast(int,bool)));
    connect(m_pPlayerThread, SIGNAL(ShowStatusMessage(QString)), this, SLOT(OnShowStatusMessage(QString)));
    connect(m_pPlayerThread, SIGNAL(UpdateCurrentTimeStamp(long long int)), this, SLOT(OnUpdateCurrentTimeStamp(long long int)));
    connect(m_pPlayerThread, SIGNAL(UpdateTableRow(int,CHANNEL_INFO)), this, SLOT(OnUpdateTableRow(int,CHANNEL_INFO)));
}

/**@brief destructor of the mainwindow;
 *
 *default destructor of the MainWindow;
 *@note
 */
MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::SwitchWidgetsStatus(bool bLoadFile, bool bPlay, bool bPause, bool bStep, bool bSetSpeed, bool bGoto, bool bTimeSlider, bool bLoop, bool bNextImg, bool bNextRTK, bool bPreviousImg, bool bPreviousRTK)
{
    ui->pushButtonLoadFile->setEnabled(bLoadFile);
    ui->pushButtonPlay->setEnabled(bPlay);
    ui->pushButtonPause->setEnabled(bPause);
    ui->pushButtonStep->setEnabled(bStep);
    ui->pushButtonSetSpeed->setEnabled(bSetSpeed);
    ui->pushButtonGoto->setEnabled(bGoto);
    ui->horizontalSliderTime->setEnabled(bTimeSlider);
    ui->checkBoxLoop->setEnabled(bLoop);
	ui->pushButton_nextIMG->setEnabled(bNextImg);
	ui->pushButton_nextRTK->setEnabled(bNextRTK);
	ui->pushButton_PreviousIMG->setEnabled(bPreviousImg);
	ui->pushButton_PreviousRTK->setEnabled(bPreviousRTK);
}

void MainWindow::OnPushButtonLoadFileClicked()
{
	m_pPlayerThread->m_bFileLoaded = false;
	SwitchWidgetsStatus(true, false, false, false, false, false, false, false, false, false, false, false);
    ui->horizontalSliderTime->setValue(0);

    //1. display dialog to select the file;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Please Select Log File !"), ".", tr("Log Files (*.log)"));
    if(fileName.isNull())
    {
       return;
    }
    ui->lineEditFileName->setText(fileName);

    //2. try to load the file;
    if(m_pPlayerThread->CheckFile(fileName))
    {
        //3. if file successfully loaded, terminate old threads and start new threads;
        m_pPlayerThread->SetTerminateThreadsStatus(true);
        m_threadGroup.join_all();

        m_pPlayerThread->LoadFile(fileName);

        //display file and channel info in the table;
        DisplayFileAndChannelInfo();

        m_pPlayerThread->SetTerminateThreadsStatus(false);
        //start threads to read and publish events;

        m_threadGroup.create_thread(bind(&CPlayerThread::ReadLogFileThread, m_pPlayerThread));
        m_threadGroup.create_thread(bind(&CPlayerThread::PublishEventsThread, m_pPlayerThread));
        //m_threadGroup.create_thread(bind(&CPlayerThread::run, m_pPlayerThread));
		

		SwitchWidgetsStatus(true, true, false, true, true, true, true, true, true, true, true, true);

        m_pPlayerThread->SetReplayMode(PAUSE);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText(QString("The file is either empty or not in log format! Please load a new file!"));
        msgBox.exec();
    }
}

void MainWindow::DisplayFileAndChannelInfo()
{
    ui->labelFirstTimeStamp->setText(QString::asprintf("%.6lf", m_pPlayerThread->m_stLogFile.nStartTimeStamp/1000000.0));
    ui->labelLastTimeStamp->setText(QString::asprintf("%.6lf", m_pPlayerThread->m_stLogFile.nStopTimeStamp/1000000.0));
    ui->labelCurrentTimeStamp->setText(QString::asprintf("%.6lf", m_pPlayerThread->m_stLogFile.nStartTimeStamp/1000000.0));
    ui->doubleSpinBoxGotoTimeStamp->setMinimum(m_pPlayerThread->m_stLogFile.nStartTimeStamp/1000000.0);
    ui->doubleSpinBoxGotoTimeStamp->setMaximum(m_pPlayerThread->m_stLogFile.nStopTimeStamp/1000000.0);
    ui->doubleSpinBoxGotoTimeStamp->setValue(m_pPlayerThread->m_stLogFile.nStartTimeStamp/10000000.0);
    m_nFirstEventTimeStamp = m_pPlayerThread->m_stLogFile.nStartTimeStamp;
    m_nLastEventTimeStamp = m_pPlayerThread->m_stLogFile.nStopTimeStamp;
    ui->doubleSpinBoxPlaySpeed->setValue(1.0);

    //show the log file data info in the table;
    ui->tableWidgetLCM->setRowCount(m_pPlayerThread->m_listChannels.size());
    for(int i=0; i<m_pPlayerThread->m_listChannels.size(); i++)
    {
        ui->tableWidgetLCM->setItem(i, 0, new QTableWidgetItem(""));
        ui->tableWidgetLCM->item(i, 0)->setTextAlignment(Qt::AlignCenter);//set item alignment;
        ui->tableWidgetLCM->item(i, 0)->setCheckState(Qt::Checked);//set check status;

        ui->tableWidgetLCM->setItem(i, 1, new QTableWidgetItem(m_pPlayerThread->m_listChannels[i].strChannelName));
        ui->tableWidgetLCM->item(i, 1)->setTextAlignment(Qt::AlignCenter);

        ui->tableWidgetLCM->setItem(i, 2, new QTableWidgetItem(QString::asprintf("%ld", m_pPlayerThread->m_listChannels[i].nMsgCount)));
        ui->tableWidgetLCM->item(i, 2)->setTextAlignment(Qt::AlignCenter);

        ui->tableWidgetLCM->setItem(i, 3, new QTableWidgetItem(QString::asprintf("%.3f", m_pPlayerThread->m_listChannels[i].nCurrentMsgSize/1000.0)));
        ui->tableWidgetLCM->item(i, 3)->setTextAlignment(Qt::AlignCenter);

        ui->tableWidgetLCM->setItem(i, 4, new QTableWidgetItem(QString::asprintf("%.3f", m_pPlayerThread->m_listChannels[i].fFrequency)));
        ui->tableWidgetLCM->item(i, 4)->setTextAlignment(Qt::AlignCenter);

        ui->tableWidgetLCM->setItem(i, 5, new QTableWidgetItem(QString::asprintf("%.3f", m_pPlayerThread->m_listChannels[i].fPeriod)));
        ui->tableWidgetLCM->item(i, 5)->setTextAlignment(Qt::AlignCenter);

        ui->tableWidgetLCM->setItem(i, 6, new QTableWidgetItem(QString::asprintf("%.6f", m_pPlayerThread->m_listChannels[i].nCurrentTimeStamp/1000000.0)));
        ui->tableWidgetLCM->item(i, 6)->setTextAlignment(Qt::AlignCenter);

        ui->tableWidgetLCM->setItem(i, 7, new QTableWidgetItem(QString::asprintf("%ld", m_pPlayerThread->m_listChannels[i].nMsgNumber)));
        ui->tableWidgetLCM->item(i, 7)->setTextAlignment(Qt::AlignCenter);

        ui->tableWidgetLCM->setItem(i, 8, new QTableWidgetItem(QString::asprintf("%.6f", m_pPlayerThread->m_listChannels[i].nFirstTimeStamp/1000000.0)));
        ui->tableWidgetLCM->item(i, 8)->setTextAlignment(Qt::AlignCenter);

        ui->tableWidgetLCM->setItem(i, 9, new QTableWidgetItem(QString::asprintf("%.6f", m_pPlayerThread->m_listChannels[i].nLastTimeStamp/1000000.0)));
        ui->tableWidgetLCM->item(i, 9)->setTextAlignment(Qt::AlignCenter);

        ui->tableWidgetLCM->setItem(i, 10, new QTableWidgetItem(QString::asprintf("%.6f", m_pPlayerThread->m_listChannels[i].nMsgSize/1000000.0)));
        ui->tableWidgetLCM->item(i, 10)->setTextAlignment(Qt::AlignCenter);

        ui->tableWidgetLCM->setItem(i, 11, new QTableWidgetItem(QString::asprintf("%.3f", m_pPlayerThread->m_listChannels[i].nAvgMsgSize/1000.0)));
        ui->tableWidgetLCM->item(i, 11)->setTextAlignment(Qt::AlignCenter);

        ui->tableWidgetLCM->setItem(i, 12, new QTableWidgetItem(QString::asprintf("%.3f", m_pPlayerThread->m_listChannels[i].fAvgFrequency)));
        ui->tableWidgetLCM->item(i, 12)->setTextAlignment(Qt::AlignCenter);

        ui->tableWidgetLCM->setItem(i, 13, new QTableWidgetItem(QString::asprintf("%.3f", m_pPlayerThread->m_listChannels[i].fAvgPeriod)));
        ui->tableWidgetLCM->item(i, 13)->setTextAlignment(Qt::AlignCenter);

        ui->tableWidgetLCM->setItem(i, 14, new QTableWidgetItem(QString::asprintf("%.3f", (m_pPlayerThread->m_listChannels[i].nLastTimeStamp-m_pPlayerThread->m_listChannels[i].nFirstTimeStamp)/1000000.0)));
        ui->tableWidgetLCM->item(i, 14)->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::OnPushButtonPlayClicked()
{
    m_pPlayerThread->SetReplayMode(PLAY);
	SwitchWidgetsStatus(false, false, true, false, false, false, false, false, false, false, false, false);
}

void MainWindow::OnPushButtonPauseClicked()
{
    m_pPlayerThread->SetReplayMode(PAUSE);
	SwitchWidgetsStatus(true, false, false, true, true, true, true, true, true, true, true, true);
}

void MainWindow::OnPushButtonStepClicked()
{
    m_pPlayerThread->SetReplayMode(STEP);
	SwitchWidgetsStatus(true, false, false, true, true, true, true, true, true, true, true, true);
}

void MainWindow::OnPushButtonGoToClicked()
{
    //get seek to time stamp;
    long long int stamp = (ui->doubleSpinBoxGotoTimeStamp->value())*1000000;
    m_pPlayerThread->SetSeekToTimeStamp(stamp);
}

void MainWindow::OnPushButtonNextRTKClicked()
{
	m_pPlayerThread->SetReplayMode(NEXTRTK);
	SwitchWidgetsStatus(true, false, true, false, true, false, false, false,false,true,false,false);
}

void MainWindow::OnPushButtonNextIMGClicked()
{
	//m_pPlayerThread->m_pLCM->publish("TrafficSignData", &m_pPlayerThread->m_msgTest);
	m_pPlayerThread->SetReplayMode(NEXTIMG);
	SwitchWidgetsStatus(true, false, true, false, true, false, false, false, true, false,false, false);
}

void MainWindow::OnPushButtonSetSpeedClicked()
{
    float speed = ui->doubleSpinBoxPlaySpeed->value();
    m_pPlayerThread->SetReplaySpeed(speed);
	SwitchWidgetsStatus(true, true, false, true, true, true, true, true, true, true, true, true);
}

void MainWindow::OnPushButtonPreviousRTKClicked()
{
	//GoToTheListTime(m_pPlayerThread->m_listRTKtimestamp);
	m_pPlayerThread->SetSeekToTimeStamp(m_pPlayerThread->m_nCurrentEventTimeStamp - 300000);
	SwitchWidgetsStatus(true, false, true, false, true, false, false, false, false, false, false, true);
	m_pPlayerThread->SetReplayMode(PREVIOUSRTK);
}

void MainWindow::OnPushButtonPreviousIMGClicked()
{
	//GoToTheListTime(m_pPlayerThread->m_listIMGtimestamp);
	m_pPlayerThread->SetSeekToTimeStamp(m_pPlayerThread->m_nCurrentEventTimeStamp - 50000);
	m_pPlayerThread->SetReplayMode(PREVIOUSIMG);
	SwitchWidgetsStatus(true, false, true, false, true, false, false, false, false, false, true, false);
}

void MainWindow::OnShowStatusMessage(QString str)
{
    ui->statusBar->clearMessage();
    ui->statusBar->showMessage(str);
}

void MainWindow::OnCheckBoxLoopStateChanged(int state)
{
    if(state = Qt::Checked)
    {
        m_pPlayerThread->SetLoop(true);
    }
    else
    {
        m_pPlayerThread->SetLoop(false);
    }
}

void MainWindow::OnTimeSliderMoved(int value)
{
	//fprintf(stderr, "value:%d\n", value);
    this->ui->doubleSpinBoxGotoTimeStamp->setValue(((value/1000000.0)*(m_nLastEventTimeStamp-m_nFirstEventTimeStamp)+m_nFirstEventTimeStamp)/1000000.0);
}

void MainWindow::OnUpdateCurrentTimeStamp(long long int timestamp)
{
    if(!ui->horizontalSliderTime->isEnabled())
    {
        this->ui->labelCurrentTimeStamp->setText(QString::asprintf("%.6lf", timestamp/1000000.0));
        ui->horizontalSliderTime->setValue((timestamp-m_nFirstEventTimeStamp)*1000000/(m_nLastEventTimeStamp-m_nFirstEventTimeStamp));
    }

}

void MainWindow::OnUpdateTableRow(int index, CHANNEL_INFO channel)
{
    ui->tableWidgetLCM->item(index, 2)->setText(QString::asprintf("%ld", channel.nMsgCount));
    ui->tableWidgetLCM->item(index, 3)->setText(QString::asprintf("%.3lf", channel.nCurrentMsgSize/1000.0));
    ui->tableWidgetLCM->item(index, 4)->setText(QString::asprintf("%.3lf", channel.fFrequency));
    ui->tableWidgetLCM->item(index, 5)->setText(QString::asprintf("%.6lf", channel.fPeriod));
    ui->tableWidgetLCM->item(index, 6)->setText(QString::asprintf("%.6lf", channel.nCurrentTimeStamp/1000000.0));
}

void MainWindow::OnTableItemClicked(int x, int y)
{
    //only respond to the checkbox in the first column;
    if(0 != y)
    {
        return;
    }

    Qt::CheckState checkState = ui->tableWidgetLCM->item(x, y)->checkState();//get check state of the channels;
    if(Qt::Checked == checkState)
    {
        emit UpdateChannelBroadCast(x, true);
        return;
    }
    else
    {
        emit UpdateChannelBroadCast(x, false);
        return;
    }
}

//void MainWindow::CallbackComandInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName)
//{
//	ControlCmd_t tmp_control;
//	tmp_control.decode(recvBuf->data, 0, recvBuf->data_size);
//	if (m_pPlayerThread->m_bFileLoaded)
//	{
//		switch (tmp_control.control_cmd)
//		{
//		case 1:
//			m_pPlayerThread->SetReplayMode(PLAY);
//			break;
//		case 2:
//			m_pPlayerThread->SetReplayMode(PAUSE);
//			break;
//		case 3:
//			m_pPlayerThread->SetReplayMode(NEXTIMG);
//			break;
//		case 4:
//			GoToTheListTime(m_pPlayerThread->m_listIMGtimestamp);
//			m_pPlayerThread->SetReplayMode(PREVIOUSIMG);
//			break;
//		case 5:
//			m_pPlayerThread->SeekToTimeStamp(tmp_control.header.nTimeStamp);
//			m_pPlayerThread->SetReplayMode(PLAY);
//			break;
//		default:
//			break;
//		}
//	}
//}


void MainWindow::GoToTheListTime(QList<int64_t> timestampList)
{
	QList<int64_t>::iterator iter = timestampList.begin();
	int64_t now_t = m_pPlayerThread->m_nCurrentEventTimeStamp;
	if ((*(iter + 1) >= now_t))
	{
		m_pPlayerThread->SetSeekToTimeStamp(m_pPlayerThread->m_stLogFile.nStartTimeStamp);
	}
	else
	{
		iter++;
		for (; iter != timestampList.end(); iter++)
		{
			int64_t tt1 = *iter;
			int64_t tt2 = *(iter - 1);
			int64_t tt3 = *(iter + 1);
			if ((tt1 < now_t) && (tt3 >= now_t))
			{
				m_pPlayerThread->SetSeekToTimeStamp(tt2);
				break;
			}
		}
	}
}

//void MainWindow::CallbackCalibrationInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName, const TrafficSignTable_t* msg)
//void MainWindow::CallbackCalibrationInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName)
//{
//	fprintf(stderr, "TEST\n");
//	m_mutTrafficsignCalibration.lock();
//	m_msgTrafficsignCalibration.decode(recvBuf->data, 0, recvBuf->data_size);
//	//for (unsigned int i = 0; i < 64; i++)
//	//{
//	//m_gstTSRInfo[i] = msg->queue[i];
//	//}
//	m_mutTrafficsignCalibration.unlock();
//	ProcessTSRCalibration();
//}

//void MainWindow::CallbackVehicleMsg(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName)
//{
//	m_mutSpeed.lock();
//	m_msgVehicleinfo.decode(recvBuf->data, 0, recvBuf->data_size);
//	m_stVehiclePos.dSpeed = m_msgVehicleinfo.messageval;
//	fprintf(stderr, "Vehicle_speed is %lf\n",m_stVehiclePos.dSpeed);
//	m_mutSpeed.unlock();
//}

//void MainWindow::CallbackRTKMsg(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName)
//{
//	m_mutRTK.lock();
//	m_msgRTKInfo.decode(recvBuf->data, 0, recvBuf->data_size);
//	m_stVehiclePos.dLatitude = m_msgRTKInfo.GGA_dwLat / 100;
//	m_stVehiclePos.dLongitude = m_msgRTKInfo.GGA_dwLon / 100;
//	m_stVehiclePos.dHeading = m_msgRTKInfo.TRA_dwHeading;
//	m_stVehiclePos.dSpeed = m_msgRTKInfo.RMC_dwSpeedIn*0.5144f*3.6f;
//	m_nlastPosTimestamp = m_msgRTKInfo.header.nTimeStamp;
//	m_mutRTK.unlock();
//}

//void MainWindow::CallbackIMGMsg(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName)
//{
//	m_mutIMG.lock();
//	m_msgCameraIMG.decode(recvBuf->data, 0, recvBuf->data_size);
//	int64_t delta_timestamp = (m_msgCameraIMG.header.nTimeStamp - m_nlastPosTimestamp);
//	double delta_dis = m_stVehiclePos.dSpeed * delta_timestamp / 1000000;
//	double delta_x = delta_dis * sin(m_stVehiclePos.dHeading * DEGREE_TO_RADIAN);
//	double delta_y = delta_dis * cos(m_stVehiclePos.dHeading * DEGREE_TO_RADIAN);
//	GPSChange(delta_x, delta_y);
//	m_nlastPosTimestamp = m_msgCameraIMG.header.nTimeStamp;
//	m_mutIMG.unlock();
//	for (unsigned int i = 0; i < 64; i++)
//	{
//		if (m_gstCalibrationSign[i].num == 0)
//		{
//			continue;
//		}
//		if (m_gstCalibrationSign[i].num == 1)
//		{
//			if (DistanceBetweenTwoPoints(m_stVehiclePos.dLatitude, m_stVehiclePos.dLongitude, m_gstCalibrationSign[i].init_lat, m_gstCalibrationSign[i].init_lon) > 15)
//			{
//				//give the calibration sign
//				m_msgTSRUpdateSignal.needupdate[i] = 1;
//			}
//			else
//			{
//				continue;
//			}
//		}
//		if (m_gstCalibrationSign[i].num>1)
//		{
//			int32_t h1 = abs(m_gstCalibrationSign[i].vecSignEdge[m_gstCalibrationSign[i].num].bottom - m_gstCalibrationSign[i].vecSignEdge[m_gstCalibrationSign[i].num].top);
//			double Delta_D = (SAMPLERATE - 1)*m_gstCalibrationSign[i].sign_height*FOCALLENGTH / (h1*CAMPIXELS);
//			if (DistanceBetweenTwoPoints(m_stVehiclePos.dLatitude, m_stVehiclePos.dLongitude, m_gstCalibrationSign[i].init_lat, m_gstCalibrationSign[i].init_lon) > Delta_D)
//			{
//				m_msgTSRUpdateSignal.needupdate[i] = 1;
//			}
//			else
//			{
//				continue;
//			}
//		}
//	}
//	m_pLCM->publish("TSR_SIGNAL", &m_msgTSRUpdateSignal,sizeof(TrafficSignSignal_t));
//	for (unsigned int i = 0; i < 64; i++)
//	{
//		m_msgTSRUpdateSignal.needupdate[i] = 0;
//	}
//}

//void MainWindow::GPSChange(double delta_x, double delta_y)
//{
//	m_stVehiclePos.dLatitude += delta_x / DISPERLATITUDEDEGREE;
//	m_stVehiclePos.dLongitude += delta_y / DISPERLONGITUDEDEGREE;
//}
//
//double MainWindow::DistanceBetweenTwoPoints(double N1, double E1, double N2, double E2)
//{
//	double a = abs(N1 - N2) * DISPERLATITUDEDEGREE;
//	double b = abs(E1 - E2) * DISPERLONGITUDEDEGREE;
//	return sqrt(a*a + b*b);
//}
//
//void MainWindow::PrintVehicleInfo()
//{
//	fprintf(stderr, "Last POS timestamp is %I64d\n", m_nlastPosTimestamp);
//	fprintf(stderr, "Vehicle latitude is %lf\n", m_stVehiclePos.dLatitude);
//	fprintf(stderr, "Vehicle longitude is %lf\n", m_stVehiclePos.dLongitude);
//	fprintf(stderr, "Vehicle heading is %lf\n", m_stVehiclePos.dHeading);
//	fprintf(stderr, "Vehicle speed is %lf\n", m_stVehiclePos.dSpeed);
//}

//void MainWindow::ProcessTSRCalibration()
//{
//	for (unsigned int i = 0; i < 64; i++)
//	{
//		if (m_msgTrafficsignCalibration.queue[i].active)
//		{
//			TrafficSignQueue_t tmpTSRQueue = m_msgTrafficsignCalibration.queue[i];
//			std::vector< TrafficSignElement_t > tmpTSRElement(tmpTSRQueue.TraSignElement);
//			m_gstCalibrationSign[i].num = tmpTSRQueue.num_ranges;
//			m_gstCalibrationSign[i].vecSignEdge.push_back(CalculateSignEdge(tmpTSRQueue.TraSignElement[tmpTSRQueue.num_ranges]));
//			if (tmpTSRQueue.num_ranges == 2)
//			{
//				//calculate the sign height approximate
//				int32_t h1 = abs(m_gstCalibrationSign[i].vecSignEdge[1].bottom - m_gstCalibrationSign[i].vecSignEdge[1].top);
//				int32_t h2 = abs(m_gstCalibrationSign[i].vecSignEdge[2].bottom - m_gstCalibrationSign[i].vecSignEdge[2].top);
//				double delta_D = DistanceBetweenTwoPoints(m_stVehiclePos.dLatitude, m_stVehiclePos.dLongitude, m_gstCalibrationSign[i].init_lat, m_gstCalibrationSign[i].init_lon);
//
//				m_gstCalibrationSign[i].sign_height = (h1*delta_D) / (h2 - h1)*(h1*CAMPIXELS) / FOCALLENGTH;
//			}
//			m_gstCalibrationSign[i].init_lat = m_stVehiclePos.dLatitude;
//			m_gstCalibrationSign[i].init_lon = m_stVehiclePos.dLongitude;
//		}
//	}
//}


//SignEdge MainWindow::CalculateSignEdge(TrafficSignElement_t TSRElement)
//{
//	SignEdge tmpSignEdge;
//	std::vector<int32_t> sign_x;
//	std::vector<int32_t> sign_y;
//	for (unsigned int i = 0; i < TSRElement.sPointNum; i++)
//	{
//		sign_x.push_back(TSRElement.objpPointPts->x);
//		sign_y.push_back(TSRElement.objpPointPts->y);
//	}
//	sort(sign_x.begin(), sign_x.end());
//	sort(sign_y.begin(), sign_y.end());
//	tmpSignEdge.left = sign_x[0];
//	tmpSignEdge.right = sign_x[TSRElement.sPointNum];
//	tmpSignEdge.top = sign_y[0];
//	tmpSignEdge.bottom = sign_y[TSRElement.sPointNum];
//	return tmpSignEdge;
//}