#ifndef FACTORY_H
    #define FACTORY_H

    #include <Ice/Ice.h>
    #include "chat.h"
    #include "RoomFactoryImpl.h"
    #include "Ports.h"

    using namespace std;
    using namespace Chat;
    using namespace IceChat;

    namespace RoomFactory {
        class Factory {
            public:
                Factory();  
                ~Factory();
            private:
                ServerPrx server;
                Ice::CommunicatorPtr ic;
                Ice::ObjectAdapterPtr adapter;
                RoomFactoryPrx roomFactory;
                Ports ports;
                void registerRoomFactory();
        };
    }

#endif