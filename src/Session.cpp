#include <boost/asio.hpp>
#include <iostream>
#include <boost/date_time/local_time/local_time.hpp>
#include "cctz/civil_time.h"
#include "cctz/time_zone.h"
#include "../include/Session.hpp"

std::shared_ptr<Session> Session::Create(boost::asio::io_service &io_service) {
    return std::shared_ptr<Session>(new Session(io_service));
}

boost::asio::ip::tcp::socket& Session::GetSocket() { return m_socket; }

void Session::Read() {
    auto session_ptr = shared_from_this();
    m_socket.async_read_some(
            boost::asio::buffer(m_data, m_buffer_size),
            [this, session_ptr](boost::system::error_code ec, int size){
                std::string zone(m_data);
                zone.pop_back();
                zone.pop_back();
                Write(GetDateByTZAbbr(zone));
            });
}

void Session::Write(const std::string message) {
    auto session_ptr = shared_from_this();
    m_socket.async_write_some(
            boost::asio::buffer(message, m_buffer_size),
            [this, session_ptr](boost::system::error_code ec, int size) {});
}

std::string Session::GetDateByTZAbbr(const std::string abbr) {
    boost::local_time::tz_database tz_db;
    std::string path = "./date_time_zonespec.csv";
    tz_db.load_from_file(path);
    auto region_list = tz_db.region_list();

    for(auto region = region_list.begin(); region != region_list.end(); region++) {
        std::string timezone_std_abbr = tz_db.time_zone_from_region(*region)->std_zone_abbrev();
        std::string timezone_dst_abbr = tz_db.time_zone_from_region(*region)->dst_zone_abbrev();
        if (timezone_std_abbr == abbr || timezone_dst_abbr == abbr) {
            cctz::time_zone zone;
            load_time_zone(*region, &zone);
            auto current_time = std::chrono::system_clock::now();

            return cctz::format("%a %b %d %H:%M:%S %Z %Y\n", current_time, zone);
        }
    }

    return "";
}

void Session::Start() {
    Read();
}

Session::Session(boost::asio::io_service &io_service) : m_socket(io_service) {}

Session::~Session() { }
