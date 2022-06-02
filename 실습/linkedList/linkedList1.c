#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

// Linkedlist Node
typedef struct Node {
	struct Node* prev;
	struct Node* next;
	char elem;
}Node;

typedef struct List {
	Node* head;
	Node* tail;
	int count;
}List;

// 함수 선언
Node* GenNode(char c);
void init(List* list);
void add(List* list, char c, int r);
void delete(List* list, int r);
void get(List* list, int r);
void print(List* list);

void main()
{
	List list; // 리스트 생성
	int N; // 실행횟수
	char c; // elem
	int r; // rank
	char command; // func

	// 초기화
	init(&list);

	// input
	scanf("%d\n", &N);
	for (int i = 0; i < N; i++) {
		scanf("%c", &command);

		if (command == 'P') { // print
			//printf("Print: ");
			//printf("%c\n", command);
			print(&list);
		}
		else if (command == 'D') { // delete
			scanf("%d", &r);
			//printf("Delete: ");
			//printf("%c: %d\n", command, r);
			delete(&list, r);
		}
		else if (command == 'A') { // add
			scanf("%d", &r);
			scanf(" %c", &c);
			//printf("add: ");
			//printf("%c: %d: %c\n", command, r, c);
			add(&list, c, r);
		}

		else if (command == 'G') { // get
			scanf("%d", &r);
			//printf("get: ");
			//printf("%c: %d\n", command, r);
			get(&list, r);
		}
		getchar();
	}
	
	
}

/*
예제
5
A 1 S
A 2 t
A 3 r
A 3 a
P

9
A 1 D
A 2 a
A 3 y
D 1
P
G 3
A 1 S
P
G 3
*/

/*---- 함수구현 ----*/
Node* GenNode(char c) // 노드 동적으로 할당
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->elem = c;
	p->prev = p->next = NULL;
	return p;
}
void init(List* list)
{
	list->head = GenNode(NULL);
	list->tail = GenNode(NULL);
	list->head->next = list->tail;
	list->tail->prev = list->head;
	list->count = 0;
}
void add(List* list, char c, int r)
{
	if ((r < 1) || (r > list->count + 1)) {
		printf("invalid position\n");
		return;
	}
	Node* p = list->head;
	
	for (int i = 0; i < r; i++) {
		p = p->next;
	}
	Node* q = GenNode(c);
	q->next = p;
	q->prev = p->prev;
	p->prev->next = q;
	p->prev = q;
	list->count++;
}
void delete(List* list, int r)
{
	if ((r < 1) || (r >= list->count + 1)) {
		printf("invalid position\n");
		return;
	}
	Node* p = list->head;

	for (int i = 0; i < r; i++) {
		p = p->next;
	}
	p->prev->next = p->next;
	p->next->prev = p->prev;
	list->count--;
	free(p);
}
void get(List* list, int r)
{
	if ((r < 1) || (r >= list->count+1)) {
		printf("invalid position\n");
		return;
	}
	Node* p = list->head;
	for (int i = 0; i < r; i++) {
		p = p->next;
	}
	printf("%c", p->elem);
}
void print(List* list)
{
	Node* p = list->head->next;
	while (p != list->tail) {
		printf("%c", p->elem);
		p = p->next;
	}
	printf("\n");
}



// 구조체 이름 헷갈리지 않도록 listNode인지 linklist인지 확인!!
