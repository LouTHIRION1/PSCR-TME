#include "TCPServer.h"
#include "Socket.h"
#include "ServerSocket.h"
#include <iostream>
#include <unistd.h>

namespace pr {

void TCPServer::handleClient(Socket scan) {
	int lu;
	read(scan.getFD(), &lu, sizeof(int));
	lu++;
	write(scan.getFD(), &lu, sizeof(int));
	scan.close();
}

bool TCPServer::startServer(int port) {
	ss = new ServerSocket(port);
	if(ss->isOpen()) {
		while(1) {
			std::cout<<"en attente sur le port "<<port <<std::endl;
			Socket sc = ss->accept();
			if(sc.isOpen()){
				// version Q1
				handleClient(sc); 
				// version Q2
				threads.emplace_back(&TCPServer::handleClient, this, sc); 
			}
		}
		return true;
	}
	return false;
}

TCPServer::~TCPServer(){
	for(auto &t : threads) {
		t.join();
	}
}

}