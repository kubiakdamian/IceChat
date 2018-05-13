#include "RoomI.h"

namespace IceChat {
    string RoomI::getName(const ::Ice::Current&) {
        return roomName;
    }

    UserList RoomI::getUsers(const ::Ice::Current&) {
        return users;
    }

    void RoomI::AddUser(const UserPrx& user, const ::Ice::Current&) {
        if(!RoomI::checkIfUserExists(user)){
            users.push_back(user);
        }else{
            throw UserAlreadyExists();
        }
        
    }

    void RoomI::LeaveRoom(const UserPrx& user, const ::Ice::Current&) {
        if(RoomI::checkIfUserExists(user)){
            for (auto usersIterator = users.begin(); usersIterator != users.end(); ++usersIterator) {
                if ((*usersIterator) == user) {
                    usersIterator = users.erase(usersIterator);
                    break;
                } 
            }   
        }else{
            throw UserDoesntExist();
        }        
    }

    void RoomI::Destroy(const ::Ice::Current&) {
        users.clear();
    }

    void RoomI::SendMessage(const UserPrx& user, const string& message, const ::Ice::Current&) {
        if(RoomI::checkIfUserExists(user)){
            for (auto& userInRoom : users) {
                userInRoom->SendMessage(roomName, user, message);
            }
        }else{
            throw UserDoesntExist();
        }
    
    }

    bool RoomI::checkIfUserExists(const UserPrx& user){
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