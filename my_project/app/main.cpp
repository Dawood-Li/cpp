#include "./network/http_server.hpp"

int main() {
    HTTP http;
    http.route("GET", "/", [] (HTTP_Request& req, HTTP_Response& res) {
        res.set(200, {
            { "Server","Flame the C++ Framework by Dawood_Li" },
            { "Content-Type","text/html" },
        },"<html><body><h1>Hello World!</h1></body></html>");
    });
    http.listen(8000);
}
