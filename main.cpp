#include "ChatClient.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Correct usage: client <ip> <port>\n";
        return EXIT_FAILURE;
    }

    io_context ioc;
    tcp::endpoint endpoint(address::from_string(argv[1]), std::stoi(argv[2]));

    ChatClient client(ioc, endpoint);

    std::thread t([&ioc]() { ioc.run(); });

    std::string data;

    while (!data.starts_with("exit")) {
        std::getline(std::cin, data);
        data += '\n';

        client.Write(data);
    }

    t.join();

    return EXIT_SUCCESS;
}
