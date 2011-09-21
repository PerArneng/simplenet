
#include <cstdio>

#include <client_handle.h>

namespace simplenet {

ClientHandle::ClientHandle(int fd, std::string* address) {
  this->fd = fd;
  this->address.reset(address);
}

std::shared_ptr<std::string> ClientHandle::get_address() {
  return this->address;
}

ClientHandle::~ClientHandle() {
  close(this->fd);
}

}
