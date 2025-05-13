#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <cstring>

int main() {
    int sd;
    const char* msg = "connected";
    struct sockaddr_in server_addr, client_addr;

    // Step 1: Create UDP socket
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sd < 0) {
        perror("socket failed");
        return 1;
    }

    // Step 2: Set up server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(4999);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Step 3: Bind socket to address
    if (bind(sd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        return 1;
    }

    // Step 4: Wait for a message from client
    char buffer[100];
    socklen_t len = sizeof(client_addr);
    recvfrom(sd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &len);

    std::cout << "Received from client: " << buffer << std::endl;

    // Step 5: Send response to client
    sendto(sd, msg, strlen(msg) + 1, 0, (struct sockaddr*)&client_addr, len);

    close(sd);
    return 0;
}
