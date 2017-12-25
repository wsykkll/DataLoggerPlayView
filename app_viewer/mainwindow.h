#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow ui;
	//Ui::MainWindowClass ui;

private slots:
	void on_actionVehicle_Model_toggled(bool checked);
	void on_actionSquareGrids_toggled(bool checked);
	void on_actionWorldCoordinate_toggled(bool checked);
    void on_actionImage_toggled(bool arg1);
    void on_actionLeft_SRR_toggled(bool arg1);
    void on_actionRight_SRR_toggled(bool arg1);
    void on_actionVCU550_toggled(bool arg1);
    void on_actionINS_toggled(bool arg1);
    void on_actionRadical_Grids_toggled(bool arg1);
    void on_actionFrontMWRFiltered_toggled(bool arg1);
    void on_actionLeftSRRFiltered_toggled(bool arg1);
    void on_actionRightSRRFiltered_toggled(bool arg1);
    void on_actionVehicleCoordinate_toggled(bool arg1);
    void on_actionCameraCoordinate_toggled(bool arg1);
    void on_actionESRCoordinate_toggled(bool arg1);
    void on_actionLeftSRRCoordinate_toggled(bool arg1);
    void on_actionRightSRRCoordinate_toggled(bool arg1);
    void on_actionPrescanLanes_toggled(bool arg1);
    void on_actionPrescanPos_toggled(bool arg1);
    void on_actionMapLanes_toggled(bool arg1);
    void on_actionDetectedLanelinesMark_toggled(bool arg1);
    void on_actionMapLanelinesMark_toggled(bool arg1);
    void on_actionDetectedTrafficSign_toggled(bool arg1);
    void on_actionMapTrafficSign_toggled(bool arg1);
    void on_actionLineBwtweenCoordinate_toggled(bool arg1);
    void on_actionLane_1_toggled(bool arg1);
    void on_actionLane_2_toggled(bool arg1);
    void on_actionLane_3_toggled(bool arg1);
    void on_actionLane_4_toggled(bool arg1);
    void on_actionMapLanelinesProcess_toggled(bool arg1);
    void on_actionMapLanelinesCalibration_toggled(bool arg1);
    void on_actionACC_toggled(bool arg1);
    void on_actionFCW_toggled(bool arg1);
    void on_action_ESRNewTarget_toggled(bool arg1);
    void on_action_ESRNewUpdatedTarget_toggled(bool arg1);
    void on_action_ESRUpdatedTarget_toggled(bool arg1);
    void on_action_ESRCoastedTarget_toggled(bool arg1);
};

#endif // MAINWINDOW_H
