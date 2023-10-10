#pragma once
#include "./http_message.hpp"
#include "./epoll_server.hpp"

#include <functional>

/*  Usage:

    HTTP http;
    http.route["GET"]["/"] = [] (HTTP_Request& req, HTTP_Response& res) {
        res.set(200, {
            { "Server","Flame the C++ Framework by Dawood_Li" },
            { "Content-Type","text/html" },
        },"<html><body><h1>Hello World!</h1></body></html>");
    };
    http.listen(8000);
*/

class HTTP {

private:

public:

    HTTP() {

        _default = [] (HTTP_Request& req, HTTP_Response& res) {
            res.set(403, {
                { "Server","Flame the C++ Framework by Dawood_Li" }
            },"<html><body><h1>403 Forbidden</h1></body></html>");
        };

        _route["GET"]["/"] = [] (HTTP_Request& req, HTTP_Response& res) {
            res.set(200, {
                { "Server","Flame the C++ Framework by Dawood_Li" }
            },"<html><body><h1>Hello World!</h1></body></html>");
        };
    }

    void route(
        const std::string& method,
        const std::string& url,
        std::function<void(HTTP_Request& req, HTTP_Response& res)>&& func
    ) {
        _route[method][url] = std::move(func);
    }

    // 执行
    void listen(int port) {
        
        auto server = Epoll_Server("0.0.0.0", port);
        server.on_msg([&] (Sockfd* sockfd, const std::string& msg) {
            auto res = process(HTTP_Request().parse(msg)).to_string();
            sockfd->send(res);
            std::cout << "req: " << msg << std::endl;
            std::cout << "res: " << res << std::endl;
        });

        std::cout << "listenning port " << port << std::endl;

        server.exec();
    }

    // 终止
    void stop();

private:

    int port = 80;

    // 匹配对应的请求函数 并使用该函数处理请求
    // 若匹配失败 则使用_default函数来进行处理
    HTTP_Response process(const HTTP_Request& req) {
        HTTP_Response res;
        auto& method = req.method;
        auto& url = req.url;
        if (_route.count(req.method) && _route[req.method].count(req.url)) {
            _route[method][url](const_cast<HTTP_Request&>(req), res);
        } else {
            _default(const_cast<HTTP_Request&>(req), res);
        }
        return res;
    }

        // 默认处理函数
    std::function<void(HTTP_Request& req, HTTP_Response& res)> _default;

    // 请求路由 处理函数的容器 第一个键是method 第二个键是url
    std::unordered_map<std::string,
        std::unordered_map<std::string,
            decltype(_default)>> _route;
};
