#include "UserI.h"

namespace IceChat {
    string UserI::getName(const Ice::Current&) { 
        return name;
    }

    void UserI::SendMessage(const string& room, const UserPrx& who, const string& message, const ::Ice::Current&) {
        cout << room << endl;
        cout << who->getName() << ":" << message << endl;
    }

    void UserI::SendPrivateMessage(const UserPrx& who, const string& message, const ::Ice::Current&) {
        cout << who->getName() << ": " << message << endl;
    }
}