#include <boost/asio.hpp>
#include <iostream>
#include <vector>
#include <atomic>

using boost::asio::ip::tcp;
using namespace std;

atomic<int> client_counter(0);

void handle_client(tcp::socket socket) {
    int client_id = ++client_counter;
    try {
        cout << "Client " << client_id << " connected." << endl;
        vector<char> data(1024);
        while (true) {
            boost::system::error_code error;
            size_t length = socket.read_some(boost::asio::buffer(data), error);
            if (error == boost::asio::error::eof) break;
            else if (error) throw boost::system::system_error(error);

            cout << "Client " << client_id << ": ";
            cout.write(data.data(), length);
            cout << endl;
        }
    } catch (std::exception &e) {
        cerr << "Exception in client " << client_id << ": " << e.what() << endl;
    }
}

int main() {
    try {
        boost::asio::io_context io_context;

        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 1234));

        while (true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            std::thread(handle_client, std::move(socket)).detach();
        }
    } catch (std::exception &e) {
        cerr << "Exception: " << e.what() << endl;
    }

    return 0;
}
