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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
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
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidgetLCM;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEditFileName;
    QPushButton *pushButtonStartRecord;
    QPushButton *pushButtonStopRecord;
    QLabel *label_3;
    QLineEdit *lineEditBandWidth;
    QLabel *label_2;
    QLineEdit *lineEditDataToWrite;
    QLabel *label;
    QLineEdit *lineEditDataWritten;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_selectAll;
    QPushButton *pushButton_invertSelect;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(950, 300);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(950, 300));
        MainWindow->setMaximumSize(QSize(950, 300));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 30, 925, 229));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tableWidgetLCM = new QTableWidget(widget);
        if (tableWidgetLCM->columnCount() < 8)
            tableWidgetLCM->setColumnCount(8);
        tableWidgetLCM->setObjectName(QStringLiteral("tableWidgetLCM"));
        tableWidgetLCM->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidgetLCM->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidgetLCM->setRowCount(0);
        tableWidgetLCM->setColumnCount(8);

        verticalLayout->addWidget(tableWidgetLCM);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEditFileName = new QLineEdit(widget);
        lineEditFileName->setObjectName(QStringLiteral("lineEditFileName"));
        lineEditFileName->setEnabled(false);

        horizontalLayout->addWidget(lineEditFileName);

        pushButtonStartRecord = new QPushButton(widget);
        pushButtonStartRecord->setObjectName(QStringLiteral("pushButtonStartRecord"));
        pushButtonStartRecord->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(pushButtonStartRecord);

        pushButtonStopRecord = new QPushButton(widget);
        pushButtonStopRecord->setObjectName(QStringLiteral("pushButtonStopRecord"));
        pushButtonStopRecord->setEnabled(false);
        pushButtonStopRecord->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(pushButtonStopRecord);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        lineEditBandWidth = new QLineEdit(widget);
        lineEditBandWidth->setObjectName(QStringLiteral("lineEditBandWidth"));
        lineEditBandWidth->setEnabled(false);
        lineEditBandWidth->setMaximumSize(QSize(80, 16777215));
        lineEditBandWidth->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditBandWidth->setReadOnly(true);

        horizontalLayout->addWidget(lineEditBandWidth);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEditDataToWrite = new QLineEdit(widget);
        lineEditDataToWrite->setObjectName(QStringLiteral("lineEditDataToWrite"));
        lineEditDataToWrite->setEnabled(false);
        lineEditDataToWrite->setMaximumSize(QSize(80, 16777215));
        lineEditDataToWrite->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(lineEditDataToWrite);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEditDataWritten = new QLineEdit(widget);
        lineEditDataWritten->setObjectName(QStringLiteral("lineEditDataWritten"));
        lineEditDataWritten->setEnabled(false);
        lineEditDataWritten->setMaximumSize(QSize(100, 16777215));
        lineEditDataWritten->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(lineEditDataWritten);


        verticalLayout->addLayout(horizontalLayout);

        widget1 = new QWidget(centralWidget);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(10, 0, 201, 29));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_selectAll = new QPushButton(widget1);
        pushButton_selectAll->setObjectName(QStringLiteral("pushButton_selectAll"));

        horizontalLayout_2->addWidget(pushButton_selectAll);

        pushButton_invertSelect = new QPushButton(widget1);
        pushButton_invertSelect->setObjectName(QStringLiteral("pushButton_invertSelect"));

        horizontalLayout_2->addWidget(pushButton_invertSelect);

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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Logger", 0));
        lineEditFileName->setText(QString());
        pushButtonStartRecord->setText(QApplication::translate("MainWindow", "Start", 0));
        pushButtonStopRecord->setText(QApplication::translate("MainWindow", "Stop", 0));
        label_3->setText(QApplication::translate("MainWindow", "BandWidth(MB/s):", 0));
        lineEditBandWidth->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "DataToWrite(MB):", 0));
        label->setText(QApplication::translate("MainWindow", "DataWritten(MB):", 0));
        lineEditDataWritten->setText(QString());
        pushButton_selectAll->setText(QApplication::translate("MainWindow", "Select ALL", 0));
        pushButton_invertSelect->setText(QApplication::translate("MainWindow", "Invert Select", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
