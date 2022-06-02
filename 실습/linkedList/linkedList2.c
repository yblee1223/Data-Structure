#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef struct node {
    int coef;
    int exp;
    struct node* next;
}Node;
typedef struct list {
    int num;
    Node* head;
}List;

Node* GenNode(int coef, int exp);
void init(List* p);
Node* appendTerm(Node* p, int c, int e);
Node* addPoly(Node* x, Node* y);
void print(Node* head);

void main()
{
    List A;
    List B;
    List C;
    int n1, n2;
    Node* p = (Node*)malloc(sizeof(Node));

    // input A
    scanf("%d", &(A.num));
    init(&A);
    p = A.head;
    for (int i = 0; i < A.num; i++) {
        scanf("%d %d", &n1, &n2);
        p = appendTerm(p, n1, n2);
    }

    // input B
    scanf("%d", &(B.num));
    init(&B);
    p = B.head;
    for (int i = 0; i < B.num; i++) {
        scanf("%d %d", &n1, &n2);
        p = appendTerm(p, n1, n2);
    }

    // addPloy
    init(&C);
    C.head = addPoly(A.head, B.head);

    // print
    print(C.head);
    free(p);
}

/*
예제
2
2 7 3 0
3
-3 10 3 7 -3 0

2
2 7 3 0
3
-3 10 3 7 -3 0

*/

/* --- func --- */
Node* GenNode(int coef, int exp)
{
    Node* p = (Node*)malloc(sizeof(Node));
    p->coef = coef;
    p->exp = exp;
    p->next = NULL;
    return p;
}
void init(List* p)
{
    p->head = GenNode(0, 0);
}
Node* appendTerm(Node* p, int c, int e)
{
    Node* q = GenNode(c, e);
    q->next = NULL;
    p->next = q;
    return q;
}
Node* addPoly(Node* x, Node* y)
{
    int sum = 0;
    Node* result = GenNode(0, 0);
    Node* i = x->next;
    Node* j = y->next;
    Node* k = result;

    while ((i != NULL) && (j != NULL)) {
        if (i->exp > j->exp) {
            k = appendTerm(k, i->coef, i->exp);
            i = i->next;
        }
        else if (i->exp < j->exp) {
            k = appendTerm(k, j->coef, j->exp);
            j = j->next;
        }
        else {
            sum = i->coef + j->coef;
            if (sum != 0) {
                k = appendTerm(k, sum, i->exp);
            }
            i = i->next;
            j = j->next;
        }
    }
    while (i != NULL) {
        k = appendTerm(k, i->coef, i->exp);
        i = i->next;
    }
    while (j != NULL) {
        k = appendTerm(k, j->coef, j->exp);
        j = j->next;
    }
    free(i);
    free(j);
    return result;
}
void print(Node* head) {
    Node* p = head->next;
    while (p != NULL) {
        printf(" %d %d", p->coef, p->exp);
        p = p->next;
    }
    free(p);
}
