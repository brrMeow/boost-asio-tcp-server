#pragma once

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include "Session.hpp"

class Server {
public:
    void Run();
    Server(const std::string &host, short port);

private:
    boost::asio::io_service m_io_service;
    boost::asio::ip::tcp::acceptor m_acceptor;

    void StartAccept();
    void HandleAccept(std::shared_ptr<Session> connection, const boost::system::error_code &error);
};