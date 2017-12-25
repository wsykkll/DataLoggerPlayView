/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "cqglviewer.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionImage;
    QAction *actionLeft_SRR;
    QAction *actionRight_SRR;
    QAction *actionVCU550;
    QAction *actionVehicle_Model;
    QAction *actionINS;
    QAction *actionSquareGrids;
    QAction *actionRadical_Grids;
    QAction *actionWorldCoordinate;
    QAction *actionVehicleCoordinate;
    QAction *actionCameraCoordinate;
    QAction *actionESRCoordinate;
    QAction *actionLeftSRRCoordinate;
    QAction *actionRightSRRCoordinate;
    QAction *actionLeftSRRFiltered;
    QAction *actionRightSRRFiltered;
    QAction *actionPrescanLanes;
    QAction *actionPrescanPos;
    QAction *actionMapLanes;
    QAction *actionDetectedLanelinesMark;
    QAction *actionMapLanelinesMark;
    QAction *actionDetectedTrafficSign;
    QAction *actionMapTrafficSign;
    QAction *actionLineBwtweenCoordinate;
    QAction *actionLane_1;
    QAction *actionLane_2;
    QAction *actionLane_3;
    QAction *actionLane_4;
    QAction *actionMapLanelinesProcess;
    QAction *actionMapLanelinesCalibration;
    QAction *actionACC;
    QAction *actionFCW;
    QAction *action_ESRNewTarget;
    QAction *action_ESRNewUpdatedTarget;
    QAction *action_ESRUpdatedTarget;
    QAction *action_ESRCoastedTarget;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    CQGLViewer *widgetQGLViewer;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuRawSensor;
    QMenu *menuMWR;
    QMenu *menuFront;
    QMenu *menuVCU;
    QMenu *menuPRESCAN;
    QMenu *menuLaneLines;
    QMenu *menuTrafficSign;
    QMenu *menuPreprocessing;
    QMenu *menuMWR_2;
    QMenu *menuFrontMWR;
    QMenu *menuMiscellaneous;
    QMenu *menuCoordinates;
    QMenu *menuLaneMatch;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1164, 802);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(0, 0));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        actionImage = new QAction(MainWindow);
        actionImage->setObjectName(QStringLiteral("actionImage"));
        actionImage->setCheckable(true);
        actionImage->setChecked(false);
        actionLeft_SRR = new QAction(MainWindow);
        actionLeft_SRR->setObjectName(QStringLiteral("actionLeft_SRR"));
        actionLeft_SRR->setCheckable(true);
        actionRight_SRR = new QAction(MainWindow);
        actionRight_SRR->setObjectName(QStringLiteral("actionRight_SRR"));
        actionRight_SRR->setCheckable(true);
        actionVCU550 = new QAction(MainWindow);
        actionVCU550->setObjectName(QStringLiteral("actionVCU550"));
        actionVCU550->setCheckable(true);
        actionVCU550->setChecked(true);
        actionVehicle_Model = new QAction(MainWindow);
        actionVehicle_Model->setObjectName(QStringLiteral("actionVehicle_Model"));
        actionVehicle_Model->setCheckable(true);
        actionVehicle_Model->setChecked(true);
        actionINS = new QAction(MainWindow);
        actionINS->setObjectName(QStringLiteral("actionINS"));
        actionINS->setCheckable(true);
        actionINS->setChecked(true);
        actionSquareGrids = new QAction(MainWindow);
        actionSquareGrids->setObjectName(QStringLiteral("actionSquareGrids"));
        actionSquareGrids->setCheckable(true);
        actionSquareGrids->setChecked(true);
        actionRadical_Grids = new QAction(MainWindow);
        actionRadical_Grids->setObjectName(QStringLiteral("actionRadical_Grids"));
        actionRadical_Grids->setCheckable(true);
        actionWorldCoordinate = new QAction(MainWindow);
        actionWorldCoordinate->setObjectName(QStringLiteral("actionWorldCoordinate"));
        actionWorldCoordinate->setCheckable(true);
        actionWorldCoordinate->setChecked(true);
        actionVehicleCoordinate = new QAction(MainWindow);
        actionVehicleCoordinate->setObjectName(QStringLiteral("actionVehicleCoordinate"));
        actionVehicleCoordinate->setCheckable(true);
        actionVehicleCoordinate->setChecked(true);
        actionCameraCoordinate = new QAction(MainWindow);
        actionCameraCoordinate->setObjectName(QStringLiteral("actionCameraCoordinate"));
        actionCameraCoordinate->setCheckable(true);
        actionCameraCoordinate->setChecked(true);
        actionESRCoordinate = new QAction(MainWindow);
        actionESRCoordinate->setObjectName(QStringLiteral("actionESRCoordinate"));
        actionESRCoordinate->setCheckable(true);
        actionESRCoordinate->setChecked(true);
        actionLeftSRRCoordinate = new QAction(MainWindow);
        actionLeftSRRCoordinate->setObjectName(QStringLiteral("actionLeftSRRCoordinate"));
        actionLeftSRRCoordinate->setCheckable(true);
        actionLeftSRRCoordinate->setChecked(true);
        actionRightSRRCoordinate = new QAction(MainWindow);
        actionRightSRRCoordinate->setObjectName(QStringLiteral("actionRightSRRCoordinate"));
        actionRightSRRCoordinate->setCheckable(true);
        actionRightSRRCoordinate->setChecked(true);
        actionLeftSRRFiltered = new QAction(MainWindow);
        actionLeftSRRFiltered->setObjectName(QStringLiteral("actionLeftSRRFiltered"));
        actionLeftSRRFiltered->setCheckable(true);
        actionRightSRRFiltered = new QAction(MainWindow);
        actionRightSRRFiltered->setObjectName(QStringLiteral("actionRightSRRFiltered"));
        actionRightSRRFiltered->setCheckable(true);
        actionPrescanLanes = new QAction(MainWindow);
        actionPrescanLanes->setObjectName(QStringLiteral("actionPrescanLanes"));
        actionPrescanLanes->setCheckable(true);
        actionPrescanPos = new QAction(MainWindow);
        actionPrescanPos->setObjectName(QStringLiteral("actionPrescanPos"));
        actionPrescanPos->setCheckable(true);
        actionPrescanPos->setChecked(false);
        actionMapLanes = new QAction(MainWindow);
        actionMapLanes->setObjectName(QStringLiteral("actionMapLanes"));
        actionMapLanes->setCheckable(true);
        actionDetectedLanelinesMark = new QAction(MainWindow);
        actionDetectedLanelinesMark->setObjectName(QStringLiteral("actionDetectedLanelinesMark"));
        actionDetectedLanelinesMark->setCheckable(true);
        actionMapLanelinesMark = new QAction(MainWindow);
        actionMapLanelinesMark->setObjectName(QStringLiteral("actionMapLanelinesMark"));
        actionMapLanelinesMark->setCheckable(true);
        actionDetectedTrafficSign = new QAction(MainWindow);
        actionDetectedTrafficSign->setObjectName(QStringLiteral("actionDetectedTrafficSign"));
        actionDetectedTrafficSign->setCheckable(true);
        actionMapTrafficSign = new QAction(MainWindow);
        actionMapTrafficSign->setObjectName(QStringLiteral("actionMapTrafficSign"));
        actionMapTrafficSign->setCheckable(true);
        actionLineBwtweenCoordinate = new QAction(MainWindow);
        actionLineBwtweenCoordinate->setObjectName(QStringLiteral("actionLineBwtweenCoordinate"));
        actionLineBwtweenCoordinate->setCheckable(true);
        actionLane_1 = new QAction(MainWindow);
        actionLane_1->setObjectName(QStringLiteral("actionLane_1"));
        actionLane_1->setCheckable(true);
        actionLane_1->setChecked(false);
        actionLane_2 = new QAction(MainWindow);
        actionLane_2->setObjectName(QStringLiteral("actionLane_2"));
        actionLane_2->setCheckable(true);
        actionLane_2->setChecked(false);
        actionLane_3 = new QAction(MainWindow);
        actionLane_3->setObjectName(QStringLiteral("actionLane_3"));
        actionLane_3->setCheckable(true);
        actionLane_3->setChecked(false);
        actionLane_4 = new QAction(MainWindow);
        actionLane_4->setObjectName(QStringLiteral("actionLane_4"));
        actionLane_4->setCheckable(true);
        actionLane_4->setChecked(false);
        actionMapLanelinesProcess = new QAction(MainWindow);
        actionMapLanelinesProcess->setObjectName(QStringLiteral("actionMapLanelinesProcess"));
        actionMapLanelinesProcess->setCheckable(true);
        actionMapLanelinesCalibration = new QAction(MainWindow);
        actionMapLanelinesCalibration->setObjectName(QStringLiteral("actionMapLanelinesCalibration"));
        actionMapLanelinesCalibration->setCheckable(true);
        actionACC = new QAction(MainWindow);
        actionACC->setObjectName(QStringLiteral("actionACC"));
        actionACC->setCheckable(true);
        actionFCW = new QAction(MainWindow);
        actionFCW->setObjectName(QStringLiteral("actionFCW"));
        actionFCW->setCheckable(true);
        action_ESRNewTarget = new QAction(MainWindow);
        action_ESRNewTarget->setObjectName(QStringLiteral("action_ESRNewTarget"));
        action_ESRNewTarget->setCheckable(true);
        action_ESRNewUpdatedTarget = new QAction(MainWindow);
        action_ESRNewUpdatedTarget->setObjectName(QStringLiteral("action_ESRNewUpdatedTarget"));
        action_ESRNewUpdatedTarget->setCheckable(true);
        action_ESRUpdatedTarget = new QAction(MainWindow);
        action_ESRUpdatedTarget->setObjectName(QStringLiteral("action_ESRUpdatedTarget"));
        action_ESRUpdatedTarget->setCheckable(true);
        action_ESRCoastedTarget = new QAction(MainWindow);
        action_ESRCoastedTarget->setObjectName(QStringLiteral("action_ESRCoastedTarget"));
        action_ESRCoastedTarget->setCheckable(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widgetQGLViewer = new CQGLViewer(centralWidget);
        widgetQGLViewer->setObjectName(QStringLiteral("widgetQGLViewer"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(widgetQGLViewer->sizePolicy().hasHeightForWidth());
        widgetQGLViewer->setSizePolicy(sizePolicy1);
        widgetQGLViewer->setMinimumSize(QSize(0, 0));
        widgetQGLViewer->setMaximumSize(QSize(16777215, 16777215));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(227, 227, 227, 100));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        widgetQGLViewer->setPalette(palette);
        widgetQGLViewer->setAutoFillBackground(true);

        gridLayout->addWidget(widgetQGLViewer, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1164, 23));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(menuBar->sizePolicy().hasHeightForWidth());
        menuBar->setSizePolicy(sizePolicy2);
        menuBar->setDefaultUp(false);
        menuBar->setNativeMenuBar(true);
        menuRawSensor = new QMenu(menuBar);
        menuRawSensor->setObjectName(QStringLiteral("menuRawSensor"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(menuRawSensor->sizePolicy().hasHeightForWidth());
        menuRawSensor->setSizePolicy(sizePolicy3);
        menuMWR = new QMenu(menuRawSensor);
        menuMWR->setObjectName(QStringLiteral("menuMWR"));
        menuFront = new QMenu(menuMWR);
        menuFront->setObjectName(QStringLiteral("menuFront"));
        menuVCU = new QMenu(menuRawSensor);
        menuVCU->setObjectName(QStringLiteral("menuVCU"));
        menuPRESCAN = new QMenu(menuRawSensor);
        menuPRESCAN->setObjectName(QStringLiteral("menuPRESCAN"));
        menuLaneLines = new QMenu(menuRawSensor);
        menuLaneLines->setObjectName(QStringLiteral("menuLaneLines"));
        menuTrafficSign = new QMenu(menuRawSensor);
        menuTrafficSign->setObjectName(QStringLiteral("menuTrafficSign"));
        menuPreprocessing = new QMenu(menuBar);
        menuPreprocessing->setObjectName(QStringLiteral("menuPreprocessing"));
        menuMWR_2 = new QMenu(menuPreprocessing);
        menuMWR_2->setObjectName(QStringLiteral("menuMWR_2"));
        menuFrontMWR = new QMenu(menuMWR_2);
        menuFrontMWR->setObjectName(QStringLiteral("menuFrontMWR"));
        menuMiscellaneous = new QMenu(menuBar);
        menuMiscellaneous->setObjectName(QStringLiteral("menuMiscellaneous"));
        menuCoordinates = new QMenu(menuMiscellaneous);
        menuCoordinates->setObjectName(QStringLiteral("menuCoordinates"));
        menuLaneMatch = new QMenu(menuBar);
        menuLaneMatch->setObjectName(QStringLiteral("menuLaneMatch"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuRawSensor->menuAction());
        menuBar->addAction(menuPreprocessing->menuAction());
        menuBar->addAction(menuMiscellaneous->menuAction());
        menuBar->addAction(menuLaneMatch->menuAction());
        menuRawSensor->addAction(actionImage);
        menuRawSensor->addAction(menuMWR->menuAction());
        menuRawSensor->addAction(actionINS);
        menuRawSensor->addAction(menuVCU->menuAction());
        menuRawSensor->addAction(menuPRESCAN->menuAction());
        menuRawSensor->addAction(menuLaneLines->menuAction());
        menuRawSensor->addAction(menuTrafficSign->menuAction());
        menuMWR->addAction(menuFront->menuAction());
        menuMWR->addAction(actionLeft_SRR);
        menuMWR->addAction(actionRight_SRR);
        menuFront->addAction(action_ESRNewTarget);
        menuFront->addAction(action_ESRNewUpdatedTarget);
        menuFront->addAction(action_ESRUpdatedTarget);
        menuFront->addAction(action_ESRCoastedTarget);
        menuVCU->addAction(actionVCU550);
        menuPRESCAN->addAction(actionPrescanLanes);
        menuPRESCAN->addAction(actionPrescanPos);
        menuPRESCAN->addAction(actionMapLanes);
        menuLaneLines->addAction(actionDetectedLanelinesMark);
        menuLaneLines->addAction(actionMapLanelinesMark);
        menuLaneLines->addAction(actionMapLanelinesProcess);
        menuLaneLines->addAction(actionMapLanelinesCalibration);
        menuTrafficSign->addAction(actionDetectedTrafficSign);
        menuTrafficSign->addAction(actionMapTrafficSign);
        menuPreprocessing->addAction(menuMWR_2->menuAction());
        menuMWR_2->addAction(menuFrontMWR->menuAction());
        menuMWR_2->addAction(actionLeftSRRFiltered);
        menuMWR_2->addAction(actionRightSRRFiltered);
        menuFrontMWR->addAction(actionACC);
        menuFrontMWR->addAction(actionFCW);
        menuMiscellaneous->addAction(menuCoordinates->menuAction());
        menuMiscellaneous->addAction(actionVehicle_Model);
        menuMiscellaneous->addAction(actionSquareGrids);
        menuMiscellaneous->addAction(actionRadical_Grids);
        menuCoordinates->addAction(actionLineBwtweenCoordinate);
        menuCoordinates->addAction(actionWorldCoordinate);
        menuCoordinates->addAction(actionVehicleCoordinate);
        menuCoordinates->addAction(actionCameraCoordinate);
        menuCoordinates->addAction(actionESRCoordinate);
        menuCoordinates->addAction(actionLeftSRRCoordinate);
        menuCoordinates->addAction(actionRightSRRCoordinate);
        menuLaneMatch->addAction(actionLane_1);
        menuLaneMatch->addAction(actionLane_2);
        menuLaneMatch->addAction(actionLane_3);
        menuLaneMatch->addAction(actionLane_4);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Autonomous Driving - Viewer", 0));
        actionImage->setText(QApplication::translate("MainWindow", "Image", 0));
        actionLeft_SRR->setText(QApplication::translate("MainWindow", "Left", 0));
        actionRight_SRR->setText(QApplication::translate("MainWindow", "Right", 0));
        actionVCU550->setText(QApplication::translate("MainWindow", "VCU550", 0));
        actionVehicle_Model->setText(QApplication::translate("MainWindow", "Vehicle Model", 0));
        actionINS->setText(QApplication::translate("MainWindow", "INS", 0));
        actionSquareGrids->setText(QApplication::translate("MainWindow", "Square_Grids", 0));
        actionRadical_Grids->setText(QApplication::translate("MainWindow", "Radical_Grids", 0));
        actionWorldCoordinate->setText(QApplication::translate("MainWindow", "World", 0));
        actionVehicleCoordinate->setText(QApplication::translate("MainWindow", "Vehicle", 0));
        actionCameraCoordinate->setText(QApplication::translate("MainWindow", "Camera", 0));
        actionESRCoordinate->setText(QApplication::translate("MainWindow", "ESR", 0));
        actionLeftSRRCoordinate->setText(QApplication::translate("MainWindow", "LeftSRR", 0));
        actionRightSRRCoordinate->setText(QApplication::translate("MainWindow", "RightSRR", 0));
        actionLeftSRRFiltered->setText(QApplication::translate("MainWindow", "LeftSRR", 0));
        actionRightSRRFiltered->setText(QApplication::translate("MainWindow", "RightSRR", 0));
        actionPrescanLanes->setText(QApplication::translate("MainWindow", "PrescanLanes", 0));
        actionPrescanPos->setText(QApplication::translate("MainWindow", "PrescanPos", 0));
        actionMapLanes->setText(QApplication::translate("MainWindow", "MapLanes", 0));
        actionDetectedLanelinesMark->setText(QApplication::translate("MainWindow", "DetectedLanelinesMark", 0));
        actionMapLanelinesMark->setText(QApplication::translate("MainWindow", "MapLanelinesMark", 0));
        actionDetectedTrafficSign->setText(QApplication::translate("MainWindow", "DetectedTrafficSign", 0));
        actionMapTrafficSign->setText(QApplication::translate("MainWindow", "MapTrafficSign", 0));
        actionLineBwtweenCoordinate->setText(QApplication::translate("MainWindow", "LineBwtweenCoordinate", 0));
        actionLane_1->setText(QApplication::translate("MainWindow", "Lane_1", 0));
        actionLane_2->setText(QApplication::translate("MainWindow", "Lane_2", 0));
        actionLane_3->setText(QApplication::translate("MainWindow", "Lane_3", 0));
        actionLane_4->setText(QApplication::translate("MainWindow", "Lane_4", 0));
        actionMapLanelinesProcess->setText(QApplication::translate("MainWindow", "MapLanelinesProcess", 0));
        actionMapLanelinesCalibration->setText(QApplication::translate("MainWindow", "MapLanelinesCalibration", 0));
        actionACC->setText(QApplication::translate("MainWindow", "ACC", 0));
        actionFCW->setText(QApplication::translate("MainWindow", "FCW", 0));
        action_ESRNewTarget->setText(QApplication::translate("MainWindow", "New", 0));
        action_ESRNewUpdatedTarget->setText(QApplication::translate("MainWindow", "NewUpdated", 0));
        action_ESRUpdatedTarget->setText(QApplication::translate("MainWindow", "Updated", 0));
        action_ESRCoastedTarget->setText(QApplication::translate("MainWindow", "Coasted", 0));
        menuRawSensor->setTitle(QApplication::translate("MainWindow", "RawSensor", 0));
        menuMWR->setTitle(QApplication::translate("MainWindow", "MWR", 0));
        menuFront->setTitle(QApplication::translate("MainWindow", "Front", 0));
        menuVCU->setTitle(QApplication::translate("MainWindow", "VCU", 0));
        menuPRESCAN->setTitle(QApplication::translate("MainWindow", "PRESCAN", 0));
        menuLaneLines->setTitle(QApplication::translate("MainWindow", "LaneLines", 0));
        menuTrafficSign->setTitle(QApplication::translate("MainWindow", "TrafficSign", 0));
        menuPreprocessing->setTitle(QApplication::translate("MainWindow", "Preprocessing", 0));
        menuMWR_2->setTitle(QApplication::translate("MainWindow", "MWR", 0));
        menuFrontMWR->setTitle(QApplication::translate("MainWindow", "FrontMWR", 0));
        menuMiscellaneous->setTitle(QApplication::translate("MainWindow", "Miscellaneous", 0));
        menuCoordinates->setTitle(QApplication::translate("MainWindow", "Coordinates", 0));
        menuLaneMatch->setTitle(QApplication::translate("MainWindow", "LaneMatch", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
