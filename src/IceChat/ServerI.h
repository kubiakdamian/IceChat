#ifndef SERVER_I_H
    #define SERVER_I_H

    #include <random>
    #include <iterator>
    #include <Ice/Ice.h>
    #include "chat.h"
    #include "UserI.h"

    using namespace Chat;
    using namespace std;

    namespace IceChat {
        class ServerI : public virtual Server {
            public:
                virtual RoomPrx CreateRoom(const string&, const ::Ice::Current& = ::Ice::Current()) override;
                virtual RoomList getRooms(const ::Ice::Current& = ::Ice::Current()) override;
                virtual RoomPrx FindRoom(const string&, const ::Ice::Current& = ::Ice::Current()) override;
                virtual void RegisterRoomFactory(const RoomFactoryPrx&, const ::Ice::Current& = ::Ice::Current()) override;
                virtual void UnregisterRoomFactory(const RoomFactoryPrx&, const ::Ice::Current& = ::Ice::Current()) override;
            private:
                RoomList roomList;
                RoomFactoryList roomFactoryList;
        };
    }
#endif