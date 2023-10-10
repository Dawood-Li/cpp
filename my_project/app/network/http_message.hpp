#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

/*
    Usage:
    
    std::string req_raw_data = "GET /index.html HTTP/1.1\r\nHost: www.example.com\r\nUser-Agent: curl/7.64.1\r\n\r\n";
    std::string res_raw_data = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\nContent-Length: 48\r\n\r\n<html><body><h1>Hello, world!</h1></body></html>";  
    std::cout << HTTP_Request().parse(req_raw_data).to_string() << std::endl;
    std::cout << HTTP_Response().parse(res_raw_data).to_string() << std::endl;

*/

class HTTP_Message {
public:
    std::string version="HTTP/1.0", content="";
    std::unordered_map<std::string, std::string> headers;
    
    virtual std::string to_string() const = 0;

protected:
    void _read_headers(std::stringstream& ss) {
        std::string line;
        while (std::getline(ss, line) && line != "\r") {
            std::istringstream iss(line);
            auto pos = line.find(':');
            auto&& k = line.substr(0, pos);
            auto&& v = line.substr(pos + 2, line.size()-1);
            headers[k] = v;
        }
        content.assign(
            std::istreambuf_iterator<char>(ss),
            std::istreambuf_iterator<char>()
        );
    }
};

class HTTP_Request : public HTTP_Message {
public:
    std::string method, url;
    
    HTTP_Request parse(const std::string& raw_data) {
        std::stringstream ss(raw_data);
        std::string line;
        std::getline(ss, line);
        std::istringstream(line) >> method >> url >> version;
        _read_headers(ss);
        return *this;
    }

    std::string to_string() const override {
        std::string str = method + ' ' + url + ' ' + version + "\r\n";
        for (auto& [k, v] : headers) {
            str += k + ": " + v + "\r\n";
        }
        if (content.size() && ! headers.count("Content-Length")) {
            str += "Content-Length: " + std::to_string(content.size()) + "\r\n";
        }
        return str + content;
    }

    HTTP_Request set(
        const std::string& method,
        const std::string& url,
        const std::unordered_map<std::string, std::string>& headers,
        const std::string& content
    ) {
        this->method = method;
        this->url = url;
        this->headers = headers;
        this->content = content;
        return *this;
    }
};

class HTTP_Response : public HTTP_Message {
public:
    std::string status, reason;

    HTTP_Response parse(const std::string& raw_data) {
        std::stringstream ss(raw_data);
        std::string line;
        std::getline(ss, line);
        std::istringstream(line) >> version >> status >> reason;  
        _read_headers(ss);
        return *this;
    }

    std::string to_string() const override {
        std::string str = version + ' '  + status + ' ' + reason + "\r\n";
        for (auto& [k, v] : headers) {
            str += k + ": " + v + "\r\n";
        }
        if (content.size() && ! headers.count("Content-Length")) {
            str += "Content-Length: " + std::to_string(content.size()) + "\r\n";
        }
        return str + "\r\n" + content;
    }

    HTTP_Response set(
        int status,
        const std::unordered_map<std::string, std::string>& headers,
        const std::string& content
    ) {
        this->status = std::to_string(status);
        this->reason = _tb_reason.count(status) ? _tb_reason.at(status) : "None";
        this->content = content;
        this->headers["Content-Length"] = std::to_string(content.size());
        return *this;
    }

private:

    // 后续考虑从配置文件加载
    inline static const std::unordered_map<int, std::string> _tb_reason = {
        { 200,  "OK" },
        { 302,  "Found" },
        { 307,  "Temporary Redirect" },
        { 403,  "forbidden" },
        { 404,  "Not Found" },
        { 502,  "Bad Gateway" },
    };
};
