#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <string>
std::string profile() {
    return R"({
  "name": "Broken_Mirror",
  "nickname": ["broken", "菠萝啃"],
  "age": 20,
  "learning": ["C++", "Go", "Gin", "Linux Network Programming"],
  "status": "正在努力成为更强的后端开发者喵"
})";
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(2150);

    bind(server_fd, reinterpret_cast<sockaddr*>(&address), sizeof(address));
    listen(server_fd, 8);

    std::cout << "Broken_Mirror server is running at http://127.0.0.1:2150\n";

    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);

        std::string body = profile();
        std::string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json; charset=utf-8\r\n"
            "Content-Length: " + std::to_string(body.size()) + "\r\n"
            "\r\n" +
            body;

        send(client_fd, response.c_str(), response.size(), 0);
        close(client_fd);
    }

    close(server_fd);
    return 0;
}
