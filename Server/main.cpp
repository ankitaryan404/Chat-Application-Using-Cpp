#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<tchar.h>
#include<thread>
#include<vector>

using namespace std;
#pragma comment(lib, "ws2_32.lib")

bool initialize() {
	WSADATA data;
	return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

void interactWithClient(SOCKET clientSocket, vector<SOCKET>& clients) {
	//send/recv

	cout << "client connected \n";
	char buffer[4096];

	while (1) {
		int bytesrecvd = recv(clientSocket, buffer, sizeof(buffer), 0);

		if (bytesrecvd <= 0) {
			cout << "client disconnected \n";
			break;
		}

		string message(buffer, bytesrecvd);
		cout << "Message from client : " << message << endl;

		for (auto& client : clients) {
			if (client != clientSocket) {
				send(client, message.c_str(), message.size(), 0);
			}
		}
	}

	auto it = find(clients.begin(), clients.end(), clientSocket);
	if (it != clients.end()) {
		clients.erase(it);
	}
	closesocket(clientSocket);
}

int main() {
	if (!initialize()) {
		cout << "winsock initialization failed \n";
		return 1;
	}
	cout << "Server program \n";

	// create the socket , here we are using Ipv4 mechanism 
	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (listenSocket == INVALID_SOCKET) {
		cout << "socket creation failed \n";
		return 1;
	}

	//create address structure
	int port = 12345;
	sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);

	//convert the ipaddress(0.0.0.0) put it inside the sin_family in binary form
	if (InetPton(AF_INET, _T("0.0.0.0"), &serveraddr.sin_addr) != 1) {
		cout << "setting address structure failed \n";
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	//bind
	if (bind(listenSocket, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR) {
		cout << "Bind failed \n";
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	//listen
	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
		cout << "Listen failed \n";
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	cout << "Server has started listening on port : " << port << endl;
	vector<SOCKET> clients;

	while (1) {
		//accept
		SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
		if (clientSocket == INVALID_SOCKET) {
			cout << "Invalid client socket \n";
		}

		clients.push_back(clientSocket);
		thread t1(interactWithClient, clientSocket, std::ref(clients));
		t1.detach();
	}

	closesocket(listenSocket);

	WSACleanup();
	return 0;
}