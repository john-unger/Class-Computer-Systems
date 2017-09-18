
void err_sys(const char* x) ;
void err_quit(const char* x)  ;
int clientUDPsock(const char *host, const char *service ) ;
int serverUDPsock(const unsigned short port) ;

typedef struct sockaddr SA ;

#define MAXBUFLEN   256

typedef struct{
	int capacity;	// How many parts the line can make
	int toMake;		// How many parts the line is actually doing
	int duration;	// How long the line has to sleep

	int iterations;	// How many times a line has executed (with parts having done)
	int totalMade;	// How many items the specific line has produced

	int id;			// The factory line ID number
	int msg;		// What type of message is being sent back and forth

}attributes;


#define BASEPORT 50000   /* port base for non-root servers */

