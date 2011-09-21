
#pragma once
#ifndef _CLIENT_HANDLE_H
#define _CLIENT_HANDLE_H

#include <string>
#include <memory>

namespace simplenet {

class ClientHandle {

  private:
    int fd;
    std::shared_ptr<std::string> address;

  public:

    typedef std::shared_ptr<ClientHandle> ptr;

    ClientHandle(int fd, std::string* address);

    std::shared_ptr<std::string> get_address();

    ~ClientHandle();

};

}

#endif
