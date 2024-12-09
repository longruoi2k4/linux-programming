#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void signal_handle (int signum) {
    printf("Handling signal ... \n");
    wait(NULL);
}

int main(int argc, char const *argv[]) {
    pid_t child_pid;

    // Tạo process con
    // Process A: parent process
    // process B: child process
    child_pid = fork();

    if (child_pid == 0) {
        printf("This is process B with PID: %d\n ", getpid());
        while(1);
    } else if (child_pid > 0) {

        signal(SIGCHLD, signal_handle);    
        printf("This is process A with PID: %d\n ", getpid());
        while(1);
    } else {
        printf("fork() unsuccess");
    }

    return 0;

}