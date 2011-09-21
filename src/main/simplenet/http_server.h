
#ifndef _HTTP_SERVER_H
#define _HTTP_SERVER_H

#include <socket_wrapper.h>

namespace scalebit { namespace http {

    class HttpServer {

      public:

        HttpServer(int port, int num_threads);

        ~HttpServer();

        void start();

        void shutdown();

      private:
        int port;
        int num_threads;
        SocketWrapper::ptr server_socket;
    };

} }

#endif
