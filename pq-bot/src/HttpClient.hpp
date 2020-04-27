#pragma once
#include <iostream>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/log/trivial.hpp>
#include <string>

namespace beast = boost::beast;   // from <boost/beast.hpp>
namespace http = beast::http;     // from <boost/beast/http.hpp>
namespace net = boost::asio;      // from <boost/asio.hpp>
namespace ssl = net::ssl;         // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>
using response = http::response<http::string_body>;
using request = http::request<http::string_body>;

namespace tlg_bot
{
class HttpClient
{
public:
    void send_request_http(const std::string &host, const http::verb &method, const std::string &target);
    void read_response(beast::tcp_stream &stream);

    void send_request_https(const std::string &host, const http::verb &method, const std::string &target);
    void read_response(beast::ssl_stream<beast::tcp_stream> &stream);

private:
    request create_request(const std::string &host, const http::verb &method, const std::string &target);

    net::io_context m_io_context;
};
typedef std::unique_ptr<HttpClient> PHttp;
} // namespace tlg_bot