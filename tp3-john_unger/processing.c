//John Paul Smithdeal and John Unger
//October 27, 2015

#ifndef processing_c
#define processing_c

#include "processing.h"
#include "hardware.h"
#include "statemodel.h"

// The number of times that an invalid payment can be made
int const LIMIT = 3;

state_t processing = {
   default_event_handler,
   invalid_pymnt,
   valid_pymnt,
   default_event_handler,
   default_event_handler,
   default_event_handler,
   default_event_handler,
   entry_to,
   default_action,
};

state_t* invalid_pymnt()
{
   if (attempts < LIMIT)
      {
      printf("The payment method obtained from the client was rejected");
      printf(" (i.e. expired, or credit limit exceeded)\n");
      
      increment_attempts();
      return &processing;
      }
   else
      {
      printf("Exceeded Limit");
      return &accepting;
      }
}

state_t* valid_pymnt()
{
   printf("The payment method obtained from the client has been validated\n");
   reset_attempts();
   return &manufacturing;
}

void entry_to()
{
   get_pymnt_method();
}

#endif

