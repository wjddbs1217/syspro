#include <stdio.h>

struct BookRecord {
	int id;char name[100];
	char author[100];
	int publicationYear;
	int loanCount;
	int isAvailable;
};

int main() {
	struct BookRecord books[] = {
		{1, "1984", "George", 1949, 7, "False"},
		{2, "Luster", "Raven", 2020, 3, "True"},
		{3, "Hamnet", "Maggie", 2020, 1, "False"},
		{4, "theWish", "Nicholas", 2021, 2, "True"},
};
int numBooks = sizeof(books) / sizeof(books[0]);
printf("list of all book, 1: list of available books\n");
printf("id\tbookname\tauthor\tyear\tnumofborrow borrow \n");
for (int i = 0; i < numBooks; i++) {
	if (books[i].isAvailable) {
		printf("%d\t\t%s\t\t%s\t\t%d\n", books[i].id, books[i].name, books[i].author, books[i].publicationYear);
	}
}

return 0;
}

