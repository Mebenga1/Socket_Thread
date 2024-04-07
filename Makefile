CC= gcc
ARGS= -g -Wall
SERVER_OBJ= ./build/socket_thread_server.o ./build/socket_thread_server_main.o 
CLIENT_OBJ= ./build/socket_thread_client.o
SERVER= ./server
CLIENT= ./client

all: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJ)
	$(CC) $(ARGS) -o $(SERVER) $(SERVER_OBJ) -lpthread
	
./build/socket_thread_server.o: ./src/server/socket_thread_server.c ./src/server/socket_thread_server.h
	$(CC) $(ARGS) -o ./build/socket_thread_server.o -c ./src/server/socket_thread_server.c -I./src/server/ -lpthread
	
./build/socket_thread_server_main.o: ./src/server/socket_thread_server_main.c ./src/server/socket_thread_server.h
	$(CC) $(ARGS) -o ./build/socket_thread_server_main.o -c ./src/server/socket_thread_server_main.c -I./src/server/ -lpthread
	
$(CLIENT): $(CLIENT_OBJ)
	$(CC) $(ARGS) -o $(CLIENT) $(CLIENT_OBJ) 
	
./build/socket_thread_client.o: ./src/client/socket_thread_client.c 
	$(CC) $(ARGS) -o ./build/socket_thread_client.o -c ./src/client/socket_thread_client.c -I./src/client/ 

clean:
	rm -r -f ./build/* && rm -f $(SERVER) $(CLIENT) && rm -f ./file/*


