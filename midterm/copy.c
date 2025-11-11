#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("오류: 사용법이 올바르지 않습니다.\n");
        printf("Usage: ./copy <option> <source_file> <dest_file>\n");
        return 1;
    }

    int option = atoi(argv[1]);
    char *source_filename = argv[2];
    char *dest_filename = argv[3];

    FILE *source_fp = fopen(source_filename, "r");
    if (source_fp == NULL) {
        printf("오류 메시지: 복사할 파일(%s)을 열 수 없습니다.\n", source_filename);
        return 1;
    }

    FILE *dest_fp = fopen(dest_filename, "w");
    if (dest_fp == NULL) {
        printf("오류 메시지: 복사본 파일(%s)을 생성할 수 없습니다.\n", dest_filename);
        fclose(source_fp);
        return 1;
    }

    int ch;
    int bytes_copied = 0;

    while ((ch = fgetc(source_fp)) != EOF) {
        int output_ch = ch;

        if (option == 1) { // 1: 모든 대문자를 소문자로
            output_ch = tolower(ch);
        } else if (option == 2) { // 2: 모든 소문자를 대문자로
            output_ch = toupper(ch);
        }
        
        if (fputc(output_ch, dest_fp) == EOF) {
            printf("오류 메시지: 파일에 쓰는 중 문제가 발생했습니다.\n");
            fclose(source_fp);
            fclose(dest_fp);
            return 1;
        }
        bytes_copied++;
    }

    fclose(source_fp);
    fclose(dest_fp);


    FILE *read_fp = fopen(dest_filename, "r");
    if (read_fp == NULL) {
        printf("오류: 복사된 파일을 읽을 수 없습니다.\n");
        return 1;
    }

    printf("결과 (%s 파일 내용) ", dest_filename);
    
    while ((ch = fgetc(read_fp)) != EOF) {
        putchar(ch);
    }
    printf("\n");

    fclose(read_fp);
    return 0;
}
