#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// Struct student
typedef struct {
    char name[20];
    int year_date;
    char hometown[20];
} Student;

Student student;

int checkAdd = 1;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond3 = PTHREAD_COND_INITIALIZER;

static void *thread_handle1(void *arg) {
    while(1) {
        pthread_mutex_lock(&mutex);
        while (!checkAdd) {
            pthread_cond_wait(&cond1, &mutex);
        }
        // Nhập thông tin
        printf("Enter name: ");
        fgets(student.name, 20, stdin);
        student.name[strcspn(student.name, "\n")] = '\0';
        
        printf("Enter year date: ");
        char input[10];
        fgets(input, 10, stdin);
        input[strcspn(input, "\n")] = '\0';
        student.year_date = atoi(input);

        printf("Enter hometown: ");
        fgets(student.hometown, 20, stdin);
        student.hometown[strcspn(student.hometown, "\n")] = '\0';

        checkAdd  = 0;

        pthread_cond_signal(&cond2); // Gửi tín hiệu cho thread 2.
        pthread_mutex_unlock(&mutex);
         
        pthread_cond_wait(&cond1, &mutex); // Chờ tín hiệu từ thread 3.
    }
    pthread_exit(NULL);
}

static void *thread_handle2(void *arg) {
    int fd;
    while(1) {
        pthread_cond_wait(&cond2, &mutex); // Thread 2 đợi.

        // Tạo mới file nếu không tồn tại.
        fd = open("studentInfor.txt", O_WRONLY | O_CREAT | O_APPEND, 0644); 
        if(fd == -1) {
            printf("openFile() failed");
            exit(EXIT_FAILURE);
        }

        // Ghi thông tin vào file.
        if(dprintf(fd, "Name: %s\n", student.name) < 0 ||
           dprintf(fd, "Year date: %d\n", student.year_date) < 0 ||
           dprintf(fd, "Hometown: %s\n", student.hometown) < 0) {
            printf("dprintf() failed");
            close(fd);
            exit(EXIT_FAILURE);
        }

        close(fd);

        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond3); // Gửi tín hiệu cho thread 3.
        
    }
    pthread_exit(NULL);
}

static void *thread_handle3(void *arg) {
    char line[100];
    while(1) {
        pthread_cond_wait(&cond3, &mutex); // Thread 3 đợi.

        int fd = open("studentInfor.txt", O_RDONLY);
        if(fd == -1) {
            printf("openFile() failed");
            exit(EXIT_FAILURE);
        }

        // Ghi thông tin vào màn hình.
        printf("Data added recently:\n");
        while(read(fd, line, 100) > 0) {
            printf("%s", line);
        }

        close(fd);

        checkAdd  = 1;

        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond1); // Gửi tín hiệu cho thread 1.
    }
    pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {

    pthread_t thread1, thread2, thread3;

    if(pthread_create(&thread1, NULL, &thread_handle1 , NULL)) {
        printf("pthread_create() failed");
        return -1;
    }

    if(pthread_create(&thread2, NULL, &thread_handle2 , NULL)) {
        printf("pthread_create() failed");
        return -1;
    }
    if(pthread_create(&thread3, NULL, &thread_handle3 , NULL)) {
        printf("pthread_create() failed");
        return -1;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond1);
    pthread_cond_destroy(&cond2);
    pthread_cond_destroy(&cond3);

    return 0;
}
