#pragma once
#include <lcm\lcm-cpp.hpp>
#include "LCMHandler.h"

class CLCMSubscriber
{
public:
	CLCMSubscriber();
	~CLCMSubscriber();
	void run();
	bool IsInitilized();
	CLCMHandler m_lcmHandler;

private:
	bool InitilizeLCM();

	lcm::LCM* m_pLCM;
	bool m_bInitilized;
};

