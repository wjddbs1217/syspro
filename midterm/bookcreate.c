#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char bookname[20];
    char author[20];
    int year;
    int numofborrow;
    int borrow; 
} Book;

int main() {

    Book initial_books[] = {
        {1, "1984", "George", 1949, 7, 0},   
        {2, "Luster", "Raven", 2020, 3, 1},   
        {3, "Hamnet", "Maggie", 2020, 0, 0},  
        {4, "theWish", "Nicholas", 2021, 2, 1} 
    };
    int num_books = sizeof(initial_books) / sizeof(Book);

    FILE *fp = fopen("db.dat", "wb");
    if (fp == NULL) {
        printf("Error: db.dat 파일을 쓸 수 없습니다.\n");
        return 1;
    }

    fwrite(initial_books, sizeof(Book), num_books, fp);

    fclose(fp);
    printf("초기 도서 기록이 db.dat에 성공적으로 저장되었습니다.\n");
    return 0;
}
