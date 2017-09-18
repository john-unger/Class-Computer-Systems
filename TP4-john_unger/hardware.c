//John Paul Smithdeal and John Unger
//December 5, 2015

#ifndef hardware_c
#define hardware_c

#include "hardware.h"

// Random generated size of order
int LinesActive = 5;
int order_size;
int attempts = 0;

unsigned short port = 77 ; 				/* service name or port number  */


void charge_client()
{
	printf("Charging Client\n");
}

void dispatch_factory_lines()
{
	printf("Dispatching Factory lines\n");
}

void get_address()
{
	printf("Getting Address\n");
}

void get_pymnt_method()
{
	printf("Getting Payment Method\n");
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
	printf("Resetting Attempts\n");
	attempts = 0;
}

void shut_down_factory_lines()
{
	printf("\nShutting Down factory Lines\n");
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

