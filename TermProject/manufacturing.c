//John Paul Smithdeal and John Unger
//October 27, 2015

#ifndef manufacturing_c
#define manufacturing_c

#include "manufacturing.h"
#include "hardware.h"
#include "statemodel.h"
#include <pthread.h>
#include <semaphore.h>

#include "mySocket.h"
#define MAXBUFLEN   256

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
	struct sockaddr_in  fsin;   /* the from address of a client */
	unsigned short port = 15 ;  /* service name or port number  */
	char    buf[MAXBUFLEN];     /* "input" buffer; any size > 0 */
	int	    sock;               /* server socket                */
	unsigned int    alen;       /* from-address length          */

	sock = serverUDPsock(port);

	while (1)
	{
		alen = sizeof(fsin);
		fprintf(stderr , "Manufacturing server waiting\n" ) ;
		if ( recvfrom( sock, buf, MAXBUFLEN , 0, (SA *) &fsin, &alen ) < 0 )
			err_sys( "recvfrom" ) ;
		fprintf(stderr , "Manufacturing server received '%s'\n" , buf ) ;

		fprintf(stderr , "Manufacturing server sending\n" ) ;
		sendto( sock , 0 , (SA *) &fsin, alen );
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

