
CXX=g++
GPP_OPTS=-Wall -std=c++0x -pedantic

SRC_DIR=src/main
TEST_DIR=src/test
SNET_DIR=$(SRC_DIR)/simplenet

all: libsimplenet.a test_tcp_server

test_tcp_server: libsimplenet.a $(TEST_DIR)/test_tcp_server.cpp
	$(CXX) $(GPP_OPTS) -I$(SNET_DIR) $(TEST_DIR)/test_tcp_server.cpp -o test_tcp_server -L. -lsimplenet

libsimplenet.a: client_handle.o tcp_server.o
	ar rcs libsimplenet.a client_handle.o tcp_server.o

tcp_server.o: $(SNET_DIR)/tcp_server.h $(SNET_DIR)/tcp_server.cpp
	$(CXX) $(GPP_OPTS) -c -I$(SNET_DIR) $(SNET_DIR)/tcp_server.cpp

client_handle.o: $(SNET_DIR)/client_handle.h $(SNET_DIR)/client_handle.cpp
	$(CXX) $(GPP_OPTS) -c -I$(SNET_DIR) $(SNET_DIR)/client_handle.cpp

clean:
	rm *.o *~ *.a
