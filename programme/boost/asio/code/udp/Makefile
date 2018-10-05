all: client server


client:
	g++ -std=c++11  ./client.cpp -o client  -lboost_system -lpthread -g

server:
	g++ -std=c++11  ./server_sync.cpp -o server_sync  -lboost_system -lpthread -g
