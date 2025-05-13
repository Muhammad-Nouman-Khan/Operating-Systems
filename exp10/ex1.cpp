#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <cstring>
#include <cstdio>

using namespace std;

sem_t sem;
int count = 0;

void* searchSubstring(void* args) {
    void** argArray = (void**)args;
    char* start = (char*)argArray[0];
    size_t length = *(size_t*)argArray[1];
    string* target = (string*)argArray[2];
    
    
    string text(start, length);
    size_t pos = 0;

    while ((pos = text.find(*target, pos)) != string::npos) {
        sem_wait(&sem);
        count++;
        sem_post(&sem);
        pos += target->length();
    }

    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Invalid input arguments";
        return 1;
    }

    const char* filename = argv[1];
    string substring = argv[2];

    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        perror("fstat");
        close(fd);
        return 1;
    }
    size_t fileSize = sb.st_size;
    
    char* fileData = (char*)mmap(NULL, fileSize, PROT_READ, MAP_SHARED, fd, 0);
    if (fileData == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    close(fd);

    sem_init(&sem, 0, 1);

    pthread_t t1, t2;
    size_t half = fileSize / 2;
    size_t adjust = substring.length() - 1;
    if (fileSize < adjust) adjust = 0;

    void* args1[3];
    void* args2[3];
    size_t len1 = half + adjust;
    size_t len2 = fileSize - half;

    args1[0] = fileData;
    args1[1] = &len1;
    args1[2] = &substring;

    args2[0] = fileData + half;
    args2[1] = &len2;
    args2[2] = &substring;

    pthread_create(&t1, NULL, searchSubstring, args1);
    pthread_create(&t2, NULL, searchSubstring, args2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    sem_destroy(&sem);
    munmap(fileData, fileSize);
    cout << "Substring \"" << substring << "\" found " << count << " times.\n";
    return 0;
}
