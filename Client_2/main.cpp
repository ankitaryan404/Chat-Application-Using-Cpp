#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<thread>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

bool initialize() {
	WSADATA data;
	return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

void sendMessage(SOCKET s) {
	cout << "Enter your chat name : \n";
	string name;
	getline(cin, name);
	string message;

	while (1) {
		getline(cin, message);
		string msg = name + " : " + message;
		int bytesent = send(s, msg.c_str(), msg.size(), 0);
		if (bytesent == SOCKET_ERROR) {
			cout << "Error sending message \n";
			break;
		}

		if (message == "quit") {
			cout << "stopping the application \n";
			break;
		}
	}

	closesocket(s);
	WSACleanup();
}

void receiveMessage(SOCKET s) {
	char buffer[4096];
	int recvLength;
	string msg = "";

	while (1) {
		recvLength = recv(s, buffer, sizeof(buffer), 0);
		if (recvLength <= 0) {
			cout << "disconnected from the server \n";
			break;
		}
		else {
			msg = string(buffer, recvLength);
			cout << msg << "\n";
		}
	}

	closesocket(s);
	WSACleanup();
}

int main() {

	cout << "client program started \n";

	if (!initialize()) {
		cout << "Initialization winsock failed \n";
		return 1;
	}

	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET) {
		cout << "Invalid socket created \n";
		return 1;
	}

	int port = 12345;
	string serveraddress = "127.0.0.1";
	sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	inet_pton(AF_INET, serveraddress.c_str(), &(serveraddr.sin_addr));

	if (connect(s, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR) {
		cout << "Not able to connect to server \n";
		closesocket(s);
		WSACleanup();
		return 1;
	}

	cout << "successfully connected to server \n";

	thread senderThread(sendMessage, s);
	thread receiverThread(receiveMessage, s);

	senderThread.join();
	receiverThread.join();

	return 0;
}