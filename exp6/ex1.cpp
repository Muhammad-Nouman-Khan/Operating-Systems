#include <iostream>              
#include <unistd.h>             
#include <fcntl.h>              
#include <sys/ipc.h>            
#include <sys/shm.h>            
#include <sys/wait.h>           
#include <cstring>              
#include <cstdlib>              
#include<stdio.h>
using namespace std;

void processData(char* data) {
    int len = strlen(data);
    int j = 0;
    for (int i = 0; i < len; i++) {
        char ch = data[i];
        if (isdigit(ch)) continue;
        if (isupper(ch)) data[j++] = tolower(ch);
        else if (islower(ch)) data[j++] = toupper(ch);
        else data[j++] = ch;
    }
    data[j] = '\0'; 
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    const char* filename = argv[1];
    const int SHM_SIZE = 4096; 

    int shmid = shmget(IPC_PRIVATE, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) {

        char *shmaddr = (char *)shmat(shmid, NULL, 0);
        if (shmaddr == (char *)-1) {
            perror("shmat - child");
            exit(1);
        }

        int file = open(filename, O_RDONLY);
        if (file == -1) {
            perror("open - child");
            exit(1);
        }

        read(file, shmaddr, SHM_SIZE);
        close(file);
        shmdt(shmaddr); 

       
        exit(0);
    }
    else {
     
        wait(NULL);

        char* shmaddr = (char *)shmat(shmid, NULL, 0);
        if (shmaddr == (char*) -1) {
            perror("shmat failed parent");
            return 1;
        }

        processData(shmaddr); 
        shmdt(shmaddr);       
       
        pid = fork();

        if (pid == 0) {
        
            shmaddr = (char *)shmat(shmid, NULL, 0);
            if (shmaddr == (char *)-1) {
                perror("shmat - child 2");
                exit(1);
            }

            int file = open(filename, O_WRONLY);
            if (file == -1) {
                perror("open - child 2");
                exit(1);
            }

            write(file, shmaddr, strlen(shmaddr));
            close(file);
            shmdt(shmaddr);
            exit(0);
        }

        wait(NULL); 
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
