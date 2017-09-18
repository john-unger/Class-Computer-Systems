//John Paul Smithdeal and John Unger
//October 27, 2015

#ifndef hardware_c
#define hardware_c

#include "hardware.h"

// Random generated size of order
int LinesActive = 5;
int order_size;
int attempts = 0;

void charge_client()
{
	printf("Charging Client\n");
}

void dispatch_factory_lines()
{
	printf("Dispatching Factory lines\n");
}

int makeRandom()
{
	// random number between 10 - 50
	int cp;
	cp = random();
	cp = (cp % (41));
	cp = cp + 10;

	// random number between 100,000 - 500,000 (in microseconds)
	// that is 100 - 500 milliseconds
	int dr;
	dr = random();
	dr = (dr % (401));
	dr = 1000 *(dr + 100);

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
	printf("\nResetting Attempts\n");
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

