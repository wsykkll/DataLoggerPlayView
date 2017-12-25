#include "cviewerwindow.h"

CViewerWindow::CViewerWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

CViewerWindow::~CViewerWindow()
{
	
}

void CViewerWindow::on_actionImage_toggled(bool checked)
{
	ui.widgetQGLViewer->m_stDisplayControl.bRawImage = checked;
}

void CViewerWindow::on_actionVehicle_Model_toggled(bool checked)
{
	ui.widgetQGLViewer->m_stDisplayControl.bVehicleModel = checked;
}

void CViewerWindow::on_actionSquareGrids_toggled(bool checked)
{
	ui.widgetQGLViewer->m_stDisplayControl.bSquareGrids = checked;
}

void CViewerWindow::on_actionPerceptionLanes_toggled(bool checked)
{
	ui.widgetQGLViewer->m_stDisplayControl.bPerceptionLanes = checked;
}

void CViewerWindow::on_actionFront_MWR_toggled(bool checked)
{
	ui.widgetQGLViewer->m_stDisplayControl.bRawFrontMWR = checked;
}

void CViewerWindow::on_actionLeft_SRR_toggled(bool checked)
{
	ui.widgetQGLViewer->m_stDisplayControl.bRawLeftMWR = checked;
}