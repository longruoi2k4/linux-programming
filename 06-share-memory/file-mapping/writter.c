#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>

#define SHM_SIZE 200
#define FILE_NAME "test_mmap"

int main() {

    /*Step 1: Create fd*/
    int shm_fd = shm_open(FILE_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd < 0) {
        printf("shm_open() failed, %s.\n", strerror(errno));
        return -1;
    }

    /*Step 2: Set size */
    ftruncate(shm_fd, SHM_SIZE);

    /*Step 3: Mapping*/
    char *data = (char *)mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    strcpy(data, "File mapping test !");
    printf("Data: %s.\n", data);

    munmap(data, SHM_SIZE);

    /*Step 4: Delete file mapping*/
      // close(shm_fd);
    return 0;
}