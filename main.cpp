#include "include/Server.hpp"

int main() {
    Server server("127.0.0.1", 13);
    server.Run();

    return 0;
}