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

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./bookquery <query_mode>\n");
        return 1;
    }

    int mode = atoi(argv[1]);

    FILE *fp = fopen("db.dat", "rb");
    if (fp == NULL) {
        printf("Error: db.dat not found. Run ./bookcreate first.\n");
        return 1;
    }

    Book book;
    int is_header_printed = 0;

    printf("bookId: list of all books, 1: list of available books) %d\n", mode);

    while (fread(&book, sizeof(Book), 1, fp) == 1) {
        int should_print = 0;

        if (mode == 0) { 
            should_print = 1;
        } else if (mode == 1) { 
            if (book.borrow == 0) {
                should_print = 1;
            }
        }

        if (should_print) {
            if (!is_header_printed) {
                print_header();
                is_header_printed = 1;
            }
            print_book(book);
        }
    }

    fclose(fp);
    return 0;
}
