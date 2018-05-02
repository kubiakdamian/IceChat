all: client server Client.o Server.o

Server.o: Server.cpp
	c++ -I. -c Printer.cpp Server.cpp
	
Client.o: Client.cpp
	c++ -I. -c Printer.cpp Client.cpp

client: Client.o
	c++ -o client Printer.o Client.o -pthread -lIce

server: Server.o
	c++ -o server Printer.o Server.o -pthread -lIce
