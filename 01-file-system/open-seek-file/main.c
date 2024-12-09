#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <fcntl.h> 

int main(void) {
    int fd;
    char buf[12] = "hello world";
    char buf_add[9] = "test add";

    // Mở hoặc tạo tệp test.txt
    fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND , 0644);
    if (-1 == fd) {
        printf("open() test.txt failed\n");
        return 1;
    }

    // Ghi dữ liệu vào tệp
    if(write(fd, buf, strlen(buf)) == -1){
        printf("write() test.txt failed\n");
        close(fd);
        return 1;
    }

    // Dịch con trỏ về đầu tệp
    if(lseek(fd, 0 , SEEK_SET) == -1) {
        printf("lseek() test.txt failed\n");
        close(fd);
        return 1; 
    }

    // Ghi thêm buf_add
    // Buf_add được thêm vào cuối file gốc 
    // do cờ O_APPEND mặc định con trỏ ở cuối file 
    if(write(fd, buf_add , strlen(buf_add)) == -1) {
        printf("write() add test.txt failed\n");
        close(fd);
        return 1; 
    }

    // Đóng tệp
    close(fd);
}
