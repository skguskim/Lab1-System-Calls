#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(int argc, char *argv[]) {
    char buf[512];
    int fd_src, fd_dest;
    int n;

    if(argc != 3){
        fprintf(2, "Usage: cp source destination\n");
        exit(1);
    }

    if((fd_src = open(argv[1], O_RDONLY)) < 0){
        fprintf(2, "cp: %s를 열 수 없습니다.\n", argv[1]);
        exit(1);
    }

    if((fd_dest = open(argv[2], O_CREATE | O_WRONLY)) < 0){
        fprintf(2, "cp: %s를 생성할 수 없습니다.\n", argv[2]);
        exit(1);
    }

    while((n = read(fd_src, buf, sizeof(buf))) > 0){
        write(fd_dest, buf, n);
    }

    close(fd_src);
    close(fd_dest);
    exit(0);
}