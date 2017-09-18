//John Paul Smithdeal and John Unger
//October 27, 2015

#ifndef statemodel_c
#define statemodel_c

#include "statemodel.h"
#include <stdlib.h>
#include <stdio.h>

//Define the initial state
static state_t* current_state = &accepting;

void handle_event(event current_event)
{
	state_t* next_state;
	next_state = NULL;

	switch(current_event)
	{
	case ORDER_RCVD:
		next_state = current_state->order_rcvd();
		break;
	case INVALID_PYMNT:
		next_state = current_state->invalid_pymnt();
		break;
	case VALID_PYMNT:
		next_state = current_state->valid_pymnt();
		break;
	case MANUF_FAILED:
		next_state = current_state->manuf_failed();
		break;
	case MANUF_COMPLETED:
		next_state = current_state->manuf_completed();
		break;
	case LOST_PACKAGE:
		next_state = current_state->lost_package();
		break;
	case RECEIVED:
		next_state = current_state->received();
		break;
	}

	if (next_state != NULL)
	{
		current_state = next_state; 	//change states
		current_state->entry_to(); 	//enter the new state

		if (current_state == &accepting)
			printf("\nCurrent State is: ACCEPTING\n");
		else if(current_state == &processing)
			printf("Current State is: PROCESSING\n");
		else if(current_state  == &manufacturing)
			printf("Current State is: MANUFACTURING\n");
		else if (current_state == &shipping)
			printf("Current State is: SHIPPING\n");

		current_state->exit_from();	//exit the new state
	}
}

#endif

