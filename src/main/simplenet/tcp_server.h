
#pragma once
#ifndef _TCP_SERVER_H
#define _TCP_SERVER_H

#include <functional>
#include <memory>

#include <client_handle.h>

namespace simplenet {

class TcpServer {

  private:

    int socket_fd;
    int port;
    std::string* address;

  public:

    typedef std::shared_ptr<TcpServer> ptr;
    typedef std::function<void (ClientHandle::ptr)> acceptor;

    TcpServer(int port, std::string* address);
  
    void start(TcpServer::acceptor acceptor);

    void shutdown();
  
    std::string* get_address();

    ~TcpServer();

};

}

#endif
