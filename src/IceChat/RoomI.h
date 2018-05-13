#ifndef ROOM_I_H
    #define ROOM_I_H

    #include "chat.h"
    #include <Ice/Ice.h>
    #include "Ports.h"
    #include "RoomFactoryI.h"

    using namespace std;
    using namespace Chat;

    namespace IceChat {
        class RoomI : public virtual Room {
            public:
                RoomI(const string &n) : roomName(n) {}
                virtual string getName(const ::Ice::Current& = ::Ice::Current()) override;
                virtual UserList getUsers(const ::Ice::Current& = ::Ice::Current()) override;
                virtual void AddUser(const UserPrx&, const ::Ice::Current& = ::Ice::Current()) override;
                virtual void SendMessage(const UserPrx&, const string&, const ::Ice::Current& = ::Ice::Current()) override;
                virtual void Destroy(const ::Ice::Current& = ::Ice::Current()) override;
                virtual void LeaveRoom(const UserPrx&, const ::Ice::Current& = ::Ice::Current()) override;
            private:
                string roomName;
                UserList users;
                bool checkIfUserExists(const UserPrx&);
        };
    }

#endif
