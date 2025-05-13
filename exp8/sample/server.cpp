#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main () {

    const char* pipeName = "/tmp/calc_pipe";

    mkfifo(pipeName,0666);

    char buffer[100];

    while(true) {

        int pipe_fd = open(pipeName,O_RDONLY);

        dup2(pipe_fd,0);

        close(pipe_fd);

        cin.getline(buffer,sizeof(buffer));

        cout << "Data received : " << buffer << endl;

        pipe_fd = open(pipeName,O_WRONLY);

        dup2(pipe_fd,1);

        close(pipe_fd);

        cout << buffer << endl; //send same data back

    }

    unlink(pipeName);

    return 0;
}