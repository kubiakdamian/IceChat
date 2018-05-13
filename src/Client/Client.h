#ifndef CLIENT_H
    #define CLIENT_H

    #include <thread>
    #include <Ice/Ice.h>
    #include "chat.h"
    #include "UserI.h"
    #include "Ports.h"
    
    using namespace std;
    using namespace Chat;
    using namespace IceChat;

    namespace ClientApp {
        class Client {
            public:
                Client(const string&);
                void createRoom();
                void printRooms();
                void joinRoom();
                void printRoomsMembers();
                void leaveRoom();
                void sendPrivateMessage();
                void sendMessage();
                void changeNickname();
                ~Client();
            private:
                string username;
                UserPrx user;
                ServerPrx server;
                Ice::CommunicatorPtr iceCommunicator;
                Ice::ObjectAdapterPtr adapter;
                Ports ports;
                RoomList userRooms;

                void createUser();
                string getNameOfTheRoom();
                void scrollConsole();
                UserList getRoomsMembers();
                void registerUser(string);
                void initializeServer();
        }; 
    }

#endif