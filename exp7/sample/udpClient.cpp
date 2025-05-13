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
    char buffer[100];
    struct sockaddr_in server_addr;

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

    // Step 3: Send message to server
    const char* hello = "Hello Server!";
    sendto(sd, hello, strlen(hello) + 1, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Step 4: Receive response from server
    socklen_t len = sizeof(server_addr);
    recvfrom(sd, buffer, sizeof(buffer), 0, (struct sockaddr*)&server_addr, &len);

    std::cout << "Message from server: " << buffer << std::endl;

    close(sd);
    return 0;
}
