

#include <iostream>

#include <socket_wrapper.h>

namespace scalebit { namespace http {

SocketWrapper::SocketWrapper(int* socket, std::string* address) {
  this->socket = socket;
  this->address = address;
}

int* SocketWrapper::get_socket() {
  return this->socket;
}

std::string* SocketWrapper::get_address() {
  return this->address;
}

SocketWrapper::~SocketWrapper() {
  std::cout << "destroying socket" << std::endl;
  close(*this->socket);
  delete this->socket;
  delete this->address;
}

} }
