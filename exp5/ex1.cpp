#include<iostream>
#include<sys/wait.h>
#include<string.h>

using namespace std;

void toggleCase(char* str){
    for(int i=0;str[i] != '\0';i++){
        if(isupper(str[i])){
            str[i] = tolower(str[i]);
        }
        else if(islower(str[i])){
            str[i] = toupper(str[i]);
        }
    }
}

int main () {

    //pipe creation

    int pipe1[1],pipe2[2];

    pipe(pipe1);

    pipe(pipe2);

    
    //fork()
    pid_t pid;
    pid = fork();

    if(pid > 0){

        close(pipe1[0]);

        const char* message = "Hi There";

        cout << "Parent : Sending message to child : " << message << endl;

        write(pipe1[1],message,strlen(message)+1);

        close(pipe1[1]);

        char modifiedMessage[100];

        close(pipe2[1]);

        read(pipe2[0],modifiedMessage,sizeof(modifiedMessage));

        close(pipe2[0]);

        cout << "Parent: Received modified message from child: " << modifiedMessage << endl;

        wait(NULL);
        
    }
    else{
        close(pipe1[1]);
        
        char receivedMessage[100];

        read(pipe1[0],receivedMessage,sizeof(receivedMessage));

        close(pipe1[0]);

        cout << "Child : Received Message : "<< receivedMessage << endl;

        toggleCase(receivedMessage);

        close(pipe2[0]);

        write(pipe2[1],receivedMessage,strlen(receivedMessage) + 1);

        close(pipe2[1]);
    }


    return 0;
}