#include "Client.h"

namespace ClientApp {

    void Client::createUser() {
        registerUser(username);
    }

    Client::Client(const string& name): username(name) {
        try {
            iceCommunicator = Ice::initialize();
            int serverPort = ports.getServerPort();
            Ice::ObjectPrx base = iceCommunicator->stringToProxy("Server:default -p " + to_string(serverPort));
            server = ServerPrx::checkedCast(base);
            if (!server)
                throw "Invalid proxy";
        } catch (const Ice::Exception& ex) {
            cerr << ex << endl;
        } catch (const char* msg) {
            cerr << msg << endl;
        }
        createUser();
    }

    Client::~Client() {
        for (auto &room : userRooms) {
            room->LeaveRoom(user);
        }
        if (iceCommunicator)
            iceCommunicator->destroy();
    }

    void Client::createRoom() const {
        scrollConsole();
        string roomName;
        cout << "Enter room name " << endl;
        cin >> roomName;
        cin.ignore(1000, '\n');
        try {
            server->CreateRoom(roomName);
        } catch (const Chat::RoomAlreadyExist& ex) {
            cerr << "Room already exists." << endl;
        } catch (const Chat::NoResourcesAvailable& ex) {
            cerr << "Creation failed, try again." << endl;
        } catch (const Ice::UnknownException& ex) {
            cerr << "Creation failed." << endl;
        }
        scrollConsole();
    }

    void Client::printRooms() const {
        scrollConsole();
        auto rooms = server->getRooms();
        cout << "Rooms: " << endl;
        for (auto room : rooms) {
            cout << room->getName() << endl;
        }
        cout << endl;
    }

    void Client::joinRoom() {
        string name = getNameOfTheRoom();
        try {
            RoomPrx room = server->FindRoom(name);
            room->AddUser(user);
            userRooms.push_back(room);
        } catch (const NoSuchRoomExist& ex) {
            cerr << "Room doesn't exists." << endl;
        } catch (const UserAlreadyExists& ex) {
            cerr << "There is a user with your nickname in room" << endl;
        } catch (const Ice::UnknownException& ex) {
            cerr << "Joining failed." << endl;
        }
        scrollConsole();
    }

    void Client::printRoomsMembers() const {
        try {
            auto users = getUsersInRoom();
            scrollConsole();
            cout << "Users in room:" << endl;
            for (auto& user : users) {
                cout << user->getName() << endl;
            }
        } catch (const Ice::UnknownException& ex) {
            cerr << "Printing failed." << endl;
        }
    }

    void Client::changeNickname(){
        scrollConsole();
        string newUsername;
        cout << "Enter new nickname:" << endl;
        cin >> newUsername;

        registerUser(newUsername);
    }

    UserList Client::getUsersInRoom() const {
        string roomName = getNameOfTheRoom();
        try {
            RoomPrx room = server->FindRoom(roomName);
            UserList users = room->getUsers();
            return users;
        } catch (const NoSuchRoomExist& ex) {
            cerr << "Room doesn't exists." << endl;
        } catch (Ice::UnknownException& ex) {
            cerr << "Couldn't get users." << endl;
        }
        return UserList();
    }

    string Client::getNameOfTheRoom() const {
        scrollConsole();
        string roomName;
        cout << "Enter room's name:" << endl;
        cin >> roomName;
        cin.ignore(1000, '\n');
        return roomName;
    }

    void Client::leaveRoom() {
        scrollConsole();
        string roomName = getNameOfTheRoom();
        for (auto roomsIterator =  userRooms.begin(); roomsIterator != userRooms.end(); ++roomsIterator) {
            if ((*roomsIterator)->getName() == roomName) {
                try {
                    (*roomsIterator)->LeaveRoom(user); 
                    userRooms.erase(roomsIterator);
                    cout << "Room left." << roomName << endl;
                    return;
                } catch (NoSuchUserExist& ex) {
                    cerr << "You aren't in this room." << endl;
                } catch (Ice::UnknownException& ex) {
                    cerr << ex << endl;
                }
            }
        }
    }

    void Client::scrollConsole() const {
        for (unsigned int i = 0; i < 2; ++i) {
            cout << endl;
        }
    }

    void Client::sendPrivateMessage() const {
        string receiver;
        UserList usersAvailable;
        try {
            usersAvailable = getUsersInRoom();
        } catch (NoSuchRoomExist& ex) {
            cerr << ex << endl;
            return;
        }
        cout << "Enter receiver's name" << endl;
        cin >> receiver;
        cin.ignore(1000, '\n');
        for(auto& targetUser : usersAvailable) {
            if (targetUser->getName() == receiver) {
                string message;
                cout << "Enter message" << endl;
                getline(cin, message);
                targetUser->SendPrivateMessage(user, message);
                return;
            }
        }
        cerr << "Couldn't find a user." << endl;
    }

    void Client::sendMessage() const {
        scrollConsole();
        string targetRoom = getNameOfTheRoom();
        for (auto roomsIterator =  userRooms.begin(); roomsIterator != userRooms.end(); ++roomsIterator) {
            if ((*roomsIterator)->getName() == targetRoom) {
                try {
                    string content;
                    cout << "Enter message" << endl;
                    getline(cin, content);
                    (*roomsIterator)->SendMessage(user, content);
                    return;
                } catch (NoSuchUserExist& ex) {
                    cerr << "You are not a member of this room." << endl;
                    return;
                }
            }
        }
        cerr << "You are not a member of this room " << targetRoom << endl;
    }

    void Client::registerUser(string username){
        UserPtr object = new UserImpl(username);
        int port = ports.getRandomPort();
        adapter = iceCommunicator->createObjectAdapterWithEndpoints("User" + username, "default -p " + to_string(port));
        user = UserPrx::uncheckedCast(adapter->addWithUUID(object));
        adapter->activate();
    }
}