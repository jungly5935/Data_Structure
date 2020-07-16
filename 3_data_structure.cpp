#include < stdio.h>
#include < stdlib.h>
#include < string.h>


typedef struct stackNode {
	char data;
	struct stackNode* link;
}stackNode;

stackNode* top;

int isEmpty()
{
	if (top == NULL) return 1;
	else return 0;
}

void push(char item)
{
	stackNode* temp = (stackNode*)malloc(sizeof(stackNode));

	temp->data = item;
	temp->link = top;
	top = temp;
}


void printStack(FILE* fp)

{
	stackNode* p = top;

	while (p) {
		fprintf(fp, "%c ", p->data);
		p = p->link;
	}

}

int main(void)
{
	FILE* fp = fopen("hw3.out", "wt");
	FILE* pf = fopen("hw3.inp", "rt");

	char item = 'A';



	while (item != '\n')
	{
		fscanf(pf, "%c", &item);

		if (item == '\n')
		{
			break;
		}
		push(item);


	}
	printStack(fp);


	fclose(fp);
	fclose(pf);

	return 0;

}

