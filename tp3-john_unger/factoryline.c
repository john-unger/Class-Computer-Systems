//John Paul Smithdeal and John Unger
//November 17, 2015

#ifndef factoryline_c
#define factoryline_c

#include "hardware.h"

int main(int argc, char *argv[])
{

	key_t mem_key;
	key_t q_key;
	msgBuf prts;
	shared_mem_data *ref;

	int cp;
	int dr;
	int lane;
	int mem_flag;
	int mem_id;
	int q_id;

	lane = atoi(argv[1]);
	cp = atoi(argv[2]);
	dr = atoi(argv[3]);

	mem_key = MEM_KEY;
	mem_flag = /*IPC_CREAT |*/ S_IRUSR | S_IWUSR;

	mem_id = shmget(mem_key, mem_size, mem_flag);

	if (mem_id != -1)
	{
		printf("\nShared memory segment '0x%X' %s %d\n", mem_key,
				"successfully created/found for the FACTORY LINE with id", mem_id);
	}
	else
	{
		printf("\nFailed to create/ find shared memory '0x%X'.\n", mem_key);
		perror("Reason: ");
		exit(-1);
	}

	ref = shmat(mem_id, NULL, 0);
	if (ref == (shared_mem_data *) -1)
	{
		printf("\nFailed to attach shared memory id=%d\n", mem_id);
		exit(-1);
	}

	prts.contents.ptFlg = true;

	//Message queue creation starts here
	q_key = BASE_MAILBOX_NAME;
	q_id = msgget(q_key, 0600);

	lane = atoi(argv[1]);
	cp = atoi(argv[2]);
	dr = atoi(argv[3]);

	prts.contents.factory_id = lane;
	prts.contents.cap = cp;
	prts.contents.dur = dr;

	prts.contents.iter = 0;
	prts.contents.total_made = 0;

	while (ref->order_size != 0)
	{
		sem_wait(&(ref->OSsem));
		printf("The old order size: %d\n", ref->order_size);

		// Even if order size is smaller than capacity, it is still to wait for the time
		if (ref->order_size < prts.contents.cap)
		{
			prts.contents.parts_made = ref->order_size;
			ref->order_size = 0;
		}
		else
		{
			ref->order_size = ref->order_size - prts.contents.cap;
			prts.contents.parts_made = prts.contents.cap;
		}
		prts.contents.total_made += prts.contents.parts_made;
		prts.contents.iter++;
		sem_post(&(ref->OSsem));

		usleep(prts.contents.dur);

		if (msgsnd(q_id, &prts, MSG_INFO_SIZE, 0) < 0)
		{
			perror("\nFailed to Send the Message, because: ");
		}
//		else
//			printf("Message sent successful.\n");

		// message the supervisor for the current progress
	}

	prts.contents.ptFlg = false;
	//sem_post(& ref->print);
	if (msgsnd(q_id, &prts, MSG_INFO_SIZE, 0) < 0)
	{
		perror("\nFailed to Send the Message, because: ");
	}
	else
	{
		printf("Message sent successful.\nWith a total parts made: %d from Lane: %d", prts.contents.total_made, prts.contents.factory_id);
	}

	shmdt(ref); //<---------------------

	// now the factory is done
	exit(1);
}

#endif
