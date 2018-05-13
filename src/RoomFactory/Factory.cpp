#include "Factory.h"

namespace RoomFactory {
    void Factory::registerRoomFactory() {
        RoomFactoryPtr object = new RoomFactoryI();
        int port = ports.getRandomPort();
        adapter = ic->createObjectAdapterWithEndpoints("RoomFactory", "default -p " + to_string(port));
        roomFactory = RoomFactoryPrx::uncheckedCast(adapter->addWithUUID(object));
        adapter->add(object, ic->stringToIdentity("RoomFactory"));
        adapter->activate();
        server->RegisterRoomFactory(roomFactory);
        ic->waitForShutdown();
    }

    Factory::Factory() {
        try {
            serverImplementation();
            registerRoomFactory();
        } catch (const RoomAlreadyExists &ex) {
            cerr << ex << endl;
        } catch (const RoomDoesntExist& ex) {
            cerr << ex << endl;
        } catch (const UserAlreadyExists& ex) {
            cerr << "User already exists" << endl;
        } catch (const Ice::Exception& ex) {
            cerr << ex << endl;
        } catch (const char* msg) {
            cerr << msg << endl;
        }
    }

    Factory::~Factory() {
        server->UnregisterRoomFactory(roomFactory);
    }

    void Factory::serverImplementation(){
        ic = Ice::initialize();
        int serverPort = ports.getServerPort();
        Ice::ObjectPrx base = ic->stringToProxy("Server:default -p " + to_string(serverPort));
        server = ServerPrx::checkedCast(base);
        if (!server) {
            throw "Invalid proxy";
        }
    }
}