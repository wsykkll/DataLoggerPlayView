#include "LCMSubscriber.h"


CLCMSubscriber::CLCMSubscriber():
m_pLCM(new lcm::LCM("udpm://239.255.76.67:7667?ttl=1")),
m_bInitilized(false)
{
	m_bInitilized = InitilizeLCM();
}


CLCMSubscriber::~CLCMSubscriber()
{
	delete m_pLCM;
}


bool CLCMSubscriber::InitilizeLCM()
{
	if (!m_pLCM->good())
	{
		return false;
	}
	m_pLCM->subscribe("Command", &MainWindow::CallbackComandInfo, &m_stLocalizationCalculate);

	return true;
}

void CLCMSubscriber::run()
{
	while (0 == m_pLCM->handle())
	{

	}
}

bool CLCMSubscriber::IsInitilized()
{
	return m_bInitilized;
}