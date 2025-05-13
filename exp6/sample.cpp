#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        exit(1);
    }
    
    int num = atoi(argv[1]);
    int shmid = shmget(3434, sizeof(int), 0666 | IPC_CREAT);
    if (shmid ==-1) { perror("shmget"); exit(1); }
    
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }
    
    if (pid == 0) { // Child process: write integer to shared memory
        int *p = shmat(shmid, NULL, 0);
        *p = num;
        shmdt(p);
        exit(0);
    }
    else {
    wait(NULL);  // Parent waits for child
    int *p = shmat(shmid, NULL, 0);
    printf("Shared integer: %d\n", *p);
    shmdt(p);
    shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}
