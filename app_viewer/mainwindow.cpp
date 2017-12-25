#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

MainWindow::~MainWindow()
{

}


void MainWindow::on_actionVehicle_Model_toggled(bool checked)
{
	ui.widgetQGLViewer->m_stDisplayControl.bVehicleModel = checked;
}

void MainWindow::on_actionSquareGrids_toggled(bool checked)
{
	ui.widgetQGLViewer->m_stDisplayControl.bSquareGrids = checked;
}

void MainWindow::on_actionWorldCoordinate_toggled(bool checked)
{
	ui.widgetQGLViewer->m_stDisplayControl.bWorldCoordinate = checked;
}
void MainWindow::on_actionImage_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bRawImage = arg1;
}

void MainWindow::on_actionLeft_SRR_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bRawLeftMWR = arg1;
}

void MainWindow::on_actionRight_SRR_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bRawRightMWR = arg1;
}

void MainWindow::on_actionVCU550_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bRawVCU550 = arg1;
}

void MainWindow::on_actionINS_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bRawINS = arg1;
}

void MainWindow::on_actionRadical_Grids_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bRadicalGrids = arg1;
}

void MainWindow::on_actionFrontMWRFiltered_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bFrontMWRFiltered = arg1;
}

void MainWindow::on_actionLeftSRRFiltered_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bLeftSRRFiltered = arg1;
}

void MainWindow::on_actionRightSRRFiltered_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bRightSRRFiltered = arg1;
}

void MainWindow::on_actionVehicleCoordinate_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bVehicleCoordinate = arg1;
}

void MainWindow::on_actionCameraCoordinate_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bCameraCoordinate = arg1;
}

void MainWindow::on_actionESRCoordinate_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bFrontMWRCoordinate = arg1;
}

void MainWindow::on_actionLeftSRRCoordinate_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bLeftMWRCoordinate = arg1;
}

void MainWindow::on_actionRightSRRCoordinate_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bRightMWRCoordinate = arg1;
}

void MainWindow::on_actionPrescanLanes_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bPrescanLanes = arg1;
}

void MainWindow::on_actionPrescanPos_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bPrescanPos = arg1;
}

void MainWindow::on_actionMapLanes_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bPrescanMapLanes = arg1;
}

void MainWindow::on_actionDetectedLanelinesMark_toggled(bool arg1)
{
    ui.widgetQGLViewer->m_stDisplayControl.bDetectedLanelines = arg1;
}

void MainWindow::on_actionMapLanelinesMark_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bMapLanelinesMark = arg1;
}

void MainWindow::on_actionDetectedTrafficSign_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bDetectedTSR = arg1;
}

void MainWindow::on_actionMapTrafficSign_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bMapTSR = arg1;
}

void MainWindow::on_actionLineBwtweenCoordinate_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bLineBetweenCoordinate = arg1;
}

void MainWindow::on_actionLane_1_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bLane1 = arg1;
}

void MainWindow::on_actionLane_2_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bLane2 = arg1;
}

void MainWindow::on_actionLane_3_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bLane3 = arg1;
}

void MainWindow::on_actionLane_4_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bLane4 = arg1;
}

void MainWindow::on_actionMapLanelinesProcess_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bMapLanelinesProcess = arg1;
}

void MainWindow::on_actionMapLanelinesCalibration_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bMapLanelinesCalibrated = arg1;
}


void MainWindow::on_actionACC_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bESRACCObjects = arg1;
}

void MainWindow::on_actionFCW_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bESRFCWObjects = arg1;
}

void MainWindow::on_action_ESRNewTarget_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bRawESRNew = arg1;
}

void MainWindow::on_action_ESRNewUpdatedTarget_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bRawESRNewUpdated = arg1;
}

void MainWindow::on_action_ESRUpdatedTarget_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bRawESRUpdated = arg1;
}

void MainWindow::on_action_ESRCoastedTarget_toggled(bool arg1)
{
	ui.widgetQGLViewer->m_stDisplayControl.bRawESRCoasted = arg1;
}
