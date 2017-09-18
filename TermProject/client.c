#ifndef client_c
#define client_c

#include "hardware.h"

#include "mySocket.h"
#define MAXBUFLEN   256

int main(int argc, char *argv[])
{
	char	*host    = "localhost";    /* host to use if none supplied	*/
	char	*service = "daytime";      /* default service name	        */
	char    *msg     = "Hello there Aboutabl" ;
	int	    s, n;                      /* socket descriptor, read count */

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

	fprintf(stderr , "DAYTIME client sending '%s'\n" , msg ) ;
	/* must send the \0 at end of msg, too */
	sendto( s, (void *) msg, strlen(msg)+1 , NULL , 0);


	n = recvfrom( s, MAXBUFLEN , NULL , 0 );
	if ( n <= 0 )
		err_sys( "Failed to get the daytime from the server" );

	printf( "DAYTIME client received %d chars in\n" , n );
	exit(0);
}

#endif
