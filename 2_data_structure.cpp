
#include <stdio.h>
#include <stdlib.h>


typedef struct ListNode {
	float coef;
	int expo;
	struct ListNode* Link;
}ListNode;

typedef struct ListHead {
	ListNode* head;
}ListHead;


ListHead* createLinkedList(void)
{
	ListHead* L;
	L = (ListHead*)malloc(sizeof(ListHead));
	L->head = NULL;
	return L;
} //공백 다항식 리스트

void appendTerm(ListHead* L, float coef, int expo)
{
	ListNode* newNode;
	ListNode* p;
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->coef = coef;
	newNode->expo = expo;
	newNode->Link = NULL;

	if (L->head == NULL)
	{
		L->head = newNode;
		return;
	}
	else {
		p = L->head;
		while (p->Link != NULL)
		{
			p = p->Link;
		}
		p->Link = newNode;
	}

}


//I 가 들어올때 insertMiddleNode함수 호출 해주기
void insertMiddleNode(FILE* input_fp, ListHead* L) //노드 중간 삽입
{

	ListNode* temp1 = L->head;
	ListNode* temp2 = L->head->Link;

	float coef;
	int expo;

	fscanf(input_fp, "%f %d", &coef, &expo);

	ListNode* newNode;
	newNode = (ListNode*)malloc(sizeof(ListNode));

	newNode->coef = coef;
	newNode->expo = expo;

	if (newNode->expo > L->head->expo) // 입력받은 다항식 차수가 더 클 경우
	{
		newNode->Link = L->head;
		L->head = newNode;
	}
	else if (newNode->expo == L->head->expo)
	{
		return;
	}
	else
	{
		while (1)
		{
			if (temp2 == NULL)
			{
				newNode->Link = NULL;
				temp1->Link = newNode;
				break;
			}
			else
			{
				if (newNode->expo > temp2->expo)
				{
					newNode->Link = temp2;
					temp1->Link = newNode;
					break;
				}
				else if (newNode->expo == temp2->expo)
				{
					return;
				}
				else
				{
					temp1 = temp1->Link;
					temp2 = temp2->Link;
				}
			}


		}
	}

}

void deleteNode(ListHead* L, int expo)
{

	ListNode* p = L->head;
	ListNode* pre = L->head;

	while (p != NULL)
	{
		if (p->expo == expo)
		{
			if (p == L->head) {
				L->head = p->Link;
				free(p);
				break;
			}
			pre->Link = p->Link;
			free(p);
			break;
		}
		else {
			if (p != L->head) {
				pre = pre->Link;
			}
			p = p->Link;
		}
	}
}
void addPoly(ListHead* A, ListHead* B, ListHead* C)
{
	ListNode* pA = A->head;
	ListNode* pB = B->head;
	float sum;

	while (pA != NULL && pB != NULL)
	{
		if (pA->expo == pB->expo)
		{
			sum = pA->coef + pB->coef;
			appendTerm(C, sum, pA->expo);
			pA = pA->Link; pB = pB->Link;
		}
		else if (pA->expo > pB->expo)
		{
			appendTerm(C, pA->coef, pA->expo);
			pA = pA->Link;
		}
		else
		{
			appendTerm(C, pB->coef, pB->expo);
			pB = pB->Link;
		}

	}
	for (; pA != NULL; pA = pA->Link)
		appendTerm(C, pA->coef, pA->expo);

	for (; pB != NULL; pB = pB->Link)
		appendTerm(C, pB->coef, pB->expo);

}

void printPoly(FILE* output_fp, ListHead* L)
{
	ListNode* p = L->head;
	for (; p != NULL; p = p->Link)
	{
		fprintf(output_fp, "%0.0f %d ", p->coef, p->expo);
	}
	fprintf(output_fp, "\n");
}

int main()
{
	FILE* output_fp = fopen("hw2.out", "wt");
	FILE* input_fp = fopen("hw2.inp", "rt");
	char a;
	ListHead* A, * B, * C;
	float coef;
	int expo;
	char cnt = 'A';
	A = createLinkedList();
	B = createLinkedList();
	C = createLinkedList();

	while (cnt != '\n') {
		fscanf(input_fp, "%f %d", &coef, &expo);
		appendTerm(A, coef, expo);
		fscanf(input_fp, "%c", &cnt);
	}
	cnt = 'A';
	fscanf(input_fp, "%c", &a);

	switch (a)
	{
	case 'I':
		while (cnt != '\n') {
			insertMiddleNode(input_fp, A);
			fscanf(input_fp, "%c", &cnt);
		}
		printPoly(output_fp, A);
		break;
	case 'D':
		while (cnt != '\n') {
			fscanf(input_fp, "%d", &expo);
			deleteNode(A, expo);
			fscanf(input_fp, "%c", &cnt);
		}
		printPoly(output_fp, A);
	}
	cnt = 'A';
	while (cnt != '\n') {
		fscanf(input_fp, "%f %d", &coef, &expo);
		appendTerm(B, coef, expo);
		fscanf(input_fp, "%c", &cnt);
	}
	cnt = 'A';
	fscanf(input_fp, "%c", &a);

	switch (a)
	{
	case 'I':
		while (cnt != '\n') {
			insertMiddleNode(input_fp, B);
			fscanf(input_fp, "%c", &cnt);
		}
		printPoly(output_fp, B);
		break;
	case 'D':
		while (cnt != '\n') {
			fscanf(input_fp, "%d", &expo);
			deleteNode(B, expo);
			fscanf(input_fp, "%c", &cnt);
		}
		printPoly(output_fp, B);
	}
	addPoly(A, B, C);
	printPoly(output_fp, C);

	fprintf(output_fp, "*");

	fclose(output_fp);
	fclose(input_fp);

	return 0;


}