#include <iostream>
#include "LCMHandler.h"
#include "LCMSubscriber.h"
#include "Transformer.h"


int  main(int argc, char** argv)
{
	CLCMSubscriber lcmSubscriber;
	if (!lcmSubscriber.IsInitilized())
	{
		return(EXIT_FAILURE);
	}
	boost::thread_group Thread_Group;
	Thread_Group.create_thread(bind(&CLCMSubscriber::run,&lcmSubscriber));

	Thread_Group.join_all();
	return 0;
}