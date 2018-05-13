#ifndef USER_I_H
    #define USER_I_H

    #include <Ice/Ice.h>
    #include "chat.h"
    #include <chrono>
    #include <ctime>

    using namespace Chat;
    using namespace std;

    namespace IceChat {
        class UserI : public virtual User {
            public:
                UserI(const string& n) : name(n){};
                virtual string getName(const Ice::Current&) override;
                virtual void SendMessage(const string&,const UserPrx&, const string&, const ::Ice::Current& = ::Ice::Current()) override;
                virtual void SendPrivateMessage(const UserPrx&, const string&, const ::Ice::Current& = ::Ice::Current()) override;
                string name;
            private:
        };
    }
    
#endif