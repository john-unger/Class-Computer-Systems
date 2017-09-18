//John Paul Smithdeal and John Unger
//December 5, 2015

#ifndef statemodel_h
#define statemodel_h

#include <stdlib.h>
#include "hardware.h"
#include "state.h"

//Declare all of the states used in the state model.
//They are extern because they are defined elsewhere
extern state_t accepting;
extern state_t processing;
extern state_t manufacturing;
extern state_t shipping;

//Declare all of the functions
void handle_event(event current_event);

#endif

