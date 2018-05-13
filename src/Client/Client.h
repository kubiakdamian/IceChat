#ifndef CLIENT_H
    #define CLIENT_H

    #include <thread>
    #include <Ice/Ice.h>
    #include "chat.h"
    #include "UserImpl.h"
    #include "Ports.h"
    
    using namespace std;
    using namespace Chat;
    using namespace LibsIce;

    namespace ClientApp {
        class Client {
            public:
                Client(const string&);
                void createRoom() const;
                void printRooms() const;
                void joinRoom();
                void printRoomsMembers() const;
                void leaveRoom();
                void sendPrivateMessage() const;
                void sendMessage() const;
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
                string getNameOfTheRoom() const;
                void scrollConsole() const;
                UserList getUsersInRoom() const;
                void registerUser(string);
        }; 
    }

#endif