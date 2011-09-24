#include <iostream>
#include <csignal>
	
#include <tcp_server.h>

using namespace std;
using namespace simplenet;

TcpServer server(8181, new string("localhost"));

int main() {

  cout << "Tcp Sever Test" << endl;
  
  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = [] (int signal) {
    server.shutdown();
  };
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  sigaction(SIGINT, &sigIntHandler, NULL);

  server.start([](ClientHandle::ptr client_handle) {
    cout << "got a connection from: " << *client_handle->get_address() << endl;
  });

  return EXIT_SUCCESS;
}
