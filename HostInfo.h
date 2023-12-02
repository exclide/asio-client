//
// Created by w on 02.12.23.
//

#ifndef ASIO_CLIENT_HOSTINFO_H
#define ASIO_CLIENT_HOSTINFO_H

#include <string>

struct HostInfo {
    static QString ip;
    static int port;
};

QString HostInfo::ip = "127.0.0.1";
int HostInfo::port = 1234;

#endif //ASIO_CLIENT_HOSTINFO_H
