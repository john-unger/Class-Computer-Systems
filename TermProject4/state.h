//John Paul Smithdeal and John Unger
//October 27, 2015

#ifndef state_h
#define state_h


typedef struct state state_t;

typedef state_t* event_handler(void);

typedef void action(void);

struct state
{
   event_handler* 	order_rcvd;
   event_handler* 	invalid_pymnt;
   event_handler* 	valid_pymnt;
   event_handler* 	manuf_failed;
   event_handler* 	manuf_completed;
   event_handler* 	lost_package;
   event_handler* 	received;
   action*	entry_to;
   action* 	exit_from;
};

//They are extern because they are used
// in each of the individual state files but defined elsewere
extern state_t*     default_event_handler();
extern void         default_action();




#endif

