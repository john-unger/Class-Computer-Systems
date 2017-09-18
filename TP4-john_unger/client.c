//John Paul Smithdeal and John Unger
//December 5, 2015

#ifndef client_c
#define client_c

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include "mySocket.h"

int main(int argc, char *argv[])
{
	char	*host    = "localhost";    /* host to use if none supplied	*/
	char	*service = "FactoryLine";      /* default service name	        */
	int	    s;                      /* socket descriptor, read count */
	attributes *numbers = malloc(sizeof(attributes));

	switch (argc)
	{
	case 1:
		break;
	case 3:
		service = argv[2];
		/* FALL THROUGH */
	case 2:
		host = argv[1];
		break;
	default:
		fprintf(stderr, "usage: %s [host [port]]\n" , argv[0] );
		exit(1);
	}
	s = clientUDPsock( host , service );
	/* socket will always send to host:service */
	/* Therefore, use  in sendto( .... , NULL , 0) */

	numbers->msg = 1;

	fprintf(stderr , "Client sending request number %d...\n", numbers->msg) ;
	/* must send the \0 at end of msg, too */

	if (sendto( s , (attributes *) numbers , sizeof(*numbers), MAXBUFLEN, NULL, 0 ) < 0)
		printf("cap FAILED\n");


	if ( recvfrom( s, (attributes *) numbers , sizeof(*numbers) , NULL, 0 ) < 0 )
		err_sys( "Failed to get information from the server\n" );
	else
	{
		printf( "Client received capacity: %d\nClient receive duration: %d\nClient received ID: %d\n",
				numbers->capacity, numbers->duration, numbers->id);
	}

	while (1)
	{
		numbers->msg = 2;

		fprintf(stderr , "\nClient sending request number %d...\n", numbers->msg) ;
		/* must send the \0 at end of msg, too */
		sendto( s, (attributes *) numbers , sizeof(*numbers), MAXBUFLEN, NULL , 0);

		if ( recvfrom( s, (attributes *) numbers , sizeof(*numbers) , NULL, 0 ) < 0 )
			err_sys( "Failed to receive number to make\n" );
		else
			printf( "Client received number of parts to make: %d\n" , numbers->toMake );

		//toMake = numbers->toMake;

		printf("Value of capacity: %d\nValue of making: %d\n", numbers->capacity, numbers->toMake);

		if (numbers->toMake == 0)
		{
			numbers->msg = 3;

			fprintf(stderr , "\n--------\nClient sending termination code: %d\n"
					"Line %d has completed its portion of the order.\n"
					"Iterations: %d\n"
					"Total Items produced: %d\n"
					"Total Duration: %d milliseconds\n\n",
					numbers->msg, numbers->id, numbers->iterations, numbers->totalMade, ((numbers->iterations)*(numbers->duration))/1000 );
			/* must send the \0 at end of msg, too */
			sendto( s,(attributes *) numbers , sizeof(*numbers), MAXBUFLEN, NULL , 0);
			exit(0);
		}
		else
		{
			printf("Sleeping\n");
			usleep(numbers->duration);
		}
	}

	free(numbers);
}

#endif
