//John Paul Smithdeal and John Unger
//December 5, 2015

#ifndef hardware_h
#define hardware_h

#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

typedef enum
{
	ORDER_RCVD,
	INVALID_PYMNT,
	VALID_PYMNT,
	MANUF_FAILED,
	MANUF_COMPLETED,
	LOST_PACKAGE,
	RECEIVED,
	NUMBER_OF_EVENTS
} event;

typedef enum
{
	DONE,
	FAIL,
	LOST,
	NUMBER_OF_STATS
}stats;

// Global variable
extern int order_size;
extern int parts_made;
extern int attempts;		// Number of attempts
extern int LinesActive;			// Number of manufacturing lines

extern unsigned short port;

extern void charge_client();
extern void dispatch_factory_lines();
extern void ind_line();
extern void get_address();
extern void get_pymnt_method();
extern void increment_attempts();
extern void refund();
extern void reset_attempts();
extern void shut_down_factory_lines();
extern void start_warranty();
extern void update_stats(stats value);


#endif

