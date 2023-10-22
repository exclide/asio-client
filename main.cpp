#include <iostream>
#include <boost/asio.hpp>

using boost::asio::io_context;
using boost::asio::ip::tcp;
using boost::asio::ip::address;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Correct usage: client <ip> <port>\n";
        return EXIT_FAILURE;
    }

    io_context ioc;
    auto strand = boost::asio::make_strand(ioc);
    boost::asio::post(strand, []() {});

    tcp::socket s(ioc);
    tcp::endpoint endpoint(address::from_string(argv[1]), std::stoi(argv[2]));
    s.connect(endpoint);

    std::cout << s.local_endpoint() << " " << s.remote_endpoint() << std::endl;

    boost::asio::streambuf buf;
    std::istream in(&buf);

    std::string data;

    while (!data.starts_with("exit")) {
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
