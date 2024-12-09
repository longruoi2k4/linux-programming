#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct {
    char name[20];
    int year_date;
    char phone[15];
    char hometown[20];
} human;

static void *handle(void *args) {
    
    // Thread 1
    if(args == NULL) {
        printf("Thread 1 ...\n");
    } else {
        human *human_infor = (human *)args;
        printf("Thread 2 ...\n");
        printf("Name: %s\n", human_infor->name);
        printf("Year Date: %d\n", human_infor->year_date);
        printf("Phone: %s\n", human_infor->phone);
        printf("Homwtown: %s\n", human_infor->hometown);
    }
    pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {

    pthread_t thread1, thread2;
    // Tao du lieu Struct
    human thread_human;
    memset(&thread_human, 0x0, sizeof(human));

    strcpy(thread_human.name, "Long");
    strcpy(thread_human.phone, "0966599572");
    strcpy(thread_human.hometown, "Vinh Phuc");
    thread_human.year_date = 2004;

    if(pthread_create(&thread1, NULL, &handle ,NULL)) {
        printf("pthread_create() failed");
        return -1;
    }

    if(pthread_create(&thread2, NULL, &handle , &thread_human)) {
        printf("pthread_create() failed");
        return -1;
    }


    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}
