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
    if (argc != 3) {
        printf("Usage: ./bookupdate <operation_mode> <bookId>\n");
        return 1;
    }

    int mode = atoi(argv[1]);
    int target_id = atoi(argv[2]);

    FILE *fp = fopen("db.dat", "r+b"); 
    if (fp == NULL) {
        printf("Error: db.dat not found. Run ./bookcreate first.\n");
        return 1;
    }

    Book book;
    long record_offset = -1;
    int found = 0;

    while (fread(&book, sizeof(Book), 1, fp) == 1) {
        if (book.id == target_id) {
            found = 1;
            record_offset = ftell(fp) - sizeof(Book);
            break;
        }
    }

    if (!found) {
        printf("Error: Book with ID %d not found.\n", target_id);
        fclose(fp);
        return 1;
    }

    if (mode == 0) { 
        printf("bookId: borrow book, 1 bookId: return book ) 0 %d\n", target_id);
        if (book.borrow == 0) { 
            book.borrow = 1;        
            book.numofborrow++;     

            fseek(fp, record_offset, SEEK_SET); 
            fwrite(&book, sizeof(Book), 1, fp); 

            printf("You've got bellow book..\n");
        } else { 
            printf("You cannot borrow below book since it has been booked.\n");
        }
    } else if (mode == 1) { 
        printf("bookId: borrow book, 1 bookId: return book ) 1 %d\n", target_id);
        if (book.borrow == 1) { 
            book.borrow = 0;        

            fseek(fp, record_offset, SEEK_SET); 
            fwrite(&book, sizeof(Book), 1, fp); 

            printf("You've returned bellow book..\n");
        } else { 
             printf("You cannot return below book since it is not currently borrowed.\n");
        }
    } else {
        printf("Invalid operation mode. Use 0 for borrow or 1 for return.\n");
    }

    print_header();
    print_book(book);

    fclose(fp);
    return 0;
}
