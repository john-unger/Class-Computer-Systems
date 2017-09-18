//John Paul Smithdeal and John Unger
//October 27, 2015

#ifndef accepting_c
#define accepting_c

#include "accepting.h"
#include "hardware.h"
#include "statemodel.h"

state_t accepting = {
		order_rcvd,
		default_event_handler,
		default_event_handler,
		default_event_handler,
		default_event_handler,
		default_event_handler,
		default_event_handler,
		default_action,
		default_action,
};

state_t* order_rcvd()
{
	// random number between 1000- 2000
	srandom(time(NULL));
	int r = random();
	r = (r % (1001));
	r = r + 1000;
	order_size = r;
	printf("Order Size: %d\n", order_size);

	reset_attempts();
	return &processing;
}

#endif

