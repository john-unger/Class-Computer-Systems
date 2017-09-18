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

//	//Shared memory variables
//	int mem_id;
//	int index;
//	int mem_flag;
//	key_t mem_key;
//
//	shared_mem_data *ref;
//
//	msgBuf *q;
//
//	//Shared memory creation and semaphore initialization starts here
//	mem_key = MEM_KEY;
//	mem_flag = /*IPC_CREAT | */S_IRUSR | S_IWUSR;
//
//	mem_id = shmget(mem_key, mem_size, mem_flag);
//	if (mem_id != -1)
//	{
//		printf("\nShared memory segment '0x%X' %s %d\n", mem_key,
//				"successfully created/found for ACCEPTING with id", mem_id);
//	}
//	else
//	{
//		printf("\nFailed to create/ find shared memory '0x%X'.\n", mem_key);
//		perror("Reason: ");
//		exit(-1);
//	}
//
//	ref = shmat(mem_id, NULL, 0);
//	if (ref == (shared_mem_data *) -1)
//	{
//		printf("\nFailed to attach shared memory id=%d\n", mem_id);
//		exit(-1);
//	}

	// random number between 1000- 2000
	srandom(time(NULL));
	int r = random();
	r = (r % (1001));
	r = r + 1000;
	ordS = r;
	printf("Order Size: %d", ordS);

	//shmdt(ref); //<---------------------

	reset_attempts();
	return &processing;
}



#endif

