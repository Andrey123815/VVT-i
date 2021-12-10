//
// Created by Yut Fut on 18.11.2021.
//

#include "http_base.h"

void HTTPBase::init_socket_address(struct sockaddr_in &server) {
    server.sin_family = AF_INET;
    server.sin_port = htons(3000);
    inet_pton(AF_INET, "127.0.0.1", &(server.sin_addr));
}

int HTTPBase::request(const int &socket, const std::string msg) {
    size_t left = msg.size();
    ssize_t sent = 0;

    while (left > 0) {
        sent = ::send(socket, msg.data() + sent, msg.size() - sent, 0);
        if (sent == -1) {
            std::cout << "ошибка соединения\n";
            return -1;
        }
        left -= sent;
    }

    std::cout << std::endl << msg << std::endl;
    return 0;
}

std::string HTTPBase::response(const int &socket) {
    char last_char;
    std::string line;
    line.reserve(1024);
    while (read(socket, &last_char, sizeof(char)) == sizeof(char)) {
        line.push_back(last_char);
    }

    if (-1 == line.size() && errno != EAGAIN) {
        return "ошибка соединения\n";
    }
    if (0 == line.size()) {
        return "ошибка соединения\n";
    }
    if (-1 == line.size()) {
        return "ошибка соединения\n";
    }

    std::cerr << line << " [" << line.size() << " bytes]" << std::endl;
    return line;
}

std::string HTTPBase::send(const std::string &message) {
    int client_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (client_socket <= 0) {
        std::cout << "ошибка соединения\n";
        return "ошибка соединения\n";
    }

    struct sockaddr_in server;
    init_socket_address(server);

    if (connect(client_socket, (struct sockaddr*)&server, sizeof(server)) != 0) {
        close(client_socket);
        return "ошибка соединения\n";
    }

    if (request(client_socket, message)) {
        return "ошибка соединения\n";
    }

    std::string http_response = response(client_socket);
    if (http_response == "ошибка соединения\n") {
        std::cout << "ошибка соединения\n";
        return "ошибка соединения\n";
    }

    close(client_socket);

    return http_response;
}
