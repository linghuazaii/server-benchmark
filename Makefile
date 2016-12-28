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

BLOCKING_SERVER_V8_SRC=$(COMMON_SRC) ./blocking_server_v8.o
BLOCKING_SERVER_V8_TARGET=blocking_server_v8

BLOCKING_SERVER_V9_SRC=$(COMMON_SRC) ./blocking_server_v9.o
BLOCKING_SERVER_V9_TARGET=blocking_server_v9

BLOCKING_SERVER_V10_SRC=$(COMMON_SRC) ./blocking_server_v10.o
BLOCKING_SERVER_V10_TARGET=blocking_server_v10

BLOCKING_SERVER_V11_SRC=$(COMMON_SRC) ./blocking_server_v11.o
BLOCKING_SERVER_V11_TARGET=blocking_server_v11

BLOCKING_SERVER_V12_SRC=$(COMMON_SRC) ./select_thread_pool.o ./threadpool.o
BLOCKING_SERVER_V12_TARGET=select_thread_pool

BLOCKING_SERVER_V13_SRC=$(COMMON_SRC) ./poll_thread_pool.o ./threadpool.o
BLOCKING_SERVER_V13_TARGET=poll_thread_pool

BLOCKING_SERVER_V14_SRC=$(COMMON_SRC) ./epoll_thread_pool.o ./threadpool.o
BLOCKING_SERVER_V14_TARGET=epoll_thread_pool

TARGET=$(BLOCKING_SERVER_V1_TARGET) $(BLOCKING_SERVER_V2_TARGET) $(BLOCKING_SERVER_V3_TARGET) $(BLOCKING_SERVER_V4_TARGET) $(BLOCKING_SERVER_V5_TARGET) $(BLOCKING_SERVER_V6_TARGET) $(BLOCKING_SERVER_V7_TARGET) $(BLOCKING_SERVER_V8_TARGET) $(BLOCKING_SERVER_V9_TARGET) $(BLOCKING_SERVER_V10_TARGET) $(BLOCKING_SERVER_V11_TARGET) $(BLOCKING_SERVER_V12_TARGET) $(BLOCKING_SERVER_V13_TARGET) $(BLOCKING_SERVER_V14_TARGET)
SRC=$(BLOCKING_SERVER_V1_SRC) $(BLOCKING_SERVER_V2_SRC) $(BLOCKING_SERVER_V3_SRC) $(BLOCKING_SERVER_V4_SRC) $(BLOCKING_SERVER_V5_SRC) $(BLOCKING_SERVER_V6_SRC) $(BLOCKING_SERVER_V7_SRC) $(BLOCKING_SERVER_V8_SRC) $(BLOCKING_SERVER_V9_SRC) $(BLOCKING_SERVER_V10_SRC) $(BLOCKING_SERVER_V11_SRC) $(BLOCKING_SERVER_V12_SRC) $(BLOCKING_SERVER_V13_SRC) $(BLOCKING_SERVER_V14_SRC)




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

$(BLOCKING_SERVER_V8_TARGET): $(BLOCKING_SERVER_V8_SRC)
	$(CC) -o $@ $^ -lpthread

$(BLOCKING_SERVER_V9_TARGET): $(BLOCKING_SERVER_V9_SRC)
	$(CC) -o $@ $^ -lpthread

$(BLOCKING_SERVER_V10_TARGET): $(BLOCKING_SERVER_V10_SRC)
	$(CC) -o $@ $^ -lpthread

$(BLOCKING_SERVER_V11_TARGET): $(BLOCKING_SERVER_V11_SRC)
	$(CC) -o $@ $^ -lpthread

$(BLOCKING_SERVER_V12_TARGET): $(BLOCKING_SERVER_V12_SRC)
	$(CC) -o $@ $^ -lpthread

$(BLOCKING_SERVER_V13_TARGET): $(BLOCKING_SERVER_V13_SRC)
	$(CC) -o $@ $^ -lpthread

$(BLOCKING_SERVER_V14_TARGET): $(BLOCKING_SERVER_V14_SRC)
	$(CC) -o $@ $^ -lpthread

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^
	
.PHONY: clean
clean:
	-rm -f $(TARGET) $(SRC)
