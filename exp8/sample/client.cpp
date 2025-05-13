#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main () {

    const char* pipeName = "/tmp/calc_pipe";

    char input[100]; //data to write to the pipe
    char buffer[100];
    cout << "Enter data to send : " << endl;

    cin.getline(input,100);

    int pipe_fd = open(pipeName,O_WRONLY);
    
    dup2(pipe_fd,1);

    close(pipe_fd);

    cout << input << endl;

    pipe_fd = open(pipeName,O_RDONLY);

    dup2(pipe_fd,0);

    close(pipe_fd);

    cin.getline(buffer,sizeof(buffer));

    cout << "Data received back : " << buff << endl;

    return 0;
}