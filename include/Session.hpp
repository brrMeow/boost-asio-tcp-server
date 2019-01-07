#pragma once

class Session : public std::enable_shared_from_this<Session> {
public:
    static std::shared_ptr<Session> Create(boost::asio::io_service &io_service);
    boost::asio::ip::tcp::socket &GetSocket();
    void Start();
    void Read();
    void Write(const std::string message);
    std::string GetDateByTZAbbr(const std::string abbr);
    Session(boost::asio::io_service& io_service);
    ~Session();

private:
    boost::asio::ip::tcp::socket m_socket;
    int m_buffer_size = 1024;
    char m_data[1024];
};