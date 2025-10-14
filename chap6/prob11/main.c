#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char*, char*, struct stat*, int, int, int);

int main(int argc, char **argv) {
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ+1];

    // 옵션 플래그
    int show_inode = 0, quote_name = 0, append_slash = 0;

    // 디렉토리 이름과 옵션 파싱
    int opt;
    while ((opt = getopt(argc, argv, "iQp")) != -1) {
        switch (opt) {
            case 'i': show_inode = 1; break;
            case 'Q': quote_name = 1; break;
            case 'p': append_slash = 1; break;
        }
    }

    // 디렉토리 설정
    if (optind == argc)
        dir = ".";
    else
        dir = argv[optind];

    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(1);
    }

    while ((d = readdir(dp)) != NULL) {
        sprintf(path, "%s/%s", dir, d->d_name);
        if (lstat(path, &st) < 0)
            perror(path);
        else
            printStat(path, d->d_name, &st, show_inode, quote_name, append_slash);
    }

    closedir(dp);
    return 0;
}

void printStat(char *pathname, char *file, struct stat *st, int show_inode, int quote_name, int append_slash) {
    if (show_inode)
        printf("%lu ", st->st_ino);

    // 기본 정보 출력
    if (!show_inode && !quote_name && !append_slash) {
        printf("%5ld ", st->st_blocks);
        printf("%c%s ", type(st->st_mode), perm(st->st_mode));
        printf("%3ld ", st->st_nlink);
        printf("%s %s ", getpwuid(st->st_uid)->pw_name,
                        getgrgid(st->st_gid)->gr_name);
        printf("%9ld ", st->st_size);
        printf("%.12s ", ctime(&st->st_mtime)+4);
    }

    // 파일 이름 출력
    if (quote_name)
        printf("\"%s", file);
    else
        printf("%s", file);

    // 디렉토리이면 `/` 붙이기
    if (append_slash && S_ISDIR(st->st_mode))
        printf("/");

    if (quote_name)
        printf("\"");

    printf("\n");
}

char type(mode_t mode) {
    if (S_ISREG(mode)) return('-');
    if (S_ISDIR(mode)) return('d');
    if (S_ISCHR(mode)) return('c');
    if (S_ISBLK(mode)) return('b');
    if (S_ISLNK(mode)) return('l');
    if (S_ISFIFO(mode)) return('p');
    if (S_ISSOCK(mode)) return('s');
    return('?');
}

char* perm(mode_t mode) {
    static char perms[10];
    strcpy(perms, "---------");

    for (int i = 0; i < 3; i++) {
        if (mode & (S_IRUSR >> i*3))
            perms[i*3] = 'r';
        if (mode & (S_IWUSR >> i*3))
            perms[i*3+1] = 'w';
        if (mode & (S_IXUSR >> i*3))
            perms[i*3+2] = 'x';
    }

    return perms;
}

