#pragma once

#include "./sockfd.hpp"

#include <signal.h>
#include <sys/epoll.h>

#include <iostream>
#include <functional>
#include <memory>

#define MAX_SIZE 4096

/* Usage:

    auto server = Epoll_Server("0.0.0.0", 8000);
    server.on_new_conn([&] (Sockfd* sockfd) {
        // do something
    });
    server.on_disconn([&] (Sockfd* sockfd) {
        // do something
    });
    server.on_msg([&] (Sockfd* sockfd, const std::string& msg) {
        // do something
    });
    server.exec();
*/

class Epoll_Server {

public:

    Epoll_Server(const char* host, uint16_t port)
        : _sockfd(socket(AF_INET, SOCK_STREAM, 0), host, port)
        , _epoll(epoll_create(MAX_SIZE))
    {
        // 若连接断开时仍发送 默认行为是无任何通知就结束进程
        signal(SIGPIPE, SIG_IGN);

        // 设置 SO_REUSEADDR 选项 取消TIME_WAIT
        int reuse = 1;  
        if (setsockopt(_sockfd.sockfd(), SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
            perror("setsockopt");  
            exit(EXIT_FAILURE);  
        }

        _sockfd.listen(host, port);
        epoll_event ev = { .events = EPOLLIN | EPOLLET, .data = { .ptr = &_sockfd } };
        if(epoll_ctl(_epoll, EPOLL_CTL_ADD, _sockfd.sockfd(), &ev) == -1) {
            perror("add server error");  
            exit(EXIT_FAILURE);  
        }
    }

    void on_new_conn(const std::function<void(Sockfd*)>& func) {
        _on_new_conn = func;
    }
    void on_disconn(const std::function<void(Sockfd*)>& func) {
        _on_disconn = func;
    }
    void on_msg(const std::function<void(Sockfd*, const std::string&)>& func) {
        _on_msg = func;
    }

    // 事件循环
    void exec() {
        
        while(1) {

            usleep(0);

            // 获取待处理的事件数量
            int num = epoll_wait(_epoll, events, MAX_SIZE, -1);
            if(num == -1) {
                perror("epoll wait error");  
                exit(EXIT_FAILURE);  
            }

            for(size_t i = 0; i < num; i++) {

                auto p = (Sockfd*)events[i].data.ptr;

                // 事件来源于server 说明有新连接
                if(p == &_sockfd) {
                    auto client = _sockfd.accept();
                    _on_new_conn(client);
                    epoll_event ev = { .events = EPOLLIN, .data = { .ptr = client } };
                    if(epoll_ctl(_epoll, EPOLL_CTL_ADD, client->sockfd(), &ev) == -1) {
                        std::cout << "epoll_ctl error" << std::endl;
                        continue;
                    }
                }

                // 事件来源于其他连接
                else if (events[i].events & EPOLLIN) {

                    // 读取消息
                    int recvlen = p->recv(msg);

                    // 连接被关闭 或 连接发生错误
                    if (recvlen <= 0) {
                        p->close();     // 关闭连接 epoll将自动剔除
                        _on_disconn(p); // 断开连接事件 callback
                        delete p;       // 断开事件处理完毕后 清理内存
                    }
                    
                    else {
                        _on_msg(p, msg);
                    }
                }

                else {
                    std::cout << "events: " << events[i].events << std::endl;
                }
            }
        }
    }

private:

    int _epoll;
    Sockfd _sockfd;
    epoll_event events[MAX_SIZE];
    std::string msg;
    std::function<void(Sockfd*)> _on_new_conn = [this] (Sockfd* sockfd) {
        // std::cout << sockfd->addr() << ":" << sockfd->port() << " connected" << std::endl;
    };
    std::function<void(Sockfd*)> _on_disconn = [this] (Sockfd* sockfd) {
        // std::cout << sockfd->addr() << ":" << sockfd->port() << " disconnected" << std::endl;        
    };
    std::function<void(Sockfd*, const std::string&)> _on_msg = [this] (Sockfd* sockfd, const std::string& msg) {
        // std::cout << sockfd->addr() << ":" << sockfd->port() << ": " << msg << std::endl;
    };
};
