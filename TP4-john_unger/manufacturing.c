//John Paul Smithdeal and John Unger
//December 5, 2015

#ifndef manufacturing_c
#define manufacturing_c

#include "manufacturing.h"
#include "hardware.h"
#include "statemodel.h"
#include <pthread.h>
#include <semaphore.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "mySocket.h"

state_t manufacturing = {
		default_event_handler,
		default_event_handler,
		default_event_handler,
		manuf_failed,
		manuf_completed,
		default_event_handler,
		default_event_handler,
		entry_to,
		exit_from,
};

state_t* manuf_failed()
{
	printf("The factory line(s) failed to manufacture ALL requested replicas of the item being ordered\n");
	update_stats(FAIL);
	return &accepting;
}

state_t* manuf_completed()
{
	printf("The factory line(s) successfully manufactured ALL requested replicas of the item being ordered\n");

	charge_client();
	return &shipping;
}

int server()
{
	struct sockaddr_in  fsin;   /* the from adnumbers->durationess of a client */
	attributes *numbers = malloc(sizeof(attributes));
	int	    sock;               			/* server socket                */
	unsigned int    alen;       			/* from-adnumbers->durationess length          */
	int lineNum = 1;

	sock = serverUDPsock(port);

	while (1)
	{
		alen = sizeof(fsin);
		fprintf(stderr , "Server waiting for client requests...\n" ) ;
		if ( recvfrom( sock, (attributes *) numbers , sizeof(*numbers) , 0, (SA *) &fsin, &alen ) < 0 )
			err_sys( "recvfrom" ) ;

		fprintf(stderr , "Server received a request from a client: code %d\n" , numbers->msg ) ;

		if ((numbers->msg) == 1)
		{
			// random number between 10 - 50
			numbers->capacity = random();
			numbers->capacity = (numbers->capacity % (491));
			numbers->capacity = numbers->capacity + 10;

			// random number between 100,000 - 500,000 (in microseconds)
			// that is 100 - 500 milliseconds
			numbers->duration = random();
			numbers->duration = (numbers->duration % (401));
			numbers->duration = 1000 *(numbers->duration + 100);

			numbers->id = lineNum;
			lineNum++;

			(numbers->iterations) = 0;
			(numbers->totalMade) = 0;

			fprintf(stderr , "Server sending line information:\nID = %d \nCapacity = %d\nDuration = %d\n" , numbers->id, numbers->capacity , numbers->duration ) ;

			if (sendto( sock , (attributes *) numbers , sizeof(*numbers) , 0 , (SA *) &fsin, alen ) < 0)
				printf("cap FAILED\n");
		}

		if ((numbers->msg) == 2)
		{
			printf("\nOrder Size: %d\n", order_size);
			if (order_size > 0)
			{
				(numbers->iterations)++;

				if (order_size < numbers->capacity)
				{
					printf("Server Command: make less than capacity\n");

					numbers->toMake = order_size;
					(numbers->totalMade) += (numbers->toMake);

					if (sendto( sock , (attributes *) numbers , sizeof(*numbers) , 0 , (SA *) &fsin, alen ) < 0)
						printf("Less than capacity has FAILED\n");

					order_size = 0;
				}
				else
				{
					numbers->toMake = numbers->capacity;
					(numbers->totalMade) += (numbers->toMake);

					printf("Server Command: make capacity\n");

					if (sendto( sock , (attributes *) numbers , sizeof(*numbers) , 0 , (SA *) &fsin, alen ) < 0)
						printf("Greater than capacity has FAILED\n");

					order_size = order_size - numbers->toMake;
				}
			}
			else
			{
				numbers->toMake = 0;
				printf("Server Command: Terminate Factory Line\n");

				if (sendto( sock , (attributes *) numbers , sizeof(*numbers) , 0 , (SA *) &fsin, alen ) < 0)
					printf("All parts have been made. Operation FAILED\n");
			}
		}

		if ((numbers->msg) == 3)
		{
			printf("\n-------------\nAll parts have been made\nLine: %d\nHas made: %d parts\nIn %d Iterations\n-------------\n\n",
					numbers->id, numbers->totalMade, numbers->iterations);
			lineNum--;
			if (lineNum == 1)
				break;
		}
	}

	free(numbers);
	return(0);
}

void entry_to()
{
	dispatch_factory_lines();
	server();
}

void exit_from()
{
	shut_down_factory_lines();
}

#endif

