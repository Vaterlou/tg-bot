#include "HttpClient.hpp"

using namespace tlg_bot;

void HttpClient::send_request_http(const std::string &host, const http::verb &method, const std::string &target)
{
    tcp::resolver resolver(m_io_context);
    beast::tcp_stream stream(m_io_context);

    auto const results = resolver.resolve(host, "80");
    stream.connect(results);

    request req{method,target,11};

    http::write(stream, req);
    BOOST_LOG_TRIVIAL(info) << "\nREQUEST:\n" << req;

    read_response(stream);

    beast::error_code ec;
    stream.socket().shutdown(tcp::socket::shutdown_both, ec);

    if (ec && ec != beast::errc::not_connected)
        throw beast::system_error{ec};
}

void HttpClient::read_response(beast::tcp_stream &stream)
{
    beast::flat_buffer buffer;
    response res;
    http::read(stream, buffer, res);
    BOOST_LOG_TRIVIAL(info) << "\nRESPONSE:\n" << res << std::endl;
}

void HttpClient::send_request_https(const std::string &host, const http::verb &method, const std::string &target)
{
    ssl::context ctx(ssl::context::tlsv12_client);
    ctx.set_default_verify_paths();
    ctx.set_verify_mode(ssl::verify_peer);
    tcp::resolver resolver(m_io_context);
    beast::ssl_stream<beast::tcp_stream> stream(m_io_context, ctx);
    auto const results = resolver.resolve(host, "443");
    beast::get_lowest_layer(stream).connect(results);
    stream.handshake(ssl::stream_base::client);
    request req = create_request(host,method,target);
    http::write(stream, req);
    BOOST_LOG_TRIVIAL(info) << "\nREQUEST:\n" << req;
    read_response(stream);
    beast::error_code ec;
    stream.shutdown(ec);
}

void HttpClient::read_response(beast::ssl_stream<beast::tcp_stream> &stream)
{
    beast::flat_buffer buffer;
    response res;
    http::read(stream, buffer, res);
    BOOST_LOG_TRIVIAL(info) << "\nRESPONSE:\n" << res << std::endl;
}

request HttpClient::create_request(const std::string &host, const http::verb &method, const std::string &target)
{
    request req{method,target,11};
    req.set(http::field::host,host);
    req.set(http::field::content_type, "application/json");
    req.set(http::field::user_agent, "Beast");
    req.prepare_payload();
    return req;
}
