
#include <http_server.h>
#include <iostream>
#include <socket_listener.h>

using namespace std;

namespace scalebit { namespace http {

HttpServer::HttpServer(int port, int num_threads) {
  cout << "starting server on port: " << port << endl;
  this->port = port;
  this->num_threads = num_threads;
  this->server_socket.reset(new SocketWrapper(new int, nullptr));
}

HttpServer::~HttpServer() {
  cout << "destroying http server" << endl;
}

void HttpServer::start() {

  cout << "starting" << endl;

  listen_port(this->server_socket, this->port, [] (SocketWrapper::ptr socket) {
    cout << "accepted! > " << *socket->get_socket() << 
         " from: " << *socket->get_address() << endl;
  });

}

void HttpServer::shutdown() {
  close(*this->server_socket->get_socket());
}

} } // namespace scalebit::http
