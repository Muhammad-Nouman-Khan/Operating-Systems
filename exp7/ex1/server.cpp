#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

int main() {
    int serverSocket, newSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize = sizeof(clientAddr);
    char buffer[1024] = {0};
    const char *msg = "Hello from server";

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        cerr << "Socket creation failed" << endl;
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(4999);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr))) {
        cerr << "Bind failed" << endl;
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 5)) {
        cerr << "Listen failed" << endl;
        close(serverSocket);
        return 1;
    }

    cout << "Server listening on port 4999..." << endl;

    newSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrSize);
    if (newSocket < 0) {
        cerr << "Accept failed" << endl;
        close(serverSocket);
        return 1;
    }

    cout << "Client connected" << endl;
    
    recv(newSocket,buffer,1024,0);
    
    cout << "Message recieved from client : " << buffer << endl;
    
    send(newSocket, msg, strlen(msg), 0);
    cout << "Message sent to client Successfully!" << endl;

    close(newSocket);
    close(serverSocket);

    return 0;
}
