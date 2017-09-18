//John Paul Smithdeal and John Unger
//October 27, 2015

#ifndef manufacturing_c
#define manufacturing_c

#include "manufacturing.h"
//#include "hardware.h"
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
	struct sockaddr_in  fsin;   /* the from adnumbers.durationess of a client */
	attributes numbers;
	unsigned short port = 77 ; 				/* service name or port number  */
	//char    buf[MAXBUFLEN];     			/* "input" buffer; any size > 0 */
	int	    sock;               			/* server socket                */
	unsigned int    alen;       			/* from-adnumbers.durationess length          */
	int lineNum = 1;
//	int toMake;
//	int capacity;

	sock = serverUDPsock(port);

	while (1)
	{
		alen = sizeof(fsin);
		fprintf(stderr , "Server waiting for client requests...\n" ) ;
		if ( recvfrom( sock, (void *) &numbers , sizeof(numbers)+1  , 0, (SA *) &fsin, &alen ) < 0 )
			err_sys( "recvfrom" ) ;

		fprintf(stderr , "Server received a request from a client: code %s\n" , (char) (numbers.msg) ) ;

		if (strcmp((char *) &(numbers.msg), "one") == 0)
		{
			// random number between 10 - 50
			numbers.capacity = random();
			numbers.capacity = (numbers.capacity % (41));
			numbers.capacity = numbers.capacity + 10;

			// random number between 100,000 - 500,000 (in microseconds)
			// that is 100 - 500 milliseconds
			numbers.duration = random();
			numbers.duration = (numbers.duration % (401));
			numbers.duration = 100 *(numbers.duration + 100);

			numbers.id = lineNum;
			lineNum++;

			fprintf(stderr , "Server sending line information:\nID = %d \nCapacity = %d\nDuration = %d\n" , numbers.id, numbers.capacity , numbers.duration ) ;

			if (sendto( sock , (void *) &numbers , sizeof(numbers)+1, 0 , (SA *) &fsin, alen ) < 0)
				printf("cap FAILED\n");
		}

		if (strcmp((char *) &(numbers.msg), "two") == 0)
		{
			if (order_size > 0)
			{
				printf("\nOrder size is greater than 0\n");

				if (order_size <= numbers.capacity)
				{
					printf("\nOrder size is < cap\n");

					numbers.toMake = order_size;

					if (sendto( sock , (void *) &numbers , sizeof(numbers)+1, 0 , (SA *) &fsin, alen ) < 0)
						printf("Less than capacity has FAILED\n");

					order_size = 0;
				}
				else
				{
					numbers.toMake = numbers.capacity;

					printf("\nOrder size is greater than cap\n");

					if (sendto( sock , (void *) &numbers , sizeof(numbers)+1, 0 , (SA *) &fsin, alen ) < 0)
						printf("Greater than capacity has FAILED\n");

					order_size = order_size - numbers.toMake;

					printf("\n%d\n%d\n", order_size, numbers.toMake);
				}
			}
			else
			{
				printf("\nNone to make\n");

				numbers.toMake = 0;

				if (sendto( sock , (void *) &numbers , sizeof(numbers)+1 , 0 , (SA *) &fsin, alen ) < 0)
					printf("ALl parts have been made. Operation FAILED\n");
			}
		}

		if (strcmp((char *) &(numbers.msg), "three") == 0)
		{
			printf("All parts have been made\n");
		}
	}
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

