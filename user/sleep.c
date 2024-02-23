//sleep.c: sleep a little time
//usage: sleep 10
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include <user/user.h>

int 
main (int argc, char *argv[]) {
    int secNum = 0;
    secNum = atoi(argv[1]);
    if(argc != 2 || secNum == 0) {
        printf("Please enter the correct format of the command like 'sleep 10' to sleep 10 second\n");
        exit(1);
    }
    sleep(secNum);
    //printf("sleep success");
    exit(0);
}