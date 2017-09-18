//John Paul Smithdeal and John Unger
//October 27, 2015

#ifndef hardware_h
#define hardware_h

#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

//Create the shared memory structure
typedef struct
{
	sem_t OSsem;
	sem_t PSsem;
	sem_t print;
	sem_t destroy;
	int order_size;

} shared_mem_data;

#define MEM_KEY 0x100
#define mem_size sizeof(shared_mem_data)

//Create the message queue structure
typedef struct
{
	long msg_type;

	struct
	{
		bool ptFlg;			// Defines whether is a production or termination message
		pid_t sender;		// The ID number
		int cap;			// Number of max parts possible
		int dur;			// Amount of time to sleep
		int factory_id;		// The Lane number
		int iter;			// Number of times the factory line has executed
		int total_made;		// Number of actually made parts
		int parts_made;
	} contents;

} msgBuf;

#define MSG_INFO_SIZE (sizeof(msgBuf) - sizeof(long) )
#define BASE_MAILBOX_NAME 0x20


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

// shared semaphore
extern sem_t s;

// global threads
extern pthread_t thrd[];

// Global variable 
extern int attempts;		// Number of attempts
extern int LinesActive;			// Number of manufacturing lines
extern int ordS;

extern void charge_client();
extern void createSharedMem();
extern void destroySharedMem();
extern void dispatch_factory_lines();
extern void get_address();
extern void get_pymnt_method();
extern void increment_attempts();
extern void ind_line();
extern void refund();
extern void reset_attempts();
extern void shut_down_factory_lines();
extern void start_warranty();
extern void update_stats(stats value);


#endif

