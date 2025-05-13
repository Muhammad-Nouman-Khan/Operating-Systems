#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    int fd,i;
    char* data;
    struct stat st;

    
    if ((fd = open("test.txt", O_RDONLY)) == -1) {
        perror("open");
        exit(1);
    }

    if (fstat(fd, &st) == -1) {
        perror("fstat");
        close(fd);
        exit(1);
    }

    data = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(1);
    }

    printf("File contains:\n");
    for ( i = 0; i < st.st_size; i++) {
        printf("data[%zu]: %c\n", i, data[i]);
    }

    // Cleanup
    munmap(data, st.st_size);
    close(fd);

    return 0;
}
