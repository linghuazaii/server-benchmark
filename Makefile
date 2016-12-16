CC=g++
#CFLAGS=-O3 -g
CFLAGS=-g

COMMON_SRC=./common.o ./socket_wrapper.o

BLOCKING_SERVER_V1_SRC=$(COMMON_SRC) ./blocking_server_v1.o
BLOCKING_SERVER_V1_TARGET=blocking_server_v1

BLOCKING_SERVER_V2_SRC=$(COMMON_SRC) ./blocking_server_v2.o
BLOCKING_SERVER_V2_TARGET=blocking_server_v2

BLOCKING_SERVER_V3_SRC=$(COMMON_SRC) ./blocking_server_v3.o
BLOCKING_SERVER_V3_TARGET=blocking_server_v3

BLOCKING_SERVER_V4_SRC=$(COMMON_SRC) ./blocking_server_v4.o
BLOCKING_SERVER_V4_TARGET=blocking_server_v4

BLOCKING_SERVER_V5_SRC=$(COMMON_SRC) ./blocking_server_v5.o
BLOCKING_SERVER_V5_TARGET=blocking_server_v5

BLOCKING_SERVER_V6_SRC=$(COMMON_SRC) ./blocking_server_v6.o
BLOCKING_SERVER_V6_TARGET=blocking_server_v6

BLOCKING_SERVER_V7_SRC=$(COMMON_SRC) ./blocking_server_v7.o
BLOCKING_SERVER_V7_TARGET=blocking_server_v7

TARGET=$(BLOCKING_SERVER_V1_TARGET) $(BLOCKING_SERVER_V2_TARGET) $(BLOCKING_SERVER_V3_TARGET) $(BLOCKING_SERVER_V4_TARGET) $(BLOCKING_SERVER_V5_TARGET) $(BLOCKING_SERVER_V6_TARGET) $(BLOCKING_SERVER_V7_TARGET)
SRC=$(BLOCKING_SERVER_V1_SRC) $(BLOCKING_SERVER_V2_SRC) $(BLOCKING_SERVER_V3_SRC) $(BLOCKING_SERVER_V4_SRC) $(BLOCKING_SERVER_V5_SRC) $(BLOCKING_SERVER_V6_SRC) $(BLOCKING_SERVER_V7_SRC)

.PHONY: all
all: $(TARGET)

$(BLOCKING_SERVER_V1_TARGET): $(BLOCKING_SERVER_V1_SRC)
	$(CC) -o $@ $^

$(BLOCKING_SERVER_V2_TARGET): $(BLOCKING_SERVER_V2_SRC)
	$(CC) -o $@ $^

$(BLOCKING_SERVER_V3_TARGET): $(BLOCKING_SERVER_V3_SRC)
	$(CC) -o $@ $^

$(BLOCKING_SERVER_V4_TARGET): $(BLOCKING_SERVER_V4_SRC)
	$(CC) -o $@ $^

$(BLOCKING_SERVER_V5_TARGET): $(BLOCKING_SERVER_V5_SRC)
	$(CC) -o $@ $^

$(BLOCKING_SERVER_V6_TARGET): $(BLOCKING_SERVER_V6_SRC)
	$(CC) -o $@ $^

$(BLOCKING_SERVER_V7_TARGET): $(BLOCKING_SERVER_V7_SRC)
	$(CC) -o $@ $^ -lpthread

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $^

%.o: %.o
	$(CC) $(CFLAGS) -c -o $@ $^
	
.PHONY: clean
clean:
	-rm -f $(TARGET) $(SRC)
