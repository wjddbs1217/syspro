#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

extern char **environ; 

int main(int argc, char *argv[]) {
    int opt;
    const char *optstring = "e::u::g::i::p::"; 

    if (argc == 1) {
        fprintf(stderr, "사용법: %s -e [환경변수명] | -u | -g | -i | -p\n", argv[0]);
        return 1;
    }
    while ((opt = getopt(argc, argv, optstring)) != -1) {
        switch (opt) {
            case 'e':
                if (optarg != NULL) {
                    char *val = getenv(optarg);
                    if (val != NULL) {
                        printf("환경 변수 (%s): %s\n", optarg, val);
                    } else {
                        printf("환경 변수 (%s): 찾을 수 없음\n", optarg);
                    }
                } else {
                    printf("---  ---\n");
                    for (char **env = environ; *env != NULL; env++) {
                        printf("%s\n", *env);
                    }
                    printf("-----------------------\n");
                }
                break;
                
            case 'u':
                printf("real user ID (UID): %d\n", getuid());
                printf("valid user ID (EUID): %d\n", geteuid());
                break;

            case 'g':
                printf("real user ID (GID): %d\n", getgid());
                printf("valid user ID (EGID): %d\n", getegid());
                break;

            case 'i':
                printf("Process ID (PID): %d\n", getpid());
                break;

            case 'p':
                printf("Parent Process ID (PPID): %d\n", getppid());
                break;

            case '?':
                fprintf(stderr, "omission\n");
                return 1;

            default:
                fprintf(stderr, "error\n");
                return 1;
        }
    }

    return 0;
}
