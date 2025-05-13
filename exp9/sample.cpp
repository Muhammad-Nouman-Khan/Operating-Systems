#include<iostream>
#include <stdio.h>      
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <semaphore.h>
using namespace std;

//Create a program where a parent and a child process both increment and print a shared counter variable. Use shared memory for the counter and use a semaphore to ensure mutual exclusion so that the parent and child do not access the counter at the same time.

int main () {

    int shmid1 = shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT | 0666);

    int *ptr = (int *)shmat(shmid1,NULL,0);

    *ptr = 0;   

    int shmid2 = shmget(IPC_PRIVATE,sizeof(sem_t),IPC_CREAT | 0666);

    sem_t* p_mutex = (sem_t*) shmat(shmid2,NULL,0);

    sem_init(p_mutex,1,1);  // If 1: shared between multiple processes (must be in shared memory)
    // If 0: semaphore is shared between threads of the same process

    if(fork() == 0) {

        sem_wait(p_mutex);
        for(int i =0;i<10;i++){
            cout << "child : " << ((*ptr)++) << endl;
        }
        sem_post(p_mutex);

        shmdt(ptr);
        shmdt(p_mutex);
        exit(0);

    }
    sem_wait(p_mutex);
    for(int i =0;i<10;i++){
        cout << "parent : " << ((*ptr)++) << endl;
    }
    sem_post(p_mutex);

    wait(NULL);

    sem_destroy(p_mutex);
    shmctl(shmid1,IPC_RMID,NULL);
    shmctl(shmid2,IPC_RMID,NULL);
    shmdt(ptr);
    shmdt(p_mutex);

    return 0;
}