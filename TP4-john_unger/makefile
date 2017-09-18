driver: driver.o state.o hardware.o statemodel.o accepting.o manufacturing.o processing.o shipping.o mySocket.o
	gcc driver.o state.o hardware.o statemodel.o accepting.o manufacturing.o processing.o shipping.o mySocket.o -lpthread -o driver

driver.o: driver.c hardware.h statemodel.h
	gcc -c driver.c

hardware.o: hardware.c hardware.h
	gcc -c hardware.c -o hardware.o

statemodel.o: hardware.h statemodel.h statemodel.c 
	gcc -c statemodel.c

state.o: state.h state.c
	gcc -c state.c -o state.o

accepting.o: state.h accepting.h accepting.c
	gcc -c accepting.c

manufacturing.o: state.h manufacturing.h manufacturing.c
	gcc -c manufacturing.c

processing.o: state.h processing.h processing.c
	gcc -c processing.c

shipping.o: state.h shipping.h shipping.c
	gcc -c shipping.c
	
clean:
	rm *.o ; rm driver ; rm client
	
client: client.o mySocket.o
	gcc client.o mySocket.o -o client
	
client.o: hardware.h mySocket.h client.c
	gcc -c client.c

mySocket.o: mySocket.h hardware.h mySocket.c
	gcc -c mySocket.c
	
cleanc:
	rm client.o ; rm client

cleand:
	rm *.o ; rm driver

