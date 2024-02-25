#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
void find(char *path, char *target_file) {
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(path, 0)) < 0){
        fprintf(2, "ls: cannot open %s\n", path);
        return;
    }

    if(fstat(fd, &st) < 0){
        fprintf(2, "ls: cannot stat %s\n", path);
        close(fd);
        return;
    }

    while(read(fd, &de, sizeof(de)) == sizeof(de)) {
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';
        if(de.inum == 0) {
            continue;    
        }
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if(stat(buf, &st) < 0){
            printf("ls: cannot stat %s\n", buf);
        }
        switch(st.type){
            case T_FILE:
                if(strcmp(de.name, target_file) == 0){
                    printf("%s\n", buf);
                }
                break;

            case T_DIR:
                if((strcmp(de.name, ".") != 0) && (strcmp(de.name, "..") != 0)){
                    find(buf, target_file);
                }
     
        }
    }
    close(fd);
    return;
}


int 
main(int argc, char *argv[]) {
    
    if(argc == 3) {
        find(argv[1], argv[2]);
    }
    else {
        printf("Usage: find <path> <fileName>\n");
        exit(1);
    }
    exit(0);
}