#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 구조체 전방 선언
typedef struct _BSTNode BSTNode;
typedef struct _BST BST;

// BSTNode구조체 선언
typedef struct _BSTNode{

	int data;
	BSTNode *RL;
	BSTNode *LL;

}BSTNode;

// BST구조체 선언
typedef struct _BST{

	BSTNode R;
	BSTNode *root;
}BST;

// BSTNode구조체 초기화
void InitNode(BSTNode *Node, int element)
{
	Node->data = element;
	Node->LL = NULL;
	Node->RL = NULL;
}

// BST구조체 초기화
void InitBST(BST *bst, int x)
{
	InitNode(&(bst->R), x);
	bst->root = &(bst->R);
}

// 트리에 노드 삽입
bool insert(BST *bst)
{
	BSTNode *p = bst->root;
	BSTNode *q = NULL; // p전의 노드를 가리킴
	BSTNode *new1 = malloc(sizeof(BSTNode));

	int x;

	printf("Enter the num : ");
	scanf("%d",&x);
	
	InitNode(new1, x);

	while(p){ // 알맞는 위치를 찾아가기
		
		q = p;

		if(x==(p->data)) // 동일 노드 없음
		{
			printf("Already existed in this tree! \n");
			return false;
		}
		else if (x>(p->data))
		{
			p=p->RL;
		}	
		else
		{
			p=p->LL;
		}
	}	

	if(!(bst->root)){ // 빈 트리의 경우 
		(bst->root) = new1;
	}
	else if(x<(q->data)){
		q->LL = new1; // 왼쪽 노드로 생성
	}
	else{
		q->RL = new1; // 오른쪽 노드로 생성
	}

	return true;
}

bool delete(BST *bst)
{
	BSTNode *p = bst->root;
	BSTNode *q = NULL;
	BSTNode *t;
	int x;

	printf("Enter the delete num : ");
	scanf("%d",&x);

	while(1)
	{
		if(x==(p->data))
			break;

		else if (x < (p->data))
		{
			if(p->LL == NULL)
			{
				printf("Not existed Node! \n");
				return false;
			}
			q = p;
			p = p->LL;
		}

		else// if (x > (p->data))
		{
			if(p->RL == NULL)
			{
				printf("Not existed Node! \n");
				return false;
			}
			q = p;
			p = p->RL;
		}
	}

	if( (p->LL == NULL) && (p->RL == NULL) )
	{
		if(p == bst->root)
		{
			printf("This node is unique. Can't delete! \n");
			return false;
		}

		if(p == q->LL)
			q->LL = NULL;
		else
			q->RL = NULL;
		//delete p;
	}

	else if( (p->LL != NULL) && (p->RL == NULL) )
	{
		if(p == bst->root)
			bst->root = p->LL;
		else
		{
			if(p == q->LL)
				q->LL = p->LL;
			else
				q->RL = p->LL;
		}
		//delete p;
	}

	else if( (p->LL == NULL) && (p->RL != NULL) )
	{
		if(p == bst->root)
			bst->root = p->RL;
		else
		{
			if(p == q->LL)
				q->LL = p->RL;
			else
				q->RL = p->RL;
		}
		//delete p;
	}

	else if( (p->LL != NULL) && (p->RL != NULL))
	{
		q=p;
		p=p->LL;
		t=p;

		while(1)
		{
			if(p->RL == NULL)
				break;
			else
			{
				t=p;
				p=p->RL;
			}
		}

		q->data = p->data;

		if( t != p )
		{
			if (p->LL != NULL)
				t->RL = p->LL;
			else
				t->RL = NULL;
			//delete p;
		}

		else
		{
			q->LL = NULL;
			//delete p;
		}
	}
	return true;
}

void inorder(BST *bst, BSTNode *CurrentNode)
{
	if(CurrentNode != NULL)
	{
		inorder(bst, CurrentNode->LL);
		if(CurrentNode->data!=bst->root->data)
			printf("%d ", CurrentNode->data);
		else
			printf("<%d(root)> ", CurrentNode->data);
		inorder(bst, CurrentNode->RL);
	}
}

void _inorder(BST *bst)
{
	printf("Result of inorder : ");
	inorder(bst, bst->root);
	printf("\n");
}

bool search(BST *bst)
{
	BSTNode *p = bst->root;
	BSTNode *q = NULL;
	int x;

	printf("Enter the search num : ");
	scanf("%d",&x);

	while(1)
	{
		if(x==(p->data))
			break;

		else if (x < (p->data))
		{
			if(p->LL == NULL)
			{
				printf("Not existed Node! \n");
				return false;
			}
			q = p;
			p = p->LL;
		}

		else// if (x > (p->data))
		{
			if(p->RL == NULL)
			{
				printf("Not existed Node! \n");
				return false;
			}
			q = p;
			p = p->RL;
		}
	}
		if(q == NULL)
		{
			if(x == (p->data))
			{
				printf("%d is a root node! \n", x);
				if(p->LL != NULL)
					printf("left chile's data : %d \n", p->LL->data);
				if(p->RL != NULL)
					printf("right chile's data : %d \n", p->RL->data);
			}
		}

		else
		{
			if(x == (p->data))
			{
				printf("%d is a chile of %d \n", x, q->data);
				if(p->LL != NULL)
					printf("left chile's data : %d \n", p->LL->data);
				if(p->RL != NULL)
					printf("right chile's data : %d \n", p->RL->data);
				if((p->LL == NULL) && (p->RL ==NULL))
					printf("No chile! \n");
			}

			else if( x < (p->data))
				p = p->LL;
			else
				p = p->RL;
		}
	return true;
}

int main()
{
	BST a;
	int num, i;

	printf("Enter the First Num : ");
	scanf("%d",&num);

	InitBST(&a, num);

	for(i=0; i<10; i++)
	{
		printf("Insert! <%d/10>\n",i+1);
		if(insert(&a)==false)
			i--;
	}

	_inorder(&a);

	for(i=0; i<2; i++)
	{
		printf("Search! <%d/2>\n", i+1);
		if(search(&a)==false)
			i--;
	}

	for(i=0; i<2; i++)
	{
		printf("Delete! <%d/2>\n", i+1);
		if(delete(&a)==false)
			i--;
	}

	_inorder(&a);

	for(i=0; i<4; i++)
	{
		printf("Insert! <%d/4>\n",i+1);
		if(insert(&a)==false)
			i--;
	}

	_inorder(&a);

	for(i=0; i<2; i++)
	{
		printf("Search! <%d/2>\n", i+1);
		if(search(&a)==false)
			i--;
	}

	for(i=0; i<2; i++)
	{
		printf("Delete! <%d/2>\n", i+1);
		if(delete(&a)==false)
			i--;
	}

	_inorder(&a);

	return 0;
}
