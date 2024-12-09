#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char const *argv[]) {
    pid_t child_pid;

    // Tạo process con
    child_pid = fork();

    if (child_pid == 0) {
        printf("This is child process B with PID: %d\n ", getpid());
        printf("My parent process A PID: %d\n ", getppid());
    } else if (child_pid > 0) {
        printf("This is parent process A with PID: %d\n ", getpid());
    } else {
        printf("fork() unsuccess");
    }

    return 0;

}