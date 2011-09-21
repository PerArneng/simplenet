#include <iostream>
#include <csignal>

#include <http_server.h>

using namespace std;
using namespace scalebit::http;

HttpServer server(8080, 8);

int main() {

  cout << "GALEWHALE" << endl;
  
  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = [] (int signal) {
    server.shutdown();
  };
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  sigaction(SIGINT, &sigIntHandler, NULL);

  server.start();

  return EXIT_SUCCESS;
}
