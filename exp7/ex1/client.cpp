#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[1024] = {0};
    const char *msg = "Hello from client";
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        cerr << "Socket creation failed" << endl;
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(4999);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr))) {
        cerr << "Connection failed" << endl;
        close(clientSocket);
        return 1;
    }

    cout << "Connected to server" << endl;
    
    send(clientSocket, msg, strlen(msg), 0);
    cout << "Message sent to server Successfully!" << endl;

    recv(clientSocket, buffer, 1024, 0);
    cout << "Message recieved from server: " << buffer << endl;
    
    
    close(clientSocket);

    return 0;
}
