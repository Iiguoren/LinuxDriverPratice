#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fnctl.h>

int main(int argc, char **argv){
    int fd;
    if(argc < 2){
        printf("I need the file to open\n");
        return 1;
    }
    fd = open(argv[1], O_RDONLY);
    if(fd < 0){
        perror("open");
        return fd;
    }
    close fd;

    fd = open(argv[1], O_RDONLY|O_SYNC);
    if(fd < 0){
        perror("open");
        return fd;
    }
    close fd;

    fd = open(argv[1], O_WRDONLY|O_NOBLOCK);
    if(fd < 0){
        perror("open");
        return fd;
    }
    close fd;
    return 0;
}