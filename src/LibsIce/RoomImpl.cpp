#include "RoomImpl.h"

namespace LibsIce {
    string RoomImpl::getName(const ::Ice::Current&) {
        return roomName;
    }

    UserList RoomImpl::getUsers(const ::Ice::Current&) {
        return users;
    }

    void RoomImpl::AddUser(const UserPrx& user, const ::Ice::Current&) {
        if(!RoomImpl::checkIfUserExists(user)){
            users.push_back(user);
        }else{
            throw UserAlreadyExists();
        }
        
    }

    void RoomImpl::LeaveRoom(const UserPrx& user, const ::Ice::Current&) {
        if(RoomImpl::checkIfUserExists(user)){
            for (auto usersIterator = users.begin(); usersIterator != users.end(); ++usersIterator) {
                if ((*usersIterator) == user) {
                    usersIterator = users.erase(usersIterator);
                    cout << "Removed user " << user->getName() << " from room" << endl;
                    break;
                } 
            }   
        }else{
            throw NoSuchUserExist();
        }        
    }

    void RoomImpl::Destroy(const ::Ice::Current&) {
        users.clear();
    }

    void RoomImpl::SendMessage(const UserPrx& user, const string& message, const ::Ice::Current&) {
        if(RoomImpl::checkIfUserExists(user)){
            for (auto& userInRoom : users) {
                userInRoom->SendMessage(roomName, user, message);
            }
        }else{
            throw NoSuchUserExist();
        }
    
    }

    bool RoomImpl::checkIfUserExists(const UserPrx& user){
        int userExist = 0;
        for(auto usersIterator = users.begin(); usersIterator != users.end(); ++usersIterator){
            if((*usersIterator)->getName() == user->getName()){
                userExist++;
            }
        }

        if(userExist > 0){
            return true;
        }else{
            return false;
        }
    }
}