#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char const *argv[]) {
    pid_t child_pid;
    int status, check;

    // Tạo process con
    // Process A: parent process
    // process B: child process
    child_pid = fork();

    if (child_pid == 0) {
        printf("This is process B with PID: %d\n ", getpid());
        printf("My parent process PID: %d\n ", getppid());
        printf("Wait 5 seconds\n");
        sleep(5);
        exit(0);
    } else if (child_pid > 0) {
        check = wait(&status);
        
        if(check == -1 ) {
            printf("wait() unsucess!");
        }
        printf("This is process A with PID: %d\n ", getpid());
        printf("My child process PID: %d\n ", check);
        
    } else {
        printf("fork() unsuccess");
    }

    return 0;

}