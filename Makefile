CC=g++
#CFLAGS=-O3 -g
CFLAGS=-g

COMMON_SRC=./common.o ./socket_wrapper.o
BLOCKING_SERVER_V1_SRC=$(COMMON_SRC) ./blocking_server_v1.o
BLOCKING_SERVER_V1_TARGET=blocking_server_v1
TARGET=$(BLOCKING_SERVER_V1_TARGET)
SRC=$(BLOCKING_SERVER_V1_SRC)

.PHONY: all
all: $(TARGET)

$(BLOCKING_SERVER_V1_TARGET): $(BLOCKING_SERVER_V1_SRC)
	$(CC) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $^

%.o: %.o
	$(CC) $(CFLAGS) -c -o $@ $^
	
.PHONY: clean
clean:
	-rm -f $(TARGET) $(SRC)
