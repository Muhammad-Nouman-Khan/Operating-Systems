#include <unistd.h>           
#include <sys/types.h>        
#include <sys/socket.h>     
#include <netinet/in.h>       
#include <stdio.h>          
#include <arpa/inet.h>       

int main() {
    int sd;              
    char msg[100];         

    struct sockaddr_in server_addr;


    server_addr.sin_family = AF_INET;             
    server_addr.sin_port = htons(4999);               
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 


    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        perror("Socket creation failed");
        return 1;
    }


    if (connect(sd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) < 0) {
        perror("Connection failed");
        return 1;
    }


    recv(sd, msg, 100, 0);


    printf("Server says: %s\n", msg);


    close(sd);

    return 0;
}
