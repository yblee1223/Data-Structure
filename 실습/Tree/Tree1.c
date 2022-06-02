#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
typedef struct node {
	struct node* left;
	int data;
	struct node* right;
}Node;

// init func
Node* newRoot(int data, Node* left, Node* right);
Node* newLeaf(int data);
void print(Node* T[], int N); // print data, left.data, right.data


void main()
{
	int N;
	Node* T[9] = {0};
	
	T[4] = newLeaf(70);
	T[5] = newLeaf(90);
	T[7] = newLeaf(130);
	T[8] = newLeaf(80);

	T[6] = newRoot(120, T[7], T[8]);
	T[2] = newRoot(30, T[4], T[5]);
	T[3] = newRoot(50, NULL, T[6]);
	T[1] = newRoot(20, T[2], T[3]);

	// input
	scanf("%d", &N); // F_N

	// output
	if (1 <= N && N <= 8)
		print(T, N);
	else
		printf("-1");
}


/*
예제
2

3
*/

/* --- func --- */
Node* newRoot(int data, Node* left, Node* right)
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->data = data;
	p->left = left;
	p->right = right;
	return p;
}
Node* newLeaf(int data)
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->data = data;
	p->left = NULL;
	p->right = NULL;
	return p;
}
void print(Node* T[], int N)
{
	Node* node = T[N];
	printf(" %d", node->data);
	if (node->left)
		printf(" %d", node->left->data);
	if (node->right)
		printf(" %d", node->right->data);
}
