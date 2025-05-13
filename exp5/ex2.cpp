#include<iostream>
#include <fcntl.h>
#include<sys/wait.h>
#include<cstdlib>
using namespace std;

int main(int argc,char *argv[]) {

    const char* sourceFile = argv[1];
    
    const char* destFile = argv[2];

    //pipes creation

    int fd[2];

    pipe(fd);

    //fork()

    pid_t pid = fork();
   

    if(pid == 0) {

        close(fd[1]);

        int dest = open(destFile,O_WRONLY | O_CREAT | O_TRUNC, 0644);

        char buffer[1024];

        ssize_t bytesRead;

        while((bytesRead = read(fd[0],buffer,sizeof(buffer))) > 0) {
            write(dest,buffer,bytesRead);
        }

        close(fd[0]);
        close(dest);
        exit(0);
    }
    else{

        close(fd[0]);

        int source = open(sourceFile,O_RDONLY);

        char buffer[1024];

        ssize_t bytesRead;

        while((bytesRead = read(source,buffer,sizeof(buffer))) > 0) {
            write(fd[1],buffer,bytesRead);
        }

        close(source);
        close(fd[1]);
        wait(NULL);


    }

    cout << "✅ File copied successfully using pipe." << endl;

    return 0;
}