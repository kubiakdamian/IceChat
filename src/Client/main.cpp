#include "Client.h"
#include "ServerImpl.h"
#include "Menu.h"

using namespace std;
using namespace ClientApp;

int main(int argc, char* argv[]) {
    Menu menu;
    string username;
    
    cout << "Enter your username: " << endl;
    cin >> username;

    Client client(username);

    while (true) {
        menu.printMenu();
        int choice = menu.getChoice();
        switch (choice) {
            case 1:
                client.createRoom();
                break;
            case 2:
                client.printRooms();
                break;
            case 3:
                client.joinRoom();
                break;
            case 4:
                client.leaveRoom();
                break;
            case 5:
                client.sendMessage();
                break;
            case 6:
                client.printRoomsMembers();
                break;
            case 7:
                client.sendPrivateMessage();
                break;
            case 8:
                client.changeNickname();
                break;
            case 0:
                return 0;
        }
    }

    return 0;
}