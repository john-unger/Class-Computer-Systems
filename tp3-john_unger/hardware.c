//John Paul Smithdeal and John Unger
//October 27, 2015

#ifndef hardware_c
#define hardware_c

#include "hardware.h"

// Random generated size of order
int LinesActive = 5;
int attempts = 0;
int ordS;

/* this variable is our LinesActive */
pthread_t thrd[5];

// Initialization of semaphore
sem_t s;

int mem_id;
shared_mem_data *ref;
int q_id;


void createSharedMem()
{
	int mem_flag;
	key_t mem_key;

	//Reference to struct for defining message queue properties
	key_t q_key;

	msgBuf *q;

	//Shared memory creation and semaphore initialization starts here
	mem_key = MEM_KEY;
	mem_flag = IPC_CREAT | S_IRUSR | S_IWUSR;

	mem_id = shmget(mem_key, mem_size, mem_flag);

	if (mem_id != -1)
	{
		printf("\nShared memory segment '0x%X' %s %d\n", mem_key,
				"successfully created/found with id", mem_id);
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


	//------------------------------------------------------------------------

	//Message queue creation starts here
	q_key = BASE_MAILBOX_NAME;
	q_id = msgget(q_key, IPC_CREAT | 0600);

	printf("parent_pid = %d\n\n", getpid());

	ref->order_size = ordS;
	printf("The order size on the Shared Memory: %d\n", ref->order_size);
}
void destroySharedMem()
{
	// Destroy the semaphores
	sem_destroy(&(ref->OSsem));
	sem_destroy(&(ref->destroy));
	sem_destroy(&(ref->PSsem));
	sem_destroy(&(ref->print));

	shmdt(ref); //<---------------------
	shmctl(mem_id, IPC_RMID, NULL); //<----------WILL NEED THESE TWO LATER TO DESTROY SHARED MEMORY
	msgctl(q_id , IPC_RMID , NULL) ; //<------WILL NEED THIS LATER TO DESTORY MESSAGE QUEUE WHEN DONE
}

void charge_client()
{
	printf("Charging Client\n");
}

void dispatch_factory_lines()
{
	int i;
	pid_t superID;

	printf("Dispatching Factory lines\n");
	// Initialization of random times
	srandom(time(NULL));



	printf("\nCreating the Shared Memory\n");
	createSharedMem();



	// Initialize the semaphores
	sem_init(&(ref->OSsem), 1, 1);
	sem_init(&(ref->destroy), 1, 1);
	sem_init(&(ref->PSsem), 1, 0);
	sem_init(&(ref->print), 1, 0);


	//-------------------------------------------------------------------------------
	char command[100];
	int rnd;
	sem_wait(& ref->destroy);

	/* Create 5 Factory Lane Processes */
	for (i = 1; i <= LinesActive; i++)
	{
		char c = (char) i;

		rnd = makeRandom();
		int cp;
		int dr;
		cp = rnd % (1000);
		dr = rnd / 1000;

		pid_t child_pid;
		child_pid = fork();
		switch (child_pid)
		{
		case 0:
			printf("LineNumber: %d\n", i);
			snprintf(command, 100, "./factoryline %d %d %d", i, cp, dr);

			printf("Create the Factory-Line\n");
			if (execlp("gnome-terminal", "LineVterm", "-x", "/bin/bash",
					"-c", command, NULL) < 0)
			{
				perror("execlp FactoryLine Failed\n");
				exit(-1);
			}

			exit(i);
			break;

		case -1:
			/* fork() failed */
			printf("Fork Failed\n");
			break;
		default:
			printf("Parent Process\n");
			break;
		}
		wait(i);
	}
	printf("Create the Supervisor\n");

	i--;

	/* Create the SuperVisor's Process */
	superID = fork();
	if (superID == 0)	/* the Supervisor child process*/
	{
		snprintf(command, 100, "./supervisor %d", i);

		if (execlp("gnome-terminal", "SuperVterm", "-x", "/bin/bash",
				"-c", command, NULL) < 0)
		{
			perror("execlp Supervisor Failed");
			exit(-1);
		}
		exit(6);
	}

	wait(6);
	puts("");

	sem_wait(& ref->PSsem);
	sem_post(& ref->print);



	printf("Waiting on destroy\n");
	sem_wait(& ref->destroy);

}

int makeRandom()
{
	// random number between 10 - 50
	int cp;
	cp = random();
	cp = (cp % (41)); // TODO 41
	cp = cp + 10;		// TODO 10

	// random number between 100,000 - 500,000 (in microseconds)
	// that is 100 - 500 milliseconds
	int dr;
	dr = random();
	dr = (dr % (401));
	dr = 100000 *(dr + 100);

	return (cp + dr);
}

void get_address()
{
	printf("\nGetting Address\n");
}

void get_pymnt_method()
{
	printf("\nGetting Payment Method\n");
}

void increment_attempts()
{
	printf("\nIncrement Attempts\n");
	attempts++;
}

void refund()
{
	printf("\nRefunding Money\n");
}

void reset_attempts()
{
	printf("\nResetting Attempts");
	attempts = 0;
}

void shut_down_factory_lines()
{
	printf("\nShutting Down factory Lines\n");

	printf("\nDestroying the Shared Memory\n");
	destroySharedMem();
}

void start_warranty()
{
	printf("\nStarting Warranty\n");
}

void update_stats(stats value)
{
	char *str[] = {"DONE","FAIL","LOST"};
	printf("New Status: %s\n", str[value]);
}

#endif

