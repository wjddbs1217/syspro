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

typedef struct Node {
    Book data;
    struct Node *next;
} Node;

// 연결 리스트에 연도(year) 내림차순으로 노드를 삽입하는 함수
Node* insert_sorted(Node *head, Book new_book) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("Error allocating memory");
        return head;
    }
    new_node->data = new_book;
    new_node->next = NULL;

    // 리스트가 비어있거나 새 노드의 year가 head보다 클 경우 (내림차순)
    if (head == NULL || new_book.year > head->data.year) {
        new_node->next = head;
        return new_node;
    }

    Node *current = head;
    // 새 노드의 year가 current의 다음 노드의 year보다 크거나 같아질 때까지 이동
    while (current->next != NULL && new_book.year <= current->next->data.year) {
        current = current->next;
    }
    
    new_node->next = current->next;
    current->next = new_node;
    return head;
}

// 연결 리스트의 메모리를 해제하는 함수
void free_list(Node *head) {
    Node *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    // 문제에 제시된 초기 데이터
    Book initial_books[] = {
        {1, "1984", "George", 1949, 7, 0},
        {2, "Luster", "Raven", 2020, 3, 1},
        {3, "Hamnet", "Maggie", 2020, 0, 0},
        {4, "theWish", "Nicholas", 2021, 2, 1}
    };
    int num_books = sizeof(initial_books) / sizeof(Book);

    Node *head = NULL;

    for (int i = 0; i < num_books; i++) {
        head = insert_sorted(head, initial_books[i]);
    }

    FILE *fp = fopen("db.dat", "wb");
    if (fp == NULL) {
        printf("Error: Could not open db.dat for writing.\n");
        free_list(head);
        return 1;
    }

    Node *current = head;
    while (current != NULL) {
        fwrite(&(current->data), sizeof(Book), 1, fp);
        current = current->next;
    }

    fclose(fp);
    free_list(head);
    printf("Book records sorted by year (descending) and saved to db.dat.\n");
    return 0;
}
