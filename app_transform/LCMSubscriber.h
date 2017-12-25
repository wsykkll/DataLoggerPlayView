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

private:
	bool InitilizeLCM();

	lcm::LCM* m_pLCM;
	bool m_bInitilized;
	CLCMHandler m_lcmHandler;
};

