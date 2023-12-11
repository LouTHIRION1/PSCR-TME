all: clean client server

client: client.o Socket.o
	g++ -o client client.o Socket.o

client.o: client.cpp
	g++ -c client.cpp

Socket.o: Socket.cpp
	g++ -c Socket.cpp

server: server.o ServerSocket.o
	g++ -o server server.o ServerSocket.o Socket.o

server.o: server.cpp
	g++ -c server.cpp

ServerSocket.o: ServerSocket.cpp
	g++ -c ServerSocket.cpp

clean: 
	rm -f server
	rm -f client
	rm -f *.o