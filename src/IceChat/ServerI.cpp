#include "ServerI.h"

namespace IceChat {
    RoomPrx ServerI::CreateRoom(const string& name, const ::Ice::Current&) {
        for (auto &room : roomList) {
            if (room->getName() == name) {
                throw RoomAlreadyExists();
            }
        }

        RoomFactoryPrx roomFactory = roomFactoryList.back();
        RoomPrx room = roomFactory->createRoom(name);
        roomList.push_back(room);
        cout << "Added room: " << name << endl;
        return room;
    }

    RoomList ServerI::getRooms(const ::Ice::Current&) {
        return roomList;
    }

    RoomPrx ServerI::FindRoom(const string& name, const ::Ice::Current& ) {
        for (auto &room : roomList) {
            if (room->getName() == name) {
                return room;
            }
        }
        throw RoomDoesntExist();   
    }

    void ServerI::RegisterRoomFactory(const RoomFactoryPrx& roomFactory, const ::Ice::Current&) {
        roomFactoryList.push_back(roomFactory);
        cout << "Room factory registred " << endl;
    }

    void ServerI::UnregisterRoomFactory(const RoomFactoryPrx& roomFactory, const ::Ice::Current&) {
        for (auto registredFactoryIt = roomFactoryList.begin(); registredFactoryIt != roomFactoryList.end(); ) {
            if (*registredFactoryIt == roomFactory) {
                registredFactoryIt = roomFactoryList.erase(registredFactoryIt);
            } else {
                ++registredFactoryIt;
            }
        }
    }
}