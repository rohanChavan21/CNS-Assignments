#include <iostream>
#include <cmath>
#include <winsock2.h>

long long p = 17; // Large prime number (public)
long long alpha = 5;  // Primitive root modulo p (public)

long long powM(long long a, long long b, long long n){
	if (b == 1){
		return a % n;
	}
	long long x = powM(a, b / 2, n);
	x = (x * x) % n;
	if (b % 2){
		x = (x * a) % n;
	}
	return x;
}

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock" << std::endl;
        return -1;
    }

    SOCKET serverSocket;
    struct sockaddr_in serverAddress;
    SOCKET clientSocket;
    struct sockaddr_in clientAddress;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket" << std::endl;
        WSACleanup();
        return -1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Error binding to port" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    listen(serverSocket, 1);
    std::cout << "Bob is waiting for Alice to connect..." << std::endl;

    int clientAddress_size = sizeof(clientAddress);
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddress_size);

    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error accepting the connection" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    int xb = 6; // Bob's private key

    // Receive Alice's public value A
    int A;
    recv(clientSocket, (char*)&A, sizeof(A), 0);
    std::cout << "Received Alice's public value A: " << A << std::endl;

    // Bob computes B = (alpha^xb) % p
    int B = powM(alpha, xb, p);
    std::cout << "Bob computes B: " << B << std::endl;

    // Send Bob's public value B to Alice
    send(clientSocket, (char*)&B, sizeof(B), 0);
    std::cout << "Sent Bob's public value B to Alice" << std::endl;

    // Calculate the shared secret key
    int shared_key_bob = powM(A, xb, p);
    std::cout << "Shared key calculated by Bob: " << shared_key_bob << std::endl;

    closesocket(serverSocket);
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
