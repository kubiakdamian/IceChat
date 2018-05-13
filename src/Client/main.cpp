#include "Client.h"
#include "ServerI.h"

using namespace std;
using namespace ClientApp;

void printMenu() {
    cout << endl;
    cout << "1. Create room" << endl;
    cout << "2. Print rooms" << endl;
    cout << "3. Print room's members" << endl;
    cout << "4. Join room" << endl;
    cout << "5. Leave room" << endl;
    cout << "6. Send message" << endl;   
    cout << "7. Send private message" << endl;
    cout << "8. Change username" << endl;
    cout << "0. Exit" << endl;
    cout << endl;
}

int getNumber() {
    int number;
    cin >> number; 
    while (number < 0 || number > 8) {
        cout << "Enter number from 0 to 8." << endl;
        cin >> number;
    }

    return number;
}

int main(int argc, char* argv[]) {
    string username;
    
    cout << "Enter your username: " << endl;
    cin >> username;

    Client client(username);

    while (true) {
        printMenu();
        int number = getNumber();
        switch (number) {
            case 1:
                client.createRoom();
                break;
            case 2:
                client.printRooms();
                break;
            case 3:
                client.printRoomsMembers();
                break;
            case 4:
                client.joinRoom();
                break;
            case 5:
                client.leaveRoom();
                break;
            case 6:
                client.sendMessage();
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