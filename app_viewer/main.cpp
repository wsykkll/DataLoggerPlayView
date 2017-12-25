#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include "LCMSubscriber.h"
//#include "global.hpp"

CLCMSubscriber* g_pLCMSubscriber;

int main(int argc, char *argv[])
{
	g_pLCMSubscriber = new CLCMSubscriber;
	QApplication a(argc, argv);
	MainWindow w;
	w.setWindowIcon(QIcon("viewer.ico"));
	//w.show();
	w.showMaximized();

	if (!g_pLCMSubscriber->IsInitilized())
	{
		return(EXIT_FAILURE);
	}
	thread_group ThreadGroup;
	ThreadGroup.create_thread(bind(&CLCMSubscriber::run,g_pLCMSubscriber));
	//w.show();
	a.exec();
	//delete[] g_pLCMSubscriber;
	return(EXIT_SUCCESS);
}
