#ifndef PORTS_H
    #define PORTS_H

    #include <random>
    using namespace std;

    namespace LibsIce {
        class Ports {
            public:
                int getServerPort() const {
                    return serverPort;
                }

                int getRandomPort() const {
                    random_device rd;
                    mt19937 mt(rd());
                    uniform_int_distribution<> dist(min, max);
                    return dist(mt);
                }
            private:
                static const int serverPort = 2000;
                static const int min = 2001;
                static const int max = 49000;
        };
    }
#endif