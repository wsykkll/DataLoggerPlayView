#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <QFileDialog>
#include "ui_mainwindow.h"
#include <global.hpp>

#include "cplayerthread.h"
#include <TrafficSignTable_t.hpp>
#include <METPublisCANEvent_Lcm.hpp>
#include <METGPSInfo_Lcm.hpp>
#include <METImageObject_Lcm.hpp>
#include <TrafficSignSignal_t.hpp>
//namespace Ui {
//class MainWindow;
//}


struct VehPosture
{
	double dLatitude;
	double dLongitude;
	double dHeading;
	double dSpeed;
	VehPosture()
	{
		dLatitude = 0.0f;
		dLongitude = 0.0f;
		dHeading = 0.0f;
		dSpeed = 0.0f;
	}
};

struct SignEdge
{
	float left;
	float right;
	float top;
	float bottom;
	SignEdge()
	{
		left = 0.0f;
		right = 0.0f;
		top = 0.0f;
		bottom = 0.0f;
	}
};

struct CalibrationSign
{
	int num;
	double init_lat;
	double init_lon;
	double delta_distance;
	double last_delta_distance;
	float sign_height;
	std::vector<SignEdge> vecSignEdge;
	CalibrationSign()
	{
		sign_height = 0.0f;
		num = 0;
		init_lon = 0.0f;
		init_lat = 0.0f;
	}
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
	Ui::MainWindow *ui;
    CPlayerThread* m_pPlayerThread;
    thread_group m_threadGroup;
	

    long long int m_nFirstEventTimeStamp;
    long long int m_nLastEventTimeStamp;

	void SwitchWidgetsStatus(bool bLoadFile, bool bPlay, bool bPause, bool bStep, bool bSetSpeed, bool bGoto, bool bTimeSlider, bool bLoop, bool bNextImg, bool bNextRTK, bool bPreviousImg, bool bPreviousRTK);
    void InitializeUI();
    void InitializeSignalsAndSlots();
    void DisplayFileAndChannelInfo();
	void GoToTheListTime(QList<int64_t> timestampList);
	//LCM 
	//mutex m_mutTrafficsignCalibration;
	//TrafficSignTable_t m_msgTrafficsignCalibration;
	//mutex m_mutSpeed;
	//mutex m_mutRTK;
	//mutex m_mutIMG;
	//METGPSInfo_Lcm m_msgRTKInfo;
	//METPublisCANEvent_Lcm m_msgVehicleinfo;
	//METImageObject_Lcm m_msgCameraIMG;

	//TrafficSignSignal_t m_msgTSRUpdateSignal;

	//SignEdge CalculateSignEdge(TrafficSignElement_t TSRElement);
	
	//void run();
	//void CallbackComandInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName);
	//void CallbackCalibrationInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName, const TrafficSignTable_t* msg);
	//void CallbackCalibrationInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName);
	//void CallbackRTKMsg(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName);
	//void CallbackVehicleMsg(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName);
	//void CallbackIMGMsg(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName);

	//void InitializeLCM();
	//lcm::LCM* m_pLCM;
	//TrafficSignQueue_t m_gstTSRInfo[64];

	////Vehicle
	//VehPosture m_stVehiclePos;
	//int64_t m_nlastPosTimestamp;
	//void PrintVehicleInfo();
	//void ProcessTSRCalibration();
	////std::vector<float> DistanceWent[64];
	//CalibrationSign m_gstCalibrationSign[64];
	//void GPSChange(double delta_x,double delta_y);
	//double DistanceBetweenTwoPoints(double N1, double E1, double N2, double E2);

signals:
    void UpdateChannelBroadCast(int index, bool broadcast);

public slots:
    void OnPushButtonLoadFileClicked();
    void OnPushButtonPlayClicked();
    void OnPushButtonPauseClicked();
    void OnPushButtonStepClicked();
    void OnPushButtonGoToClicked();
    void OnPushButtonSetSpeedClicked();
    void OnTimeSliderMoved(int value);
	void OnPushButtonNextRTKClicked();
	void OnPushButtonNextIMGClicked();
	void OnPushButtonPreviousRTKClicked();
	void OnPushButtonPreviousIMGClicked();


    void OnCheckBoxLoopStateChanged(int state);

    void OnShowStatusMessage(QString str);

    void OnUpdateCurrentTimeStamp(long long int timestamp);
    void OnUpdateTableRow(int index, CHANNEL_INFO channel);
    void OnTableItemClicked(int x, int y);
};

#endif // MAINWINDOW_H
