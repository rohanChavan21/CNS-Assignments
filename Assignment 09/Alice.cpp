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

    SOCKET clientSocket;
    struct sockaddr_in serverAddress;

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket" << std::endl;
        WSACleanup();
        return -1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); //Localhost

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Error connecting to Bob" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return -1;
    }

    int xa = 4; // Alice's private key

    // Alice computes A = (alpha^xa) % p
    int A = powM(alpha, xa, p);
    std::cout << "Alice computes A: " << A << std::endl;

    // Send Alice's public value A to Bob
    send(clientSocket, (char*)&A, sizeof(A), 0);
    std::cout << "Sent Alice's public value A to Bob" << std::endl;

    // Receive Bob's public value B
    int B;
    recv(clientSocket, (char*)&B, sizeof(B), 0);
    std::cout << "Received Bob's public value B: " << B << std::endl;

    // Calculate the shared secret key
    int shared_key_alice = powM(B, xa, p);
    std::cout << "Shared key calculated by Alice: " << shared_key_alice << std::endl;

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
