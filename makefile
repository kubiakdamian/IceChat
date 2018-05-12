
SRCICE = ice/chat.cpp src/LibsIce/UserImpl.cpp src/LibsIce/ServerImpl.cpp src/LibsIce/RoomFactoryImpl.cpp src/LibsIce/RoomImpl.cpp

all: client server factory

#-wall - włącza pokazywanie ostrzezen kompilatora
# -g  - dodaje informacje debugowania do pliku wykonywalnego
client: 
	g++ -g -Wall -I src/Client -I ice -I src/LibsIce -I src/Server -I src/RoomFactory -o client  $(SRCICE) src/Client/Client.cpp  src/Client/main.cpp src/Client/Menu.cpp -pthread -lIce  -std=c++0x

server:
	g++ -g -Wall -I src/Client -I ice -I src/LibsIce -I src/Server -I src/RoomFactory -o server  $(SRCICE) src/Server/Server.cpp -pthread -lIce  -std=c++0x

factory:
	g++ -g -Wall -I src/Client -I ice -I src/LibsIce -I src/Server -I src/RoomFactory -o factory $(SRCICE) src/RoomFactory/main.cpp src/RoomFactory/Factory.cpp -pthread -lIce  -std=c++0x

.cpp.o:
		g++ -g -Wall -I src/Client -I ice -I src/LibsIce -I src/Server -I src/RoomFactory -o $< -o $@

clean:
		$(RM) *.o *~ client
		$(RM) *.o *~ server
		$(RM) *.o *~ factory