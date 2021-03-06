module Chat {

interface Room;
interface RoomFactory;

exception UserAlreadyExists {};
exception UserDoesntExist {};
exception RoomAlreadyExists {};
exception RoomDoesntExist {};

interface User {
  void SendMessage(string where, User* who, string message);
  void SendPrivateMessage(User* who, string message);
  string getName();
};

sequence<Room*> RoomList;
sequence<RoomFactory*> RoomFactoryList;

interface Server {
  Room* CreateRoom(string name) throws RoomAlreadyExists;
  RoomList getRooms();
  Room* FindRoom(string name) throws RoomDoesntExist;
  void RegisterRoomFactory(RoomFactory* factory);
  void UnregisterRoomFactory(RoomFactory* factory);
};

sequence<User*> UserList;

interface Room {
  string getName();
  UserList getUsers();
  void AddUser(User* who) throws UserAlreadyExists;
  void SendMessage(User* who, string message);
  void Destroy();
  void LeaveRoom(User* who);
};

interface RoomFactory
{
   Room* createRoom(string name);
   RoomList getRooms();
};

};
