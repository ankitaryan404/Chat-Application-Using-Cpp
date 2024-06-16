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

## Files

- `server.cpp`: The server application.
- `client1.cpp`: The first client application.
- `client2.cpp`: The second client application (identical to client1.cpp).

## How to Build and Run

### Server

1. Open `server.cpp` in your C++ development environment.
2. Build the project.
3. Run the compiled executable.

### Clients

1. Open `client1.cpp` and `client2.cpp` in your C++ development environment.
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

1. Compile and run `server.cpp`.
2. The server will start listening on port `12345` for incoming client connections.
3. The server console will display messages from clients and broadcast them to all connected clients.

### Clients

1. Compile and run `client1.cpp` and `client2.cpp`.
2. Enter your chat name when prompted.
3. Type messages and press Enter to send. Type `quit` to exit the chat.

## Example

### Server Output

