#include <boost/bind.hpp>
#include <iostream>
#include "../include/Server.hpp"
#include "../include/Session.hpp"

void Server::Run() {
    m_io_service.run();
}

Server::Server(const std::string &host, short port) :
    m_acceptor(m_io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(host), port)) {
    StartAccept();
}

void Server::StartAccept() {
    std::shared_ptr<Session> connection = Session::Create(m_acceptor.get_io_service());
    m_acceptor.async_accept(
            connection->GetSocket(),
            boost::bind(&Server::HandleAccept, this, connection, boost::asio::placeholders::error));
}

void Server::HandleAccept(std::shared_ptr<Session> connection, const boost::system::error_code &error) {
    connection->Start();
    StartAccept();
}