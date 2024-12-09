#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_handle1(int num) {
    printf("Action Ctrl+C with signal number: %d\n", num);
}

void sig_handle2(int num) {
    printf("Action SIGUSR1 with signal number: %d\n", num);
}

void sig_handle3(int num) {
    printf("Action SIGUSR2 with signal number: %d\n", num);
}

int main() {
    if (signal(SIGINT, sig_handle1) == SIG_ERR) {
        printf("Handle SIGINT fail\n");
        exit(EXIT_FAILURE);
    }
    
    if (signal(SIGUSR1, sig_handle2) == SIG_ERR) {
        printf("Handle SIGUSR1 fail\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGUSR2, sig_handle3) == SIG_ERR) {
        printf("Handle SIGUSR2 fail\n");
        exit(EXIT_FAILURE);
    }

    pid_t pid = getpid();
    while(1) {
        printf("My PID: %d\n", pid);
        sleep(3);
    }
}