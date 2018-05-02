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
	BSTNode *q = NULL; // p의 이전 노드를 가리킴
	BSTNode *new1 = (BSTNode *) malloc(sizeof(BSTNode));
	
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

// 트리에 있는 노드 삭제
bool delete(BST *bst)
{
	BSTNode *p = bst->root;
	BSTNode *q = NULL; // p의 이전 노드를 가리킴
	BSTNode *t; // p의 이전 노드를 가리킴
	int x;

	printf("Enter the delete num : ");
	scanf("%d",&x);

	while(1) // 알맞은 위치 찾기
	{
		if(x==(p->data))
			break; // 찾았으면 멈추기

		else if (x < (p->data))
		{
			if(p->LL == NULL)
			{ // 존재하지 않을 경우
				printf("Not existed Node! \n");
				return false;
			}
			// 왼쪽 노드로 이동
			q = p;
			p = p->LL;
		}

		else// if (x > (p->data))
		{
			if(p->RL == NULL)
			{ // 존재하지 않을 경우
				printf("Not existed Node! \n");
				return false;
			}
			// 오른쪽 노드로 이동
			q = p;
			p = p->RL;
		}
	}

	if( (p->LL == NULL) && (p->RL == NULL) ) // 단일 노드의 삭제
	{
		if(p == bst->root)
		{ // 유일하게 남은 노드를 삭제하려고 할 때
			printf("This node is unique. Can't delete! \n");
			return false;
		}

		if(p == q->LL)
			q->LL = NULL;
		else
			q->RL = NULL;
		//delete p;
	}

	else if( (p->LL != NULL) && (p->RL == NULL) ) // 왼쪽 노드를 가지고 있는 노드를 삭제하려고 할 때
	{
		if(p == bst->root)
			bst->root = p->LL; // root 노드의 삭제의 경우
		else
		{
			if(p == q->LL)
				q->LL = p->LL;
			else
				q->RL = p->LL;
		}
		//delete p;
	}

	else if( (p->LL == NULL) && (p->RL != NULL) ) // 오른쪽 노드를 가지고 있는 노드를 삭제하려고 할 때
	{
		if(p == bst->root)
			bst->root = p->RL; // root 노드의 삭제의 경우
		else
		{
			if(p == q->LL)
				q->LL = p->RL;
			else
				q->RL = p->RL;
		}
		//delete p;
	}

	else if( (p->LL != NULL) && (p->RL != NULL)) // 2개의 노드를 가지고 있는 노드를 삭제하려고 할 때
	{										     // 왼쪽 서브트리 중 Data의 크기가 가장 느 노드로 대체
		q=p; // q는 삭제하려는 노드
		p=p->LL; // p는 왼쪽 서브트리 중 가장 큰 노드
		t=p; // t는 p의 이전 노드 

		while(1) // 알맞은 위치 찾기
		{
			if(p->RL == NULL)
				break; // 찾았으면 멈추기
			else
			{ // 가장 큰 값을 찾기 때문에 오른쪽 노드로만 이동
				t=p;
				p=p->RL;
			}
		}

		q->data = p->data; // 삭제하려는 노드에 왼쪽 서브트리 중 가장 큰 노드의 Data를 넣음

		if( t != p ) // 삭제하려는 노드로부터 거리가 1 초과인 경우
		{
			if (p->LL != NULL)
				t->RL = p->LL;
			else
				t->RL = NULL;
			//delete p;
		}

		else // 삭제하려는 노드로부터 거리가 1인 경우
		{
			q->LL = p->LL;
			//delete p;
		}
	}
	return true;
}

// 전위순회 WorkHorse
void preorder(BST *bst, BSTNode *CurrentNode)
{
	if(CurrentNode != NULL)
	{
		if(CurrentNode->data!=bst->root->data)
			printf("%d ", CurrentNode->data); // root 노드 아닐 경우
		else
			printf("<%d(root)> ", CurrentNode->data); // root 노드일 경우
		preorder(bst, CurrentNode->LL); 
		preorder(bst, CurrentNode->RL);
	}
}

// 전위순회 Driver
void _preorder(BST *bst)
{
	printf("Result of preorder : ");
	preorder(bst, bst->root); // WorkHorse 순환호출
	printf("\n");
}

// 후위순회 WorkHorse
void postorder(BST *bst, BSTNode *CurrentNode)
{
	if(CurrentNode != NULL)
	{
		postorder(bst, CurrentNode->LL);
		postorder(bst, CurrentNode->RL);
	
		if(CurrentNode->data!=bst->root->data)
			printf("%d ", CurrentNode->data); // root 노드 아닐 경우
		else
			printf("<%d(root)> ", CurrentNode->data); // root 노드일 경우
	}
}

// 후위순회  Driver
void _postorder(BST *bst)
{
	printf("Result of postorder : ");
	postorder(bst, bst->root); // WorkHorse 순환호출
	printf("\n");
}

// 중위순회 WorkHorse
void inorder(BST *bst, BSTNode *CurrentNode)
{
	if(CurrentNode != NULL)
	{
		inorder(bst, CurrentNode->LL);
		if(CurrentNode->data!=bst->root->data)
			printf("%d ", CurrentNode->data); // root 노드 아닐 경우
		else
			printf("<%d(root)> ", CurrentNode->data); // root 노드일 경우
		inorder(bst, CurrentNode->RL);
	}
}

// 중위순회 Driver
void _inorder(BST *bst)
{
	printf("Result of inorder : ");
	inorder(bst, bst->root); // WorkHorse 순환호출
	printf("\n");
}

// 데이터 값을 통한 트리 탐색 함수
bool search(BST *bst)
{
	BSTNode *p = bst->root;
	BSTNode *q = NULL; // p의 이전 노드를 가리킴
	int x;

	printf("Enter the search num : ");
	scanf("%d",&x);

	while(1) // 알맞은 위치 찾기
	{
		if(x==(p->data))
			break; // 찾았으면 멈추기

		else if (x < (p->data))
		{
			if(p->LL == NULL)
			{ // 존재하지 않을 경우
				printf("Not existed Node! \n");
				return false;
			}
			q = p;
			p = p->LL;
		}

		else// if (x > (p->data))
		{
			if(p->RL == NULL)
			{ // 존재하지 않을 경우
				printf("Not existed Node! \n");
				return false;
			}
			q = p;
			p = p->RL;
		}
	}
		if(q == NULL) // root 노드를 탐색했을 경우
		{ // 부모, 자식노드 알려줌
			if(x == (p->data))
			{
				printf("%d is a root node! \n", x);
				if(p->LL != NULL)
					printf("left chile's data : %d \n", p->LL->data);
				if(p->RL != NULL)
					printf("right chile's data : %d \n", p->RL->data);
			}
		}

		else // root노드 이외의 노드를 탐색했을 경우
		{ // 부모, 자식노드 알려줌
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

	// 10개 삽입
	for(i=0; i<10; i++)
	{
		printf("Insert! <%d/10>\n",i+1);
		if(insert(&a)==false) // 삽입에 실패했을 경우 횟수 감소 없애기
			i--;
	}

	// 중위순회
	_inorder(&a);

	// 2개 탐색
	for(i=0; i<2; i++)
	{
		printf("Search! <%d/2>\n", i+1);
		if(search(&a)==false) // 탐색에 실패했을 경우 횟수 감소 없애기
			i--;
	}

	// 2개 삭제
	for(i=0; i<2; i++)
	{
		printf("Delete! <%d/2>\n", i+1);
		if(delete(&a)==false){ // 삭제에 실패했을 경우 횟수 감소 없애기
			i--;
			continue;
		}
		_inorder(&a); // 중위순회
	}

	// 4개 삽입
	for(i=0; i<4; i++)
	{
		printf("Insert! <%d/4>\n",i+1);
		if(insert(&a)==false) // 삽입에 실패했을 경우 횟수 감소 없애기
			i--;
	}

	// 중위순회
	_inorder(&a);

	// 2개 탐색
	for(i=0; i<2; i++)
	{
		printf("Search! <%d/2>\n", i+1);
		if(search(&a)==false) // 탐색에 실패했을 경우 횟수 감소 없애기
			i--;
	}

	// 4개 삭제
	for(i=0; i<4; i++)
	{
		printf("Delete! <%d/4>\n", i+1);
		if(delete(&a)==false){ // 삭제에 실패했을 경우 횟수 감소 없애기
			i--;
			continue;
		}
		_inorder(&a); // 중위순회
	}

	// 전위순회
	_preorder(&a);

	// 후위순회
	_postorder(&a);

	return 0;
}
