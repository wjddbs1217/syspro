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
        printf("Usage: ./searchbook <book_name>\n");
        return 1;
    }

    char *target_name = argv[1];
    
    printf("input name of book ) %s\n", target_name);

    FILE *fp = fopen("db.dat", "rb");
    if (fp == NULL) {
        printf("Error: db.dat not found. Run ./bookcreate first.\n");
        return 1;
    }

    Book book;
    int found = 0;

    while (fread(&book, sizeof(Book), 1, fp) == 1) {
        if (strcmp(book.bookname, target_name) == 0) {
            if (!found) {
                print_header();
            }
            print_book(book);
            found = 1;
            break; 
        }
    }

    if (!found) {
        printf("not found book name : '%s'\n", target_name);
    }

    fclose(fp);
    return 0;
}
