#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h> 

int main() {
    int sd;
    const char* msg = "connected";

    struct sockaddr_in my_addr, client_addr;

    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        perror("Socket creation failed");
        return 1;
    }


    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(4999);
    my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");



    if (bind(sd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr_in)) < 0) {
        perror("Bind failed");
        return 1;
    }


    listen(sd, 5);

    int i = 0;
    while (i < 1) {
        socklen_t size = sizeof(struct sockaddr_in); 
        int new_sd = accept(sd, (struct sockaddr*)&client_addr, &size);
        if (new_sd < 0) {
            perror("Accept failed");
            return 1;
        }

        send(new_sd, msg, 100, 0);
        close(new_sd);
        ++i;
    }

    close(sd);
    return 0;
}
