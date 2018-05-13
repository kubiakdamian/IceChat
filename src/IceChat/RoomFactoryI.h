#ifndef ROOM_FACTORY_I_H
    #define ROOM_FACTORY_I_H

    #include <Ice/Ice.h>
    #include "chat.h"
    #include "RoomI.h"
    #include "Ports.h"

    using namespace std;
    using namespace Chat;

    namespace IceChat {
        class RoomFactoryI : public virtual RoomFactory {
            public:
                RoomFactoryI();
                virtual RoomPrx createRoom(const string&, const ::Ice::Current& = ::Ice::Current()) override;
                virtual RoomList getRooms(const ::Ice::Current& = ::Ice::Current()) override;
                ~RoomFactoryI();
            private:
                RoomList roomList;
                Ice::CommunicatorPtr ic;
                Ice::ObjectAdapterPtr adapter;
                Ports ports;
        };
    }

#endif