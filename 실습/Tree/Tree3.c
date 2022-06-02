#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
typedef struct node {
	struct node* left, *right;
	int data;
}TreeNode;

// init func
void init_tree(TreeNode* T);
TreeNode* makeNode(int d);
void append_node(TreeNode* T, int d, int l, int r);
void traversal(TreeNode* T, char* str);
void main()
{
	int node_num, traversal_num;
	int l, r, d;
	char str[100];
	TreeNode T;

	init_tree(&T);//root
	// append
	scanf("%d\n", &node_num);
	for (int i = 0; i < node_num; i++) {
		scanf("%d %d %d\n", &d, &l, &r);
		append_node(&T, d, l, r);
	}

	// traversal
	scanf("%d\n", &traversal_num);
	for (int i = 0; i < traversal_num; i++) {
		gets(str);
		traversal(&T, str);
		printf("\n");
	}
}


/*
ex)
9
5 3 9
3 8 15
8 0 2
2 0 0
15 0 0
9 7 10
7 12 0
12 0 0
10 0 0
3
RLL
LL
LR
*/
/* --- func --- */
void init_tree(TreeNode* T)
{
	T->data = -1;
	T->left = makeNode(0);
	T->right = makeNode(0);
}
TreeNode* makeNode(int d)
{
	TreeNode* T = calloc(1, sizeof(TreeNode));
	T->data = d;
	return T;
}
void append_node(TreeNode* T, int d, int l, int r)
{
	// root_node down and find data == d
	if (T == NULL) {
		return;
	}
	else if (T->data == -1) { // make root
		T->data = d;
		T->left = makeNode(l);
		T->right = makeNode(r);
	}
	else if (T->data == d) {
		T->left = makeNode(l);
		T->right = makeNode(r);
	}
	else {
		append_node(T->left, d, l, r);
		append_node(T->right, d, l, r);
	}
}
void traversal(TreeNode* T, char* str)
{
	printf(" %d", T->data);
	if (str[0] == 'R')
		traversal(T->right, str+1);
	else if (str[0] == 'L')
		traversal(T->left, str+1);
}
