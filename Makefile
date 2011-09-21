
CXX=g++
GPP_OPTS=-Wall -std=c++0x -pedantic

SRC_DIR=src/main
SNET_DIR=$(SRC_DIR)/simplenet

all: test_g

test_g: client_handle.o tcp_server.o

tcp_server.o: $(SNET_DIR)/tcp_server.h $(SNET_DIR)/tcp_server.cpp
	$(CXX) $(GPP_OPTS) -c -I$(SNET_DIR) $(SNET_DIR)/tcp_server.cpp

client_handle.o: $(SNET_DIR)/client_handle.h $(SNET_DIR)/client_handle.cpp
	$(CXX) $(GPP_OPTS) -c -I$(SNET_DIR) $(SNET_DIR)/client_handle.cpp

clean:
	rm *.o *~
