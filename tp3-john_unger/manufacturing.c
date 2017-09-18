//John Paul Smithdeal and John Unger
//October 27, 2015

#ifndef manufacturing_c
#define manufacturing_c

#include "manufacturing.h"
#include "hardware.h"
#include "statemodel.h"
#include <pthread.h>
#include <semaphore.h>

state_t manufacturing = {
	default_event_handler,
	default_event_handler,
	default_event_handler,
	manuf_failed,
	manuf_completed,
	default_event_handler,
	default_event_handler,
	entry_to,
	exit_from,
};

state_t* manuf_failed()
{
	printf("The factory line(s) failed to manufacture ALL requested replicas of the item being ordered\n");
	update_stats(FAIL);
	return &accepting;
}

state_t* manuf_completed()
{
	printf("The factory line(s) successfully manufactured ALL requested replicas of the item being ordered\n");
	
	charge_client();
	return &shipping;
}

void entry_to()
{
	dispatch_factory_lines();
}

void exit_from()
{
	shut_down_factory_lines();
}

#endif

