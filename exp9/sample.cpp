#include <stdio.h>      
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <semaphore.h>


// Create a program where a parent and a child process both increment and print a shared counter variable. Use shared memory for the counter and use a semaphore to ensure mutual exclusion so that the parent and child do not access the counter at the same time.

int main(int argc, char **argv) {
    int i, nloop = 10, *ptr;
    int shmid1, shmid2;
    int SHMSIZE = sizeof(int);  
    int SEMSIZE = sizeof(sem_t); 
    sem_t *p_mutex;

    if ((shmid1 = shmget(IPC_PRIVATE, SHMSIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget for counter");
        exit(1);
    }
    ptr = (int *)shmat(shmid1, NULL, 0);
    if (ptr == (int *)-1) {
        perror("shmat for counter");
        exit(1);
    }
    *ptr = 0; // Initialize counter

    // Shared memory for the semaphore
    if ((shmid2 = shmget(IPC_PRIVATE, SEMSIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget for semaphore");
        exit(1);
    }

    p_mutex = (sem_t *)shmat(shmid2, NULL, 0);
    if (p_mutex == (sem_t *)-1) {
        perror("shmat for semaphore");
        exit(1);
    }

    
    if (sem_init(p_mutex, 1, 1) == -1) {
        perror("sem_init");
        exit(1);
    }

    if (fork() == 0) {
        // Child process
        sem_wait(p_mutex);
        for (i = 0; i < nloop; i++)
            printf("child: %d\n", (*ptr)++);
        sem_post(p_mutex);

        shmdt(ptr);
        shmdt(p_mutex);
        exit(0);
    }

    sem_wait(p_mutex);
    for (i = 0; i < nloop; i++)
        printf("parent: %d\n", (*ptr)++);
    sem_post(p_mutex);

    wait(NULL); 

    sem_destroy(p_mutex);
    shmctl(shmid1, IPC_RMID, NULL);
    shmctl(shmid2, IPC_RMID, NULL);
    shmdt(ptr);
    shmdt(p_mutex);

    return 0;
}
