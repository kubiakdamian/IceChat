
SRC = ice/chat.cpp src/IceChat/UserImpl.cpp src/IceChat/ServerImpl.cpp src/IceChat/RoomFactoryImpl.cpp src/IceChat/RoomImpl.cpp

all: client server factory

client: 
	g++ -g -I src/Client -I ice -I src/IceChat -I src/Server -I src/RoomFactory -o client  $(SRC) src/Client/Client.cpp  src/Client/main.cpp src/Client/Menu.cpp -pthread -lIce  -std=c++0x

server:
	g++ -g -I src/Client -I ice -I src/IceChat -I src/Server -I src/RoomFactory -o server  $(SRC) src/Server/Server.cpp -pthread -lIce  -std=c++0x

factory:
	g++ -g -I src/Client -I ice -I src/IceChat -I src/Server -I src/RoomFactory -o factory $(SRC) src/RoomFactory/main.cpp src/RoomFactory/Factory.cpp -pthread -lIce  -std=c++0x

.cpp.o:
	g++ -g -I src/Client -I ice -I src/IceChat -I src/Server -I src/RoomFactory -o


