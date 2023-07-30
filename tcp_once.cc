// File: tcp_once.cc
// Date: 20230730
// Author: dawood
// Email: dawood_li@outlook.com
// Description: 向指定地址发送消息，并获取消息回执
// License: None

#include <iostream>
#include <string>

/// @brief 向指定地址发送消息，并获取消息回执
/// @param host 主机地址
/// @param port 主机端口
/// @param msg 消息
/// @return 消息回执
std::string
tcp_once (
    std::string host,
    uint16_t    port,
    std::string msg
);

#ifndef _WIN32 // linux

    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>

    std::string
    tcp_once (
        std::string host,
        uint16_t    port,
        std::string msg
    ) {
        std::string response = "";

        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1) {
            std::cerr << "Failed to create socket" << std::endl;
            return response;
        }

        struct sockaddr_in server;
        server.sin_addr.s_addr = inet_addr(host.c_str());
        server.sin_family = AF_INET;
        server.sin_port = htons(port);

        if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
            std::cerr << "Failed to connect to server" << std::endl;
            close(sock);
            return response;
        }

        if (send(sock, msg.c_str(), msg.length(), 0) < 0) {
            std::cerr << "Failed to send message" << std::endl;
            close(sock);
            return response;
        }

        char buffer[1024] = {0};
        if (read(sock, buffer, 1024) < 0) {
            std::cerr << "Failed to receive message" << std::endl;
            close(sock);
            return response;
        }

        close(sock);
        return std::string(buffer);
    }

#else // windows

    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")

    std::string
    tcp_once (
        std::string host,
        uint16_t    port,
        std::string msg
    ) {
        std::string response = "";

        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "Failed to initialize Winsock" << std::endl;
            return response;
        }

        SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == INVALID_SOCKET) {
            std::cerr << "Failed to create socket" << std::endl;
            WSACleanup();
            return response;
        }

        struct sockaddr_in server;
        server.sin_addr.s_addr = inet_addr(host.c_str());
        server.sin_family = AF_INET;
        server.sin_port = htons(port);

        if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
            std::cerr << "Failed to connect to server" << std::endl;
            closesocket(sock);
            WSACleanup();
            return response;
        }

        if (send(sock, msg.c_str(), msg.length(), 0) < 0) {
            std::cerr << "Failed to send message" << std::endl;
            closesocket(sock);
            WSACleanup();
            return response;
        }

        char buffer[1024] = {0};
        if (recv(sock, buffer, 1024, 0) < 0) {
            std::cerr << "Failed to receive message" << std::endl;
            closesocket(sock);
            WSACleanup();
            return response;
        }

        response = std::string(buffer);

        closesocket(sock);
        WSACleanup();

        return response;
    }

#endif

int main() {
    auto response = tcp_once("127.0.0.1", 8080, "Hello, server!");
    std::cout << "Server response: " << response << std::endl;
}
