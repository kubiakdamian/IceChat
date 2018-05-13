#include "RoomFactoryI.h"

namespace IceChat {
    RoomList RoomFactoryI::getRooms(const ::Ice::Current&) {
        return roomList;
    }

    RoomPrx RoomFactoryI::createRoom(const string& name, const ::Ice::Current&) {
        RoomPtr object = new RoomI(name);
        cout << "RoomFactory::Creating room " << name << endl;
        int port = ports.getRandomPort();

        adapter = ic->createObjectAdapterWithEndpoints("SimpleRoom" + name, "default -p " + to_string(port));
        adapter->add(object, ic->stringToIdentity("SimpleRoom" + name));
        adapter->activate();
        Ice::ObjectPrx base = ic->stringToProxy("SimpleRoom" + name + ":default -p " + to_string(port));
        RoomPrx room = RoomPrx::checkedCast(base);
        roomList.push_back(room);
        cout << "RoomFactory::Room created" << endl;
        return room;
    }

    RoomFactoryI::RoomFactoryI() {
        ic = Ice::initialize();
    }

    RoomFactoryI::~RoomFactoryI() {
        if (ic) {
            try {
                ic->destroy();
            } catch (const Ice::Exception& e) {
                cerr << e << endl;
            }
        }
    }
}