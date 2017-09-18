//John Paul Smithdeal and John Unger
//October 27, 2015

#ifndef driver_c
#define driver_c

#include "hardware.h"
#include "statemodel.h"
#include <stdio.h>

int main()
{
   printf("Current State is: ACCEPTING\n");
   
   char input;
   
   input = getchar();
   
   while(input != 'X')
      {
      switch(input)
         {
            case 'O':
            handle_event(ORDER_RCVD);
            break;
            case 'V':
            handle_event(VALID_PYMNT);
            break;
            case 'I':
            handle_event(INVALID_PYMNT);
            break;
            case 'F':
            handle_event(MANUF_FAILED);
            break;
            case 'C':
            handle_event(MANUF_COMPLETED);
            break;
            case 'R':
            handle_event(RECEIVED);
            break;
            case 'L':
            handle_event(LOST_PACKAGE);
            break;
         }
      
      input=getchar();
      }
   
   return 0;
}

#endif

