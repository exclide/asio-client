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

    boost::asio::streambuf buf;
    std::istream in(&buf);

    std::string data;

    while (true) {
        std::getline(std::cin, data);
        data += '\n';

        boost::asio::write(s, boost::asio::buffer(data));

        boost::asio::read_until(s,buf,"\n");
        std::getline(in, data);

        std::cout << data << "\n";

        buf.consume(buf.size());
    }

    return EXIT_SUCCESS;
}
