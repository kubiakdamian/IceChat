#include <Ice/Ice.h>
#include "chat.h"
#include "ServerI.h"
#include "Ports.h"

using namespace IceChat;
using namespace std;

int main(int argc, char* argv[]) {
    int status = 0;
    Ports ports;
    Ice::CommunicatorPtr ic;
    try {
        ic = Ice::initialize(argc, argv);
        int serverPort = ports.getServerPort();
        Ice::ObjectAdapterPtr adapter = ic->createObjectAdapterWithEndpoints("ServerAdapter", "default -p " + to_string(serverPort));
        Ice::ObjectPtr object = new ServerI();
        //servant
        adapter->add(object, ic->stringToIdentity("Server"));
        adapter->activate();
        ic->waitForShutdown();
    } catch (const char* msg) {
        cerr << msg << endl;
        status = 1;
    } catch (const RoomAlreadyExists &ex) {
        cerr << ex << endl;
    } catch (const RoomDoesntExist& ex) {
            cerr << ex << endl;
    } catch (const UserAlreadyExists& ex) {
            cerr << "User already exist" << endl;
    } catch (const Ice::Exception& e) {
        cerr << e << endl;
        status = 1;
    } 
    if (ic) {
        try {
            ic->destroy();
        } catch (const Ice::Exception& e) {
            cerr << e << endl;
            status = 1;
        }
    }
    return status;
}
