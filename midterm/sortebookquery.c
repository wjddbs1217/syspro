#include <stdio.h>

struct BookRecord {
	int id;
	char name[100];
	char author[100];
	int publicationYear;
	int loanCount;
	int isAvailable;
};

struct BookRecord books[] = {
	{1, "1984", "George", 1949, 7, "False"},
	{2, "Luster", "Raven", 2020, 3, "True"},
	{3, "Hamnet", "Maggie", 2020, 1, "False"},
	{4, "theWish", "Nocholas", 2021, 2, "True"},

};

int numBooks = sizeof(books) / sizeof(books[0]);

void borrowBook(int bookId) {
	if (books[bookId - 1].isAvailable) {
		books[bookId - 1].isAvailable = 0;
		books[bookId - 1].loanCount++;
		printf("%s가 대출되며 대출 횟수가 %d로 증가하고 대출 유무는 0으로 변경됩니다.\n", books[bookId - 1].name, books[bookId - 1].loanCount);
} else {
	printf("%s는 이미 대출 중입니다. 대출할 수 없습니다.\n", books[bookId - 1].name);
}
}

void returnBook(int bookId) {
	if (!books[bookId - 1].isAvailable) {
		books[bookId - 1].isAvailable = 1;
		printf("%s가 반납되며 대출 유무가 1로 변경됩니다.\n", books[bookId - 1].name);
} else {
	printf("%s는 이미 반납되었습니다.\n", books[bookId - 1].name);
}
}

int main() {
int choice, bookId;

printf("도서 대출 및 반납 프로그램\n");
printf("0 책번호: 책을 대출\n");
printf("1 책번호: 책을 반납\n");
printf("예시 입력: 0 1 (대출 1984)\n");

while (1) {
	scanf("%d %d", &choice, &bookId);

	if (choice == 0) {
		if (bookId >= 1 && bookId <= numBooks) {
			borrowBook(bookId);
} else {
printf("올바르지 않은 책 번호입니다.\n");
}
} else if (choice == 1) {
	if (bookId >= 1 && bookId <= numBooks) {
		returnBook(bookId);
	}
}
}
}

