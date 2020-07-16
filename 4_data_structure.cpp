#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
	int key;
	struct treeNode* left;
	struct treeNode* right;
} treeNode;

treeNode* insertNode(treeNode* p, int x)
{

	treeNode* newNode;
	if (p == NULL)
	{
		newNode = (treeNode*)malloc(sizeof(treeNode));
		newNode->key = x;
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}

	else if (x < p->key) p->right = insertNode(p->right, x);
	else if (x > p->key) p->left = insertNode(p->left, x);

	return p;
}

void deleteNode(treeNode* root, int key)
{

	treeNode* parent, * p, * succ_parent1, * succ_parent2;
	treeNode* child;

	parent = NULL;
	p = root;

	while ((p != NULL) && (p->key != key))
	{
		parent = p;
		if (key < p->key) p = p->right; //key가 그 밑 key보다 작으면 p는 오른쪽으로
		else p = p->left; //크면 왼쪽으로
	}

	if (p == NULL) //삭제 할 노드 없는 경우
	{
		return;
	}

	//삭제할 노드가 단말 노드일 경우
	if ((p->right == NULL) && (p->left == NULL))
	{
		if (parent != NULL)
		{
			if (parent->right == p) parent->right = NULL;
			else parent->left = NULL;
		}
		else root = NULL;
	}

	//삭제할 노드가 자식 노드를 한 개 가진 경우
	else if ((p->right == NULL) || (p->left == NULL))
	{
		if (p->right != NULL)	child = p->right;
		else child = p->left;

		if (parent != NULL)
		{
			if (parent->right == p) parent->right = child;
			else parent->left = child;
		}
		else root = child;
	}

	//삭제할 노드가 자식 노드 두개 가진 경우
	else
	{

		succ_parent1 = p;
		succ_parent2 = p;

		treeNode* succ1 = p->left;
		treeNode* succ2 = p->right;


		while (succ1->right != NULL) // succ_parent->left에서 가장 작은 값 succ1
		{
			succ_parent1 = succ1;
			succ1 = succ1->right;
		}


		while (succ2->left != NULL) // succ_parent->right 에서 가장 큰 값 succ2
		{
			succ_parent2 = succ2;
			succ2 = succ2->left;
		}

		if ((succ1->key) - (p->key) < (p->key) - (succ2->key))
		{
			if (succ_parent1->left == succ1) succ_parent1->left = succ1->left;
			else
				succ_parent1->left = succ1->right;
			p->key = succ1->key;
			p = succ1;
		}
		else if ((succ1->key) - (p->key) == (p->key) - (succ2->key))
		{
			if (succ_parent1->left == succ1) succ_parent1->left = succ1->left;
			else
				succ_parent1->left = succ1->right;
			p->key = succ1->key;
			p = succ1;
		}
		else
		{
			if (succ_parent2->right == succ2) succ_parent2->right = succ2->right;
			else
				succ_parent2->right = succ2->left;
			p->key = succ2->key;
			p = succ2;
		}


	} //else

	free(p);

}

void searchBST(FILE* fp_output, treeNode* root, int x)
{
	treeNode* p;
	p = root;

	while (p != NULL)
	{
		if (x < p->key)
		{
			fprintf(fp_output, "%d ", p->key);
			p = p->right;//key값이 더 크면 오른쪽


		}
		else if (x == p->key)
		{
			fprintf(fp_output, "%d ", p->key);
			fprintf(fp_output, "\nYes\n");
			break;
		}
		else
		{
			fprintf(fp_output, "%d ", p->key);
			p = p->left; //key값이 더 작으면 왼쪽


		}
	}
	if (p == NULL)
		fprintf(fp_output, "\nNo\n");


}


//key를 루트 노드로 하여 왼쪽 서브트리와 오른쪽 서브트리 연결
treeNode* makeRootNode(int key, treeNode* leftNode, treeNode* rightNode)
{
	treeNode* root = (treeNode*)malloc(sizeof(treeNode));
	root->key = key;
	root->left = leftNode;
	root->right = rightNode;
	return root;
}

void preorder(FILE* fp_output, treeNode* root) //이진 트리 전위 순회 연산
{

	if (root)
	{
		fprintf(fp_output, "%d ", root->key);
		preorder(fp_output, root->left);
		preorder(fp_output, root->right);
	}
}



int main()
{
	FILE* fp_output = fopen("hw4.out", "w");
	FILE* fp_input = fopen("hw4.inp", "r");

	treeNode* p = NULL;
	int x;
	char y = 'a';

	fscanf(fp_input, "%d", &x);
	p = insertNode(p, x);

	while (y != '\n')
	{
		fscanf(fp_input, "%d%c", &x, &y); //첫번째 입력
		insertNode(p, x);
	}

	preorder(fp_output, p); // 트리 노드 출력

	y = 'b';

	while (y != '\n')
	{
		fscanf(fp_input, "%d%c", &x, &y); //두번째 입력
		deleteNode(p, x);
	}

	fprintf(fp_output, "\n");
	preorder(fp_output, p); //트리 노드 출력


	y = 'c';

	while (y != '\n')
	{
		fscanf(fp_input, "%d%c", &x, &y); //세번째 입력
	}
	fprintf(fp_output, "\n");

	searchBST(fp_output, p, x); // x탐색



	fprintf(fp_output, "*");


	fclose(fp_output);
	fclose(fp_input);

	return 0;
}