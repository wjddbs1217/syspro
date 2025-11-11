#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char bookname[20];
    char author[20];
    int year;
    int numofborrow;
    int borrow; 
} Book;

void print_header() {
    printf("%-5s%-20s%-15s%-8s%-15s%-8s\n",
           "Id", "bookname", "author", "year", "numofborrow", "borrow");
}

void print_book(Book b) {
    printf("%-5d%-20s%-15s%-8d%-15d%-8s\n",
           b.id, b.bookname, b.author, b.year, b.numofborrow, 
           b.borrow ? "True" : "False");
}

// numofborrow 내림차순 비교 함수 (qsort 사용)
int compare_numofborrow(const void *a, const void *b) {
    Book *bookA = (Book *)a;
    Book *bookB = (Book *)b;
    // 내림차순 정렬
    return bookB->numofborrow - bookA->numofborrow; 
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./sortedbookquery <query_mode>\n");
        return 1;
    }

    int mode = atoi(argv[1]);

    FILE *fp = fopen("db.dat", "rb");
    if (fp == NULL) {
        printf("Error: db.dat not found. Run ./bookcreate first.\n");
        return 1;
    }

    Book books[100]; 
    int count = 0;

    while (fread(&books[count], sizeof(Book), 1, fp) == 1) {
        count++;
    }
    fclose(fp);

    qsort(books, count, sizeof(Book), compare_numofborrow);

    printf("bookId: list of all books, 1: list of available books) %d\n", mode);
    print_header();

    for (int i = 0; i < count; i++) {
        if (mode == 0) { 
            print_book(books[i]);
        } else if (mode == 1 && books[i].borrow == 0) { 
            print_book(books[i]);
        }
    }

    return 0;
}
