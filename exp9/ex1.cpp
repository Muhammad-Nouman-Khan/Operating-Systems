#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

sem_t mutex;
int counter = 0;

void* threadFunction(void* arg) {
    int id = *((int*) arg);

    for (int i = 0; i < 5; i++) {
        sem_wait(&mutex);
        counter++;
        cout << "Thread " << id << " incremented counter to " << counter << endl;
        sem_post(&mutex);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t threads[4];
    int ids[4]; 

    sem_init(&mutex, 0, 1);

    for (int i = 0; i < 4; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, threadFunction, &ids[i]);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&mutex);
    cout << "Final counter Value : " << counter << endl;
    return 0;
}
