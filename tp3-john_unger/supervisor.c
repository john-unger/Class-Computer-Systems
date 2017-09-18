//John Paul Smithdeal and John Unger
//November 17, 2015

#ifndef supervisor_h
#define supervisor_h

#include "hardware.h"

int main(int argc, char *argv[])
{
	int LinesActive = atoi(argv[1]);
	printf("The number of active lanes: %d\n", LinesActive);
	int lines = atoi(argv[1]);
	//Shared memory variables
	int mem_id;
	int index;
	int mem_flag;
	key_t mem_key;

	shared_mem_data *ref;

	//Reference to struct for defining message queue properties
	int q_id;
	int msgStatus;
	key_t q_key;

	msgBuf q;

	//Shared memory creation and semaphore initialization starts here
	mem_key = MEM_KEY;
	mem_flag = /*IPC_CREAT |*/ S_IRUSR | S_IWUSR;

	mem_id = shmget(mem_key, mem_size, mem_flag);
	if (mem_id != -1)
	{
		printf("\nShared memory segment '0x%X' %s %d\n", mem_key,
				"successfully created/found for the SUPERVISOR with id", mem_id);
	}
	else
	{
		printf("\nFailed to create/ find shared memory '0x%X'.\n", mem_key);
		perror("Reason");
		exit(-1);
	}

	ref = shmat(mem_id, NULL, 0);
	if (ref == (shared_mem_data *) -1)
	{
		printf("\nFailed to attach shared memory id=%d\n", mem_id);
		exit(-1);
	}

	//Message queue creation starts here
	q_key = BASE_MAILBOX_NAME;
	q_id = msgget(q_key, 0600);

	int dns = 0;
	int database[(lines * 3)];
	int indx = 0;

	while (LinesActive > 0)
	{
		msgStatus = msgrcv(q_id, &q, MSG_INFO_SIZE, 0, 0);

		if (msgStatus < 0)
		{
			printf("Failed to receive message from factory line number %d. Error code: %d\n", q_id, errno);
			exit(-2);
		}

		if (q.contents.ptFlg == true)
		{
			//			printf("\n\nITTT HAASSS BEEEN EXECUTED!!!!!   %d   %d\n\n", q.contents.parts_made, q.contents.total_made);
			//			q.contents.total_made += q.contents.parts_made;
		}
		else
		{
			indx = q.contents.factory_id *3;
			indx = indx - 3;
			database[indx] = q.contents.factory_id;
			indx++;
			database[indx] = q.contents.total_made;
			indx++;
			database[indx] = q.contents.iter;

			dns++;
			//printf("THE LANE DELETED: %d\n", q.contents.factory_id);
			//sem_wait(& ref->print);
			kill(q.contents.sender);
			LinesActive--;

			if(dns == lines)
			{
				//printf("LINE 86\n");
				sem_post(& ref->PSsem);
				sem_wait(& ref->print);
				int in;
				indx = 0;
				//printf("LINE 92\n");
				for (in = 0; in < lines; in++)
				{
					indx = in *3;
					printf("Terminating factory line %d, which has made %d parts, in %d iterations.\n", database[indx], database[(indx+1)], database[(indx+2)]);
				}

			}
		}
	}



	//sem_post(& ref->PSsem);
	sem_post(& ref->destroy);
	shmdt(ref); //<---------------------
	return 0;
}

/*
 * LinesActive = 5;
 * While (LinesActive > 0)
 * {
 * Receive a message from the mailbox;
 * If(Production Message)
 * 		update production aggregates (num-items-built, num-iterations)
 * elseif (Termination Message)
 * 		LinesActive--;
 * else
 * 		discard this unsupported message
 * }
 *
 * Inform the Parent that all factory lines are done
 * Wait for permission from the Parent to start printing production aggregates
 * Print production aggregates
 * Inform the Parent that Supervisor is done
 *
 * Hint: semaphore(s) might be needed to inform/signal
 */
#endif

