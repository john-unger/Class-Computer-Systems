//John Paul Smithdeal and John Unger
//October 27, 2015

#ifndef shipping_c
#define shipping_c

#include "shipping.h"
#include "hardware.h"
#include "statemodel.h"

state_t shipping = {
   default_event_handler,
   default_event_handler,
   default_event_handler,
   default_event_handler,
   default_event_handler,
   lost_package,
   received,
   entry_to,
   default_action,
};

state_t* lost_package()
{
   printf("The shipment was not delivered to the client (for some reason)\n");
   update_stats(LOST);
   refund();
   return &accepting;
}

state_t* received()
{
   printf("Delivery of the shipment to the client’s address has been confirmed\n");
   update_stats(DONE);
   start_warranty();
   return &accepting;
}

void entry_to()
{
   get_address();
}

#endif

