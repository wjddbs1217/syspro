#include <stdio.h>

struct BookRecord {
	int id;
    char name[100];
    char author[100];
    int publicationYear;
    int loanCount;
    int isAvailable;
};

int main() {
	struct BookRecord books[] = {
		{1, "1984", "George", 1949, 0, 1},
        {2, "Luster", "Raven", 2020, 0, 1},
        {3, "Hamnet", "Maggie", 2020, 0, 1},
        {4, "theWish", "Nicholas", 2021, 0, 1},
};
int numBooks = sizeof(books) / sizeof(books[0]);
printf("모든 책의 정보를 출력\n");
printf("아이디\t책 이�\t저자이름\t출판년도\t대출횟수\t대출 유무 \n");
for (int i = 0; i < numBooks; i++) {
	if (books[i].isAvailable) {
		printf("%d\t\t%s\t\t%s\t\t%d\n", books[i].id, books[i].name, books[i].author, books[i].publicationYear);
	}
}

return 0;
}
