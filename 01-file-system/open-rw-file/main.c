#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/stat.h>
#include <time.h>

int main(void) {
    int fd;
    int numb_write;
    char buf[12] = "hello world\n";

    // Mở hoặc tạo tệp test.txt
    fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (-1 == fd) {
        printf("open() test.txt failed\n");
        return 1;
    }

    // Ghi dữ liệu vào tệp
    numb_write = write(fd, buf, strlen(buf));
    printf("Write %d bytes to test.txt\n", numb_write);

    // Đóng tệp
    close(fd);

    // Lấy thông tin file
    struct stat fileStat;
    if (stat("test.txt", &fileStat) == -1) {
        perror("stat() failed");
        return 1;
    }

    // In thông tin về loại file
    printf("\nThong tin file:\n");
    if (S_ISREG(fileStat.st_mode))
        printf("Loai file: Regular file\n");
    else if (S_ISDIR(fileStat.st_mode))
        printf("Loai file: Directory\n");
    else
        printf("Loai file: Unknown\n");

    // In tên file
    printf("Ten file: test.txt\n");

    // In thời gian chỉnh sửa file lần cuối
    char timebuf[26];
    struct tm *tm_info = localtime(&fileStat.st_mtime);
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Thoi gian sua doi cuoi: %s\n", timebuf);

    return 0;
}
