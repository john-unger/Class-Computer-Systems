//John Paul Smithdeal and John Unger
//December 5, 2015

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
	r = (r % (40001));
	r = r + 10000;
	order_size = r;
	printf("Order Size: %d\n", order_size);

	port++ ; 				/* service name or port number  */

	reset_attempts();
	return &processing;
}

#endif

