module Chat {

interface Room;
interface RoomFactory;

exception UserAlreadyExists {};
exception NoSuchUserExist {};
exception NoSuchRoomExist {};
exception RoomAlreadyExist {};
exception NoResourcesAvailable {};

interface User {
  void SendMessage(string where, User* who, string message);
  void SendPrivateMessage(User* who, string message);
  string getName();
};

sequence<Room*> RoomList;
sequence<RoomFactory*> RoomFactoryList;

interface Server {
  Room* CreateRoom(string name) throws RoomAlreadyExist, NoResourcesAvailable;
  RoomList getRooms();
  Room* FindRoom(string name) throws NoSuchRoomExist;
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
