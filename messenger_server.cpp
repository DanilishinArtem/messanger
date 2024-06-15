// messenger_server.cpp
#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <chrono>
#include <ctime>
#include <vector>

class MessengerServer {
public:
    MessengerServer(const std::string& connection_string)
        : conn(connection_string) {}

    void handleCommand(const std::vector<std::string>& args) {
        if (args.size() < 2) {
            std::cerr << "Usage: ./messenger_server <command> <args...>" << std::endl;
            return;
        }

        std::string command = args[1];
        if (command == "send" && args.size() == 5) {
            std::string sender = args[2];
            std::string receiver = args[3];
            std::string message = args[4];
            addMessage(sender, receiver, message);
        } else if (command == "receive" && args.size() == 3) {
            std::string user = args[2];
            getMessages(user);
        } else {
            std::cerr << "Unknown command or invalid arguments." << std::endl;
        }
    }

private:
    void addMessage(const std::string& sender, const std::string& receiver, const std::string& message) {
        pqxx::work W(conn);
        std::string query = "INSERT INTO messages (sender, receiver, message) VALUES (" +
                            W.quote(sender) + ", " + W.quote(receiver) + ", " + W.quote(message) + ");";
        W.exec(query);
        W.commit();
    }

    void getMessages(const std::string& user) {
        pqxx::nontransaction N(conn);
        std::string query = "SELECT sender, receiver, message, timestamp FROM messages WHERE receiver = " + N.quote(user) + ";";
        pqxx::result R(N.exec(query));

        for (auto row : R) {
            std::cout << row["timestamp"].as<std::string>() << " - "
                      << row["sender"].as<std::string>() << ": "
                      << row["message"].as<std::string>() << std::endl;
        }
    }

private:
    pqxx::connection conn;
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./messenger_server <command> <args...>" << std::endl;
        return 1;
    }

    std::string connection_string = "dbname=messenger_db user=postgres password=root host=localhost";
    MessengerServer server(connection_string);

    std::vector<std::string> args(argv, argv + argc);
    server.handleCommand(args);

    return 0;
}
