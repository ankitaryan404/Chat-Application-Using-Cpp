# Chat Application Using C++

## Overview

This project is a simple chat application demonstrating socket programming using WinSock in C++. It includes a server and two clients. The server accepts multiple client connections, and clients can send messages to the server, which then broadcasts the messages to all connected clients.

## Features

- Multiple client support
- Real-time message broadcasting to all connected clients
- Simple console-based chat interface

## Requirements

- Windows OS
- Microsoft Visual Studio or any other C++ compiler that supports WinSock
- Basic knowledge of C++ and socket programming

## Files/Folders

- `Server/main.cpp`: The server application.
- `Client_1/main.cpp`: The first client application.
- `Client_2/main.cpp`: The second client application (identical to Client_1).

## How to Build and Run

### Server

1. Open `Server/main.cpp` in your C++ development environment.
2. Build the project.
3. Run the compiled executable.

### Clients

1. Open `Client_1/main.cpp` and `Client_2/main.cpp` in your C++ development environment.
2. Build both projects.
3. Run the compiled executables for each client.

### Detailed Steps

1. **Initialize WinSock Library**:
   - The `initialize` function sets up the WinSock library for use.

2. **Create Socket**:
   - The server and clients create a socket using `socket(AF_INET, SOCK_STREAM, 0)`.

3. **Bind IP/Port (Server)**:
   - The server binds the IP and port using the `bind` function.

4. **Listen (Server)**:
   - The server starts listening for incoming connections using the `listen` function.

5. **Accept Connections (Server)**:
   - The server accepts incoming client connections with the `accept` function and starts a new thread for each client.

6. **Connect to Server (Client)**:
   - The clients connect to the server using the `connect` function.

7. **Send and Receive Messages**:
   - Both the server and clients use `send` and `recv` to exchange messages.

8. **Close Socket and Cleanup**:
   - After communication, sockets are closed using `closesocket`, and the WinSock library is cleaned up with `WSACleanup`.

## Usage

### Server

1. Compile and run `Server/main.cpp`.
2. The server will start listening on port `12345` for incoming client connections.
3. The server console will display messages from clients and broadcast them to all connected clients.

### Clients

1. Compile and run `Client_1/main.cpp` and `Client_2/main.cpp`.
2. Enter your chat name when prompted.
3. Type messages and press Enter to send. Type `quit` to exit the chat.

## Example

### Server Output
Server program
Server has started listening on port : 12345
client connected
Message from client : Ankit: Hello, World!
Message from client : Amit: Hi, Ankit!


### Client Output

client program started
successfully connected to server
Enter your chat name :
Ankit
Ankit : Hello, World!
Amit : Hi, Ankit!


## Note

- The clients automatically disconnect from the server if the message "quit" is sent.
- Make sure to run the server before starting the clients to ensure they can connect successfully.

## Troubleshooting

- If the server or client fails to start, ensure that the WinSock library is properly initialized.
- Check for any firewall or network issues that might block the server or client from connecting.
- Ensure that the server and clients are using the same port number (`12345`).

