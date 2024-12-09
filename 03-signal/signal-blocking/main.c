#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_handle(int num) {
    printf("Action SIGINT with signal number: %d\n", num);
}
//BLOCK SIGINT
int main() {

    sigset_t new_set;

    if (signal(SIGINT, sig_handle) == SIG_ERR) {
        printf("Handle SIGINT fail\n");
        exit(EXIT_FAILURE);
    }

    sigemptyset(&new_set);
    sigaddset(&new_set, SIGINT);

    if(sigprocmask(SIG_SETMASK,&new_set, NULL) == 0) {
        if (sigismember(&new_set, SIGINT) == 1) {
            printf("SIGINT BLOCK\n");
        } else if (sigismember(&new_set, SIGINT) == 0) {
            printf("SIGINT UNBLOCK\n");
        } 
    }
    
    pid_t pid = getpid();
    while(1) {
        printf("My PID: %d\n", pid);
        sleep(3);
    }
}