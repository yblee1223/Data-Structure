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
void findNode(Tree* T, int node_id);
void setlr(Tree* T, Tree* left, Tree* right);
int calc_dir_size(Tree* T);
void main()
{
	Tree T;
	Tree* l, * r;
	int node_id;
	scanf("%d", &node_id);
	
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
	findNode(&T, node_id);
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

void findNode(Tree* T, int node_id)
{
	if (node_id <= 0 || node_id > 8) {
		printf("-1");
		return;
	}
	else if (T == NULL)
		return;
	else if(T->id == node_id) {
		printf("%d", calc_dir_size(T));
	}
	else {
		findNode(T->left, node_id); // node_id mismatch 1
		findNode(T->right, node_id); // node_id mismatch 2
	}
}

void setlr(Tree* T, Tree* left, Tree* right)
{
	T->left = left;
	T->right = right;
}

int calc_dir_size(Tree* T)
{
	int left_size, right_size;
	if (T == NULL)
		return 0;
	left_size = calc_dir_size(T->left);
	right_size = calc_dir_size(T->right);
	return T->data + left_size + right_size;
}
