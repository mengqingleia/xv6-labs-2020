//pingpong.c "Ping pong" a byte between two processes

#include "kernel/types.h"
#include "user/user.h"

int 
main (int argc, char *argv[]) {
    char buf[1];
    int pid;
    int p1[2];
    int p2[2];

    pipe(p1);
    pipe(p2);
    pid = fork();//注意fork和pipe的前后顺序不能改
    if(pid < 0) {//创建失败，退出
        exit(1);
    }
    else if(pid == 0) {//子进程
        close(p1[1]);
        close(p2[0]);
        read(p1[0], buf, 1);
        printf("%d: received ping\n", getpid());
        write(p2[1], " ", 1);
        close(p1[0]);
        close(p2[1]);
        exit(0);
    }
    else {//父进程
        close(p1[0]);
        write(p1[1], " ", 1);
        close(p1[1]);

        close(p2[1]);
        read(p2[0], buf, 1);
        close(p2[0]);
        printf("%d: received pong\n", getpid());
        exit(0);
    }
    
}
