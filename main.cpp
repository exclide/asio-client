#include <iostream>
#include <boost/asio.hpp>

using boost::asio::io_context;
using boost::asio::ip::tcp;


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Correct usage: client <ip> <port>\n";
        return EXIT_FAILURE;
    }

    io_context ioc;
    tcp::socket s(ioc);
    tcp::resolver  resolver(ioc);
    boost::asio::connect(s, resolver.resolve(argv[1], argv[2]));

    size_t readSize = 128;

    while (true) {
        std::string input;
        std::getline(std::cin, input);
        input.push_back('\n');

        boost::asio::write(s, boost::asio::buffer(input));

        std::string output;
        output.resize(readSize);

        s.read_some(boost::asio::buffer(output));

        std::cout << output;
    }

    return EXIT_SUCCESS;
}
