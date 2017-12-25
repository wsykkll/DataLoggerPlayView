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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTableWidget *tableWidgetLCM;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QSlider *horizontalSliderTime;
    QHBoxLayout *horizontalLayout_7;
    QLabel *labelFirstTimeStamp;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLabel *labelCurrentTimeStamp;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_6;
    QDoubleSpinBox *doubleSpinBoxGotoTimeStamp;
    QPushButton *pushButtonGoto;
    QSpacerItem *horizontalSpacer_5;
    QLabel *labelLastTimeStamp;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEditFileName;
    QPushButton *pushButtonLoadFile;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBoxLoop;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_3;
    QDoubleSpinBox *doubleSpinBoxPlaySpeed;
    QPushButton *pushButtonSetSpeed;
    QPushButton *pushButtonPlay;
    QPushButton *pushButtonPause;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonStep;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *pushButton_PreviousRTK;
    QPushButton *pushButton_PreviousIMG;
    QPushButton *pushButton_nextRTK;
    QPushButton *pushButton_nextIMG;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1005, 370);
        MainWindow->setMinimumSize(QSize(1005, 347));
        MainWindow->setMaximumSize(QSize(1005, 370));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tableWidgetLCM = new QTableWidget(centralWidget);
        if (tableWidgetLCM->columnCount() < 15)
            tableWidgetLCM->setColumnCount(15);
        tableWidgetLCM->setObjectName(QStringLiteral("tableWidgetLCM"));
        tableWidgetLCM->setGeometry(QRect(20, 69, 971, 191));
        tableWidgetLCM->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tableWidgetLCM->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidgetLCM->setRowCount(0);
        tableWidgetLCM->setColumnCount(15);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 0, 971, 62));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSliderTime = new QSlider(layoutWidget);
        horizontalSliderTime->setObjectName(QStringLiteral("horizontalSliderTime"));
        horizontalSliderTime->setEnabled(true);
        horizontalSliderTime->setMaximum(1000000);
        horizontalSliderTime->setSliderPosition(0);
        horizontalSliderTime->setOrientation(Qt::Horizontal);
        horizontalSliderTime->setTickPosition(QSlider::NoTicks);

        verticalLayout->addWidget(horizontalSliderTime);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        labelFirstTimeStamp = new QLabel(layoutWidget);
        labelFirstTimeStamp->setObjectName(QStringLiteral("labelFirstTimeStamp"));
        labelFirstTimeStamp->setEnabled(false);
        labelFirstTimeStamp->setMinimumSize(QSize(150, 0));
        labelFirstTimeStamp->setMaximumSize(QSize(100, 16777215));
        labelFirstTimeStamp->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(labelFirstTimeStamp);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_5->addWidget(label_4);

        labelCurrentTimeStamp = new QLabel(layoutWidget);
        labelCurrentTimeStamp->setObjectName(QStringLiteral("labelCurrentTimeStamp"));
        labelCurrentTimeStamp->setEnabled(false);
        labelCurrentTimeStamp->setMinimumSize(QSize(150, 27));
        labelCurrentTimeStamp->setMaximumSize(QSize(100, 27));
        labelCurrentTimeStamp->setFrameShape(QFrame::NoFrame);
        labelCurrentTimeStamp->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(labelCurrentTimeStamp);


        horizontalLayout_7->addLayout(horizontalLayout_5);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        doubleSpinBoxGotoTimeStamp = new QDoubleSpinBox(layoutWidget);
        doubleSpinBoxGotoTimeStamp->setObjectName(QStringLiteral("doubleSpinBoxGotoTimeStamp"));
        doubleSpinBoxGotoTimeStamp->setMinimumSize(QSize(150, 0));
        doubleSpinBoxGotoTimeStamp->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxGotoTimeStamp->setDecimals(3);
        doubleSpinBoxGotoTimeStamp->setMinimum(0.01);
        doubleSpinBoxGotoTimeStamp->setMaximum(1);
        doubleSpinBoxGotoTimeStamp->setSingleStep(0.1);
        doubleSpinBoxGotoTimeStamp->setValue(1);

        horizontalLayout_6->addWidget(doubleSpinBoxGotoTimeStamp);

        pushButtonGoto = new QPushButton(layoutWidget);
        pushButtonGoto->setObjectName(QStringLiteral("pushButtonGoto"));
        pushButtonGoto->setEnabled(false);
        pushButtonGoto->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_6->addWidget(pushButtonGoto);


        horizontalLayout_7->addLayout(horizontalLayout_6);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);

        labelLastTimeStamp = new QLabel(layoutWidget);
        labelLastTimeStamp->setObjectName(QStringLiteral("labelLastTimeStamp"));
        labelLastTimeStamp->setEnabled(false);
        labelLastTimeStamp->setMinimumSize(QSize(150, 0));
        labelLastTimeStamp->setMaximumSize(QSize(100, 16777215));
        labelLastTimeStamp->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(labelLastTimeStamp);


        verticalLayout->addLayout(horizontalLayout_7);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 270, 971, 33));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lineEditFileName = new QLineEdit(layoutWidget1);
        lineEditFileName->setObjectName(QStringLiteral("lineEditFileName"));
        lineEditFileName->setEnabled(false);
        lineEditFileName->setMinimumSize(QSize(400, 0));
        lineEditFileName->setMaximumSize(QSize(400, 16777215));

        horizontalLayout_2->addWidget(lineEditFileName);

        pushButtonLoadFile = new QPushButton(layoutWidget1);
        pushButtonLoadFile->setObjectName(QStringLiteral("pushButtonLoadFile"));
        pushButtonLoadFile->setMaximumSize(QSize(90, 16777215));

        horizontalLayout_2->addWidget(pushButtonLoadFile);


        horizontalLayout_4->addLayout(horizontalLayout_2);

        horizontalSpacer = new QSpacerItem(20, 26, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        checkBoxLoop = new QCheckBox(layoutWidget1);
        checkBoxLoop->setObjectName(QStringLiteral("checkBoxLoop"));
        checkBoxLoop->setEnabled(false);

        horizontalLayout_4->addWidget(checkBoxLoop);

        horizontalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        doubleSpinBoxPlaySpeed = new QDoubleSpinBox(layoutWidget1);
        doubleSpinBoxPlaySpeed->setObjectName(QStringLiteral("doubleSpinBoxPlaySpeed"));
        doubleSpinBoxPlaySpeed->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxPlaySpeed->setMinimum(0.01);
        doubleSpinBoxPlaySpeed->setMaximum(10);
        doubleSpinBoxPlaySpeed->setSingleStep(0.1);
        doubleSpinBoxPlaySpeed->setValue(1);

        horizontalLayout_3->addWidget(doubleSpinBoxPlaySpeed);

        pushButtonSetSpeed = new QPushButton(layoutWidget1);
        pushButtonSetSpeed->setObjectName(QStringLiteral("pushButtonSetSpeed"));
        pushButtonSetSpeed->setEnabled(false);
        pushButtonSetSpeed->setMaximumSize(QSize(90, 16777215));

        horizontalLayout_3->addWidget(pushButtonSetSpeed);


        horizontalLayout->addLayout(horizontalLayout_3);

        pushButtonPlay = new QPushButton(layoutWidget1);
        pushButtonPlay->setObjectName(QStringLiteral("pushButtonPlay"));
        pushButtonPlay->setEnabled(false);
        pushButtonPlay->setMaximumSize(QSize(60, 16777215));

        horizontalLayout->addWidget(pushButtonPlay);

        pushButtonPause = new QPushButton(layoutWidget1);
        pushButtonPause->setObjectName(QStringLiteral("pushButtonPause"));
        pushButtonPause->setEnabled(false);
        pushButtonPause->setMaximumSize(QSize(60, 16777215));

        horizontalLayout->addWidget(pushButtonPause);


        horizontalLayout_4->addLayout(horizontalLayout);

        horizontalSpacer_2 = new QSpacerItem(20, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        pushButtonStep = new QPushButton(layoutWidget1);
        pushButtonStep->setObjectName(QStringLiteral("pushButtonStep"));
        pushButtonStep->setEnabled(false);
        pushButtonStep->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_4->addWidget(pushButtonStep);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(670, 310, 320, 25));
        horizontalLayout_8 = new QHBoxLayout(widget);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        pushButton_PreviousRTK = new QPushButton(widget);
        pushButton_PreviousRTK->setObjectName(QStringLiteral("pushButton_PreviousRTK"));
        pushButton_PreviousRTK->setEnabled(false);

        horizontalLayout_8->addWidget(pushButton_PreviousRTK);

        pushButton_PreviousIMG = new QPushButton(widget);
        pushButton_PreviousIMG->setObjectName(QStringLiteral("pushButton_PreviousIMG"));
        pushButton_PreviousIMG->setEnabled(false);

        horizontalLayout_8->addWidget(pushButton_PreviousIMG);

        pushButton_nextRTK = new QPushButton(widget);
        pushButton_nextRTK->setObjectName(QStringLiteral("pushButton_nextRTK"));
        pushButton_nextRTK->setEnabled(false);

        horizontalLayout_8->addWidget(pushButton_nextRTK);

        pushButton_nextIMG = new QPushButton(widget);
        pushButton_nextIMG->setObjectName(QStringLiteral("pushButton_nextIMG"));
        pushButton_nextIMG->setEnabled(false);

        horizontalLayout_8->addWidget(pushButton_nextIMG);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Player", 0));
        labelFirstTimeStamp->setText(QApplication::translate("MainWindow", "0.000", 0));
        label_4->setText(QApplication::translate("MainWindow", "Current:", 0));
        labelCurrentTimeStamp->setText(QApplication::translate("MainWindow", "0.000", 0));
        pushButtonGoto->setText(QApplication::translate("MainWindow", "Goto", 0));
        labelLastTimeStamp->setText(QApplication::translate("MainWindow", "1.000", 0));
        lineEditFileName->setText(QString());
        pushButtonLoadFile->setText(QApplication::translate("MainWindow", "Load File", 0));
        checkBoxLoop->setText(QApplication::translate("MainWindow", "Loop", 0));
        pushButtonSetSpeed->setText(QApplication::translate("MainWindow", "Set Speed", 0));
        pushButtonPlay->setText(QApplication::translate("MainWindow", "Play", 0));
        pushButtonPause->setText(QApplication::translate("MainWindow", "Pause", 0));
        pushButtonStep->setText(QApplication::translate("MainWindow", "Step", 0));
        pushButton_PreviousRTK->setText(QApplication::translate("MainWindow", "PreviousRTK", 0));
        pushButton_PreviousIMG->setText(QApplication::translate("MainWindow", "PreviousIMG", 0));
        pushButton_nextRTK->setText(QApplication::translate("MainWindow", "NextRTK", 0));
        pushButton_nextIMG->setText(QApplication::translate("MainWindow", "NextIMG", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
