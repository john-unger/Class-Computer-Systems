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
	attributes numbers;
	char *msg1 = "one";
	char *msg2 = "two";
	char *msg3 = "three";
//	int toMake;
//	int cap;
//	int dur;
//	int id;

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

	numbers.msg = msg1;

	fprintf(stderr , "Client sending request number %s...\n", numbers.msg) ;
	/* must send the \0 at end of msg, too */

	if (sendto( s , (void *) &numbers , sizeof(numbers), MAXBUFLEN, NULL, 0 ) < 0)
		printf("cap FAILED\n");


	if ( recvfrom( s, (void *) &numbers , sizeof(numbers)+1 , NULL, 0 ) < 0 )
		err_sys( "Failed to get information from the server\n" );
	else
	{
//		cap = numbers.capacity;
//		dur = numbers.duration;
//		id = numbers.id;

		printf( "Client received capacity: %d\nClient receive duration: %d\nClient received ID: %d\n",
				numbers.capacity, numbers.duration, numbers.id);
	}

	while (1)
	{
		numbers.msg = msg2;

		fprintf(stderr , "\nClient sending request number %s...\n", numbers.msg) ;
		/* must send the \0 at end of msg, too */
		sendto( s, (void *) &numbers , sizeof(numbers)+1, MAXBUFLEN, NULL , 0);

		if ( recvfrom( s, (void *) &numbers , sizeof(numbers)+1 , NULL, 0 ) < 0 )
			err_sys( "Failed to receive number to make\n" );
		else
			printf( "Client received number of parts to make: %d\n" , numbers.toMake );

		//toMake = numbers.toMake;

		printf("\nvalue of capacity: %d\nvalue of making: %d\n", numbers.capacity, numbers.toMake);

		if (numbers.toMake == 0)
		{
			numbers.msg = msg3;

			fprintf(stderr , "Client sending termination code: %s\n", numbers.msg) ;
			/* must send the \0 at end of msg, too */
			sendto( s, (void *) &numbers , sizeof(numbers)+1, MAXBUFLEN, NULL , 0);
			exit(0);
		}
		else
		{
			printf("\n%d\n", numbers.duration);
			usleep(numbers.duration);
		}
	}
}

#endif
