#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main() {
    try {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 7666));
        int client_count = 0;

        std::cout << "Server running on port 7666. Waiting for connections..." << std::endl;

        while (true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            client_count++;
            std::cout << "Client " << client_count << " connected." << std::endl;

            std::string message = "Welcome, client " + std::to_string(client_count) + "!\n";
            boost::asio::write(socket, boost::asio::buffer(message));
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
