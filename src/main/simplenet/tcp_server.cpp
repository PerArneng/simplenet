#include <fcntl.h>
#include <netinet/in.h>
#include <resolv.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <cstdio>
#include <iostream>

#include <tcp_server.h>

namespace simplenet {

TcpServer::TcpServer(int port, std::string* address) {
  this->port = port;
  this->address = address;
}

std::string* TcpServer::get_address() {
  return this->address;
}

TcpServer::~TcpServer() {
  this->shutdown();
  delete this->address;
}

void TcpServer::shutdown() {
  std::cout << "shutting down socket" << std::endl;
  close(this->socket_fd);
}

void TcpServer::start(TcpServer::acceptor acceptor) {

  struct sockaddr_in my_addr;

  int * p_int ;

  socklen_t addr_size = 0;
  int* csock;
  sockaddr_in sadr;

  this->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if(this->socket_fd == -1){
    printf("Error initializing socket %d\n", errno);
    goto FINISH;
  }
  
  p_int = (int*)malloc(sizeof(int));
  *p_int = 1;
      
  if( (setsockopt(this->socket_fd, SOL_SOCKET, SO_REUSEADDR, (char*)p_int, sizeof(int)) == -1 )||
      (setsockopt(this->socket_fd, SOL_SOCKET, SO_KEEPALIVE, (char*)p_int, sizeof(int)) == -1 ) ){
    printf("Error setting options %d\n", errno);
    free(p_int);
    goto FINISH;
  }
  free(p_int);

  my_addr.sin_family = AF_INET ;
  my_addr.sin_port = htons(this->port);
  
  memset(&(my_addr.sin_zero), 0, 8);
  my_addr.sin_addr.s_addr = INADDR_ANY ;
  
  if( bind( this->socket_fd, (sockaddr*)&my_addr, sizeof(my_addr)) == -1 ){
    fprintf(stderr,"Error binding to socket, make sure nothing else is listening on this port %d\n",errno);
    goto FINISH;
  }
  if(listen( this->socket_fd, 10) == -1 ){
    fprintf(stderr, "Error listening %d\n",errno);
    goto FINISH;
  }

  addr_size = sizeof(sockaddr_in);
  
  while(true){
    printf("waiting for a connection\n");
    csock = (int*)malloc(sizeof(int));
    if((*csock = accept( this->socket_fd, (sockaddr*)&sadr, &addr_size))!= -1){
        auto address = new std::string(inet_ntoa(sadr.sin_addr));
        acceptor(ClientHandle::ptr(new ClientHandle(*csock, address)));
    }
    else{
        fprintf(stderr, "Error accepting %d\n", errno);
        goto FINISH;
    }
  }
    
FINISH:
;
}

}

