//primes.c 

#include "kernel/types.h"
#include "user/user.h"
void child(int *pl);
int main() {
    int startNum = 2;
    int endNum = 35;
    int p[2];
    pipe(p);
    int pid = fork();
    if(pid < 0) {
        printf("fork() is failed\n");
        exit(1);
    }
    else if(pid == 0) {
        child(p);
    }
    else {
        //父进程
        close(p[0]);
        for(int i = startNum; i <= endNum; i++) {
            write(p[1], &i, sizeof(int));
        }
        close(p[1]);
        wait((int *)0);
    }
    exit(0);
}

void child(int *pl) {
    int n = 0;
    int pr[2];
    close(pl[1]);
    int result_num = read(pl[0], &n, sizeof(int));
    if(result_num == 0) {
        exit(0);
    }

    pipe(pr);
    if(fork() == 0) {
        child(pr);
    }
    else {
        close(pr[0]);
        printf("prime %d\n", n);
        int prime = n;
        while(read(pl[0], &n, sizeof(n)) != 0) {
            if(n % prime != 0) {
                write(pr[1], &n, sizeof(n));
            } 
        }
        close(pr[1]);
        wait((int *)0);
        exit(0);
    }
    

}