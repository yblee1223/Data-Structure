#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct node {
	struct node* left, * right;
	int data, id;
}Tree;

// init func
Tree* NewNode(int data, int id);
void preorder(Tree* T);
void inorder(Tree* T);
void postorder(Tree* T);
void print(Tree* T);
void findNode(Tree* T, int order, int node_id);
void setlr(Tree* T, Tree* left, Tree* right);
void main()
{
	Tree T;
	Tree* l, * r;
	int order, node_id;
	scanf("%d %d", &order, &node_id);
	
	// input tree
	T.data = 20;
	T.id = 1;
	l = NewNode(30, 2);
	r = NewNode(50, 3);
	setlr(&T, l, r);

	l = NewNode(70, 4);
	r = NewNode(90, 5);
	setlr(T.left, l, r);

	l = NULL;
	r = NewNode(120, 6);
	setlr(T.right, l, r);

	l = NewNode(130, 7);
	r = NewNode(80, 8);
	setlr(T.right->right, l, r);

	// calc
	findNode(&T, order, node_id);
}
/*
Ex)
1 2
2 3
1 9
*/

/* --- func --- */
Tree* NewNode(int data, int id)
{
	Tree* node = (Tree*)calloc(1, sizeof(Tree));
	node->data = data;
	node->id = id;
	return node;
}

void findNode(Tree* T, int order, int node_id)
{
	if (node_id <= 0 || node_id > 8) {
		printf("-1");
		return;
	}
	else if (T == NULL)
		return;
	else if(T->id == node_id) {
		switch (order) {
		case 1:
			preorder(T);
			break;
		case 2:
			inorder(T);
			break;
		case 3:
			postorder(T);
			break;
		}
	}
	else {
		findNode(T->left, order, node_id); // node_id mismatch 1
		findNode(T->right, order, node_id); // node_id mismatch 2
	}
}

void setlr(Tree* T, Tree* left, Tree* right)
{
	T->left = left;
	T->right = right;
}

void inorder(Tree* T)
{
	if (!T)
		return;
	inorder(T->left);
	printf(" %d", T->data);
	inorder(T->right);
}
void postorder(Tree* T)
{
	if (!T)
		return;
	postorder(T->left);
	postorder(T->right);
	printf(" %d", T->data);
}
void preorder(Tree* T)
{
	if (!T)
		return;
	printf(" %d", T->data);
	preorder(T->left);
	preorder(T->right);
}
