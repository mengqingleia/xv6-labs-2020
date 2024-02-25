#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"
#define MAX_LEN 100
int
main(int argc, char* argv[])
{
    char *command = argv[1];
    char bf;
    char paramv[MAXARG][MAX_LEN];
    char *m[MAXARG];

    while(1) {
        int count = argc - 1;
        memset(paramv, 0 , MAXARG * MAX_LEN);//初始化参数为空
        ////复制命令的参数
        for(int i = 1; i < argc; i++) {
            strcpy(paramv[i - 1], argv[i]);
        }    

        int cursor = 0;//光标指向single_arg中的字符位置
        int flag = 0;//标志，指示thers是否为空格前的参数
        int read_result;

        while((read_result = read(0, &bf, 1)) > 0 && bf != '\n') {
            if(bf == ' ' && flag == 1) {
                count++;

                cursor = 0;
                flag = 0;
            }
            else if(bf != ' ') {
                paramv[count][cursor++] = bf;
                flag = 1;
            }
        }
        if(read_result <= 0) {
            break;
        }
        for(int i = 0; i < MAXARG - 1; i++) {
            m[i] = paramv[i];
        }

        m[MAXARG - 1] = 0;
        if(fork() == 0) {
            exec(command, m);
            exit(0);
        }
        else {
            wait((int *)0);
        }
    }
    exit(0);
}
