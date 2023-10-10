#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <cstring>
#include <memory>

class Sockfd {

public:
    
    // 作为client端用于描述与server的连接 由用户创建
    Sockfd ()
        : _sockfd(socket(AF_INET, SOCK_STREAM, 0)) {}

    // 作为server端用于描述与client的连接时的构造函数 由accept函数返回
    Sockfd (int sockfd, const char* addr, uint16_t port) 
        : _sockfd(sockfd), _addr(addr), _port(port) {}
    
    ~Sockfd () {
        close();
    }

    int sockfd() const {
        return _sockfd;
    }

    std::string addr() const {
        return _addr;
    }

    uint16_t port() const {
        return _port;
    }
    
    // 作为服务端时用于监听端口
    void listen (const char* addr, uint16_t port) {
        auto&& addr_pack = _bind(addr, port);
        if (::bind(_sockfd, (sockaddr*)&addr_pack, sizeof(addr_pack)) == -1) {
            perror("bind");
            exit(EXIT_FAILURE);
        };
        if (::listen(_sockfd, SOMAXCONN) == -1) {
            perror("listen");
            exit(EXIT_FAILURE);
        }
    }

    // 作为服务端时用于接受一个连接
    // 需要手动释放
    Sockfd* accept() {
    // std::shared_ptr<Sockfd> accept() {
        sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);  
        int client = ::accept(_sockfd, (sockaddr*)&client_addr, &client_addr_len);
        if (client < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
            return nullptr;
        }  
  
        return new Sockfd(client, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        // return std::make_shared<Sockfd>(client, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    }

    // 作为客户端时用于发起连接
    bool connect (const char* addr, uint16_t port) {
        auto&& addr_pack = _bind(addr, port);
        if (::connect(_sockfd, (struct sockaddr*)&addr_pack, sizeof(addr_pack)) < 0) {  
            std::cerr << "Failed to connect." << std::endl;  
            return false;  
        }  
        return true;
    }

    // 接收消息 返回值是消息长度 若0则是连接被对方关闭 若-1则是连接发生错误
    int recv (std::string& str) const {
        str.resize(65535);
        auto recvlen = ::recv(_sockfd, (char*)str.c_str(), str.size(), 0);
        if (recvlen >= 0) {
            str.resize(recvlen);
        }
        return recvlen;
    }

    // 发送消息
    void send (const std::string& str) const {
        ::send(_sockfd, str.c_str(), str.size(), 0);
    }

    // 关闭连接
    void close () {
        ::close(_sockfd);
    }  
  
private:

    // 生成一个sockaddr_in类型的地址包
    sockaddr_in _bind(const char* addr, uint16_t port) {
        _addr.assign(addr), _port = port;
        struct sockaddr_in addr_pack;  
        addr_pack.sin_family = AF_INET;  
        addr_pack.sin_port = htons(_port);  
        if (inet_pton(AF_INET, _addr.c_str(), &addr_pack.sin_addr) <= 0) {  
            perror("Invalid address");
            exit(EXIT_FAILURE);
        }
        return addr_pack;
    }

    int _sockfd;
    std::string _addr;
    uint16_t _port;
};
