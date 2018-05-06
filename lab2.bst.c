/*
*	Operating System Lab
*	    Lab2 (Synchronization)
*	    Student id : 
*	    Student name : 
*
*   lab2_lab2_tree.c :
*       - thread-safe lab2_tree code.
*       - coarse-grained, fine-grained lock code
*
*   Implement thread-safe lab2_tree for coarse-grained version and fine-grained version.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <string.h>

#include "lab2_sync_types.h"

pthread_mutex_t lock;



/*
 * TODO
 *  Implement funtction which traverse lab2_tree in in-order
 *  
 *  @param lab2_tree *tree  : lab2_tree to print in-order. 
 *  @return                 : status (success or fail)
 */

 // 중위순회 WorkHorse
void inorder(lab2_tree *tree, lab2_node *CurrentNode)
{
	if (CurrentNode != NULL)
	{
		inorder(tree, CurrentNode->LL);
		inorder(tree, CurrentNode->RL);
	}
}

int lab2_node_print_inorder(lab2_tree *tree) {
	inorder(tree, tree->root); // WorkHorse 순환호출
	return LAB2_SUCCESS;
}

/*
 * TODO
 *  Implement function which creates struct lab2_tree
 *  ( refer to the ./include/lab2_sync_types.h for structure lab2_tree )
 * 
 *  @return                 : lab2_tree which you created in this function.
 */
lab2_tree *lab2_tree_create() {
	pthread_mutex_lock(&lock);         //lock
	lab2_tree *tree = (lab2_tree *)malloc(sizeof(lab2_tree));
	tree->root = NULL;
	pthread_mutex_unlock(&lock);         //lock
	return tree;
}

/*
 * TODO
 *  Implement function which creates struct lab2_node
 *  ( refer to the ./include/lab2_sync_types.h for structure lab2_node )
 *
 *  @param int key          : lab2_tree node's key to creates
 *  @return                 : lab2_tree node which you created in this function.
 */
lab2_node * lab2_node_create(int key) {
	pthread_mutex_lock(&lock);         //lock
	lab2_node *newNode = (lab2_node *)malloc(sizeof(lab2_node));
	newNode->data = key;
	pthread_mutex_unlock(&lock);         //lock
	return newNode;
}

/* 
 * TODO
 *  Implement a function which insert nodes from the lab2_tree. 
 *  
 *  @param lab2_tree *tree      : lab2_tree which you need to insert new node.
 *  @param lab2_node *new_node  : lab2_tree node which you need to insert. 
 *  @return                 : satus (success or fail)
 */
int lab2_node_insert(lab2_tree *tree, lab2_node *new1){
	lab2_node *p = tree->root;
	lab2_node *q = NULL; // p의 이전 노드를 가리킴

	while (p) { // 알맞는 위치를 찾아가기

		q = p;

		if (new1->data == (p->data)) // 동일 노드 없음
		{
			//printf("Already existed in this tree! \n");
			return LAB2_ERROR;
		}
		else if (new1->data>(p->data))
		{
			p = p->RL;
		}
		else
		{
			p = p->LL;
		}
	}

	if (!(tree->root)) { // 빈 트리의 경우 
		(tree->root) = new1;
	}
	else if (new1->data<(q->data)) {
		q->LL = new1; // 왼쪽 노드로 생성
	}
	else {
		q->RL = new1; // 오른쪽 노드로 생성
	}
	return LAB2_SUCCESS;
}

/* 
 * TODO
 *  Implement a function which insert nodes from the lab2_tree in fine-garined manner.
 *
 *  @param lab2_tree *tree      : lab2_tree which you need to insert new node in fine-grained manner.
 *  @param lab2_node *new_node  : lab2_tree node which you need to insert. 
 *  @return                     : status (success or fail)
 */
int lab2_node_insert_fg(lab2_tree *tree, lab2_node *new1){

	lab2_node *p = tree->root;
	lab2_node *q = NULL; // p의 이전 노드를 가리킴

	while (p) { // 알맞는 위치를 찾아가기

		q = p;

		if (new1->data == (p->data)) // 동일 노드 없음
		{
			//printf("Already existed in this tree! \n");
			return LAB2_ERROR;
		}
		else if (new1->data>(p->data))
		{
			p = p->RL;
		}
		else
		{
			p = p->LL;
		}
	}

	pthread_mutex_lock(&lock);         //lock
	if (!(tree->root)) { // 빈 트리의 경우 
		(tree->root) = new1;
	}
	else if (new1->data<(q->data)) {
		q->LL = new1; // 왼쪽 노드로 생성
	}

	else {
		q->RL = new1; // 오른쪽 노드로 생성
	}

	pthread_mutex_unlock(&lock);  //unlock
	return LAB2_SUCCESS;
}

/* 
 * TODO
 *  Implement a function which insert nodes from the lab2_tree in coarse-garined manner.
 *
 *  @param lab2_tree *tree      : lab2_tree which you need to insert new node in coarse-grained manner.
 *  @param lab2_node *new_node  : lab2_tree node which you need to insert. 
 *  @return                     : status (success or fail)
 */
int lab2_node_insert_cg(lab2_tree *tree, lab2_node *new1){
	pthread_mutex_lock(&lock);         //lock
	lab2_node *p = tree->root;
	lab2_node *q = NULL; // p의 이전 노드를 가리킴

	while (p) { // 알맞는 위치를 찾아가기

		q = p;

		if (new1->data == (p->data)) // 동일 노드 없음
		{
			//printf("Already existed in this tree! \n");
			
			pthread_mutex_unlock(&lock);  //unlock
			return LAB2_ERROR;
		}
		else if (new1->data>(p->data))
		{
			p = p->RL;
		}
		else
		{
			p = p->LL;
		}
	}

	if (!(tree->root)) { // 빈 트리의 경우 
		(tree->root) = new1;
	}
	else if (new1->data<(q->data)) {
		q->LL = new1; // 왼쪽 노드로 생성
	}
	else {
		q->RL = new1; // 오른쪽 노드로 생성
	}

	pthread_mutex_unlock(&lock);  //unlock
	return LAB2_SUCCESS;
}

/* 
 * TODO
 *  Implement a function which remove nodes from the lab2_tree.
 *
 *  @param lab2_tree *tree  : lab2_tree tha you need to remove node from lab2_tree which contains key.
 *  @param int key          : key value that you want to delete. 
 *  @return                 : status (success or fail)
 */
int lab2_node_remove(lab2_tree *tree, int x) {
	lab2_node *p = tree->root;
	lab2_node *q = NULL; // p의 이전 노드를 가리킴
	lab2_node *t; // p의 이전 노드를 가리킴

	while (1) // 알맞은 위치 찾기
	{
		if (x == (p->data))
			break; // 찾았으면 멈추기

		else if (x < (p->data))
		{
			if (p->LL == NULL)
			{ // 존재하지 않을 경우
				return LAB2_ERROR;
			}
			// 왼쪽 노드로 이동
			q = p;
			p = p->LL;
		}

		else// if (x > (p->data))
		{
			if (p->RL == NULL)
			{ // 존재하지 않을 경우
				return LAB2_ERROR;
			}
			// 오른쪽 노드로 이동
			q = p;
			p = p->RL;
		}
	}

	if ((p->LL == NULL) && (p->RL == NULL)) // 단일 노드의 삭제
	{
		if (p == tree->root)
		{ // 유일하게 남은 노드를 삭제하려고 할 때
			tree->root = NULL;
			return LAB2_SUCCESS;
		}

		if (p == q->LL)
			q->LL = NULL;
		else
			q->RL = NULL;
		//delete p;
	}

	else if ((p->LL != NULL) && (p->RL == NULL)) // 왼쪽 노드를 가지고 있는 노드를 삭제하려고 할 때
	{
		if (p == tree->root)
			tree->root = p->LL; // root 노드의 삭제의 경우
		else
		{
			if (p == q->LL)
				q->LL = p->LL;
			else
				q->RL = p->LL;
		}
		//delete p;
	}

	else if ((p->LL == NULL) && (p->RL != NULL)) // 오른쪽 노드를 가지고 있는 노드를 삭제하려고 할 때
	{
		if (p == tree->root)
			tree->root = p->RL; // root 노드의 삭제의 경우
		else
		{
			if (p == q->LL)
				q->LL = p->RL;
			else
				q->RL = p->RL;
		}
		//delete p;
	}

	else if ((p->LL != NULL) && (p->RL != NULL)) // 2개의 노드를 가지고 있는 노드를 삭제하려고 할 때
	{										     // 왼쪽 서브트리 중 Data의 크기가 가장 느 노드로 대체
		q = p; // q는 삭제하려는 노드
		p = p->LL; // p는 왼쪽 서브트리 중 가장 큰 노드
		t = p; // t는 p의 이전 노드 

		while (1) // 알맞은 위치 찾기
		{
			if (p->RL == NULL)
				break; // 찾았으면 멈추기
			else
			{ // 가장 큰 값을 찾기 때문에 오른쪽 노드로만 이동
				t = p;
				p = p->RL;
			}
		}

		q->data = p->data; // 삭제하려는 노드에 왼쪽 서브트리 중 가장 큰 노드의 Data를 넣음

		if (t != p) // 삭제하려는 노드로부터 거리가 1 초과인 경우
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
	return LAB2_SUCCESS;
}

/* 
 * TODO
 *  Implement a function which remove nodes from the lab2_tree in fine-grained manner.
 *
 *  @param lab2_tree *tree  : lab2_tree tha you need to remove node in fine-grained manner from lab2_tree which contains key.
 *  @param int key          : key value that you want to delete. 
 *  @return                 : status (success or fail)
 */
int lab2_node_remove_fg(lab2_tree *tree, int x) {

	lab2_node *p = tree->root;
	lab2_node *q = NULL; // p의 이전 노드를 가리킴
	lab2_node *t; // p의 이전 노드를 가리킴
	while (1) // 알맞은 위치 찾기
	{
		if (x == (p->data))
			break; // 찾았으면 멈추기

		else if (x < (p->data))
		{
			if (p->LL == NULL)
			{ // 존재하지 않을 경우
				//printf("Not existed Node! \n");
				return LAB2_ERROR;
			}
			// 왼쪽 노드로 이동
			q = p;
			p = p->LL;
		}

		else// if (x > (p->data))
		{
			if (p->RL == NULL)
			{ // 존재하지 않을 경우
				//printf("Not existed Node! \n");
				return LAB2_ERROR;
			}
			// 오른쪽 노드로 이동
			q = p;
			p = p->RL;
		}
	}

	pthread_mutex_lock(&lock);         //lock

	if ((p->LL == NULL) && (p->RL == NULL)) // 단일 노드의 삭제
	{
		if (p == tree->root)
		{ // 유일하게 남은 노드를 삭제하려고 할 때
			//printf("This node is unique. Can't delete! \n");
			tree->root = NULL;
			pthread_mutex_unlock(&lock);  //unlock
			return LAB2_SUCCESS;
		}

		if (p == q->LL)
			q->LL = NULL;
		else
			q->RL = NULL;
		//delete p;
	}

	else if ((p->LL != NULL) && (p->RL == NULL)) // 왼쪽 노드를 가지고 있는 노드를 삭제하려고 할 때
	{
		if (p == tree->root)
			tree->root = p->LL; // root 노드의 삭제의 경우
		else
		{
			if (p == q->LL)
				q->LL = p->LL;
			else
				q->RL = p->LL;
		}
		//delete p;
	}

	else if ((p->LL == NULL) && (p->RL != NULL)) // 오른쪽 노드를 가지고 있는 노드를 삭제하려고 할 때
	{
		if (p == tree->root)
			tree->root = p->RL; // root 노드의 삭제의 경우
		else
		{
			if (p == q->LL)
				q->LL = p->RL;
			else
				q->RL = p->RL;
		}
		//delete p;
	}

	else if ((p->LL != NULL) && (p->RL != NULL)) // 2개의 노드를 가지고 있는 노드를 삭제하려고 할 때
	{										     // 왼쪽 서브트리 중 Data의 크기가 가장 느 노드로 대체
		q = p; // q는 삭제하려는 노드
		p = p->LL; // p는 왼쪽 서브트리 중 가장 큰 노드
		t = p; // t는 p의 이전 노드 

		while (1) // 알맞은 위치 찾기
		{
			if (p->RL == NULL)
				break; // 찾았으면 멈추기
			else
			{ // 가장 큰 값을 찾기 때문에 오른쪽 노드로만 이동
				t = p;
				p = p->RL;
			}
		}

		q->data = p->data; // 삭제하려는 노드에 왼쪽 서브트리 중 가장 큰 노드의 Data를 넣음

		if (t != p) // 삭제하려는 노드로부터 거리가 1 초과인 경우
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
	pthread_mutex_unlock(&lock);    //unlock
	return LAB2_SUCCESS;
}


/* 
 * TODO
 *  Implement a function which remove nodes from the lab2_tree in coarse-grained manner.
 *
 *  @param lab2_tree *tree  : lab2_tree tha you need to remove node in coarse-grained manner from lab2_tree which contains key.
 *  @param int key          : key value that you want to delete. 
 *  @return                 : status (success or fail)
 */
int lab2_node_remove_cg(lab2_tree *tree, int x) {

	pthread_mutex_lock(&lock); // lock

	lab2_node *p = tree->root;
	lab2_node *q = NULL; // p의 이전 노드를 가리킴
	lab2_node *t; // p의 이전 노드를 가리킴

	while (1) // 알맞은 위치 찾기
	{
		if (x == (p->data))
			break; // 찾았으면 멈추기

		else if (x < (p->data))
		{
			if (p->LL == NULL)
			{ // 존재하지 않을 경우
				//printf("Not existed Node! \n");
				pthread_mutex_unlock(&lock);     //unlock
				return LAB2_ERROR;
			}
			// 왼쪽 노드로 이동
			q = p;
			p = p->LL;
		}

		else// if (x > (p->data))
		{
			if (p->RL == NULL)
			{ // 존재하지 않을 경우
				//printf("Not existed Node! \n");
				pthread_mutex_unlock(&lock);     //unlock
				return LAB2_ERROR;
			}
			// 오른쪽 노드로 이동
			q = p;
			p = p->RL;
		}
	}

	if ((p->LL == NULL) && (p->RL == NULL)) // 단일 노드의 삭제
	{

		if (p == tree->root)
		{ // 유일하게 남은 노드를 삭제하려고 할 때
			//printf("This node is unique. Can't delete! \n");
			//return LAB2_ERROR;
			tree->root = NULL;
			pthread_mutex_unlock(&lock);     //unlock
			return LAB2_SUCCESS;
		}

		if (p == q->LL)
			q->LL = NULL;
		else
			q->RL = NULL;
		//delete p;
	}

	else if ((p->LL != NULL) && (p->RL == NULL)) // 왼쪽 노드를 가지고 있는 노드를 삭제하려고 할 때
	{
		if (p == tree->root)
			tree->root = p->LL; // root 노드의 삭제의 경우
		else
		{
			if (p == q->LL)
				q->LL = p->LL;
			else
				q->RL = p->LL;
		}
		//delete p;
	}

	else if ((p->LL == NULL) && (p->RL != NULL)) // 오른쪽 노드를 가지고 있는 노드를 삭제하려고 할 때
	{
		if (p == tree->root)
			tree->root = p->RL; // root 노드의 삭제의 경우
		else
		{
			if (p == q->LL)
				q->LL = p->RL;
			else
				q->RL = p->RL;
		}
		//delete p;
	}

	else if ((p->LL != NULL) && (p->RL != NULL)) // 2개의 노드를 가지고 있는 노드를 삭제하려고 할 때
	{										     // 왼쪽 서브트리 중 Data의 크기가 가장 느 노드로 대체
		q = p; // q는 삭제하려는 노드
		p = p->LL; // p는 왼쪽 서브트리 중 가장 큰 노드
		t = p; // t는 p의 이전 노드 

		while (1) // 알맞은 위치 찾기
		{
			if (p->RL == NULL)
				break; // 찾았으면 멈추기
			else
			{ // 가장 큰 값을 찾기 때문에 오른쪽 노드로만 이동
				t = p;
				p = p->RL;
			}
		}

		q->data = p->data; // 삭제하려는 노드에 왼쪽 서브트리 중 가장 큰 노드의 Data를 넣음

		if (t != p) // 삭제하려는 노드로부터 거리가 1 초과인 경우
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

	pthread_mutex_unlock(&lock);     //unlock
	return LAB2_SUCCESS;
}


/*
 * TODO
 *  Implement function which delete struct lab2_tree
 *  ( refer to the ./include/lab2_sync_types.h for structure lab2_node )
 *
 *  @param lab2_tree *tree  : lab2_tree which you want to delete. 
 *  @return                 : status(success or fail)
 */
void lab2_tree_delete(lab2_tree *tree) {
	pthread_mutex_lock(&lock);         //lock
	free(tree);
	pthread_mutex_unlock(&lock);         //unlock
}

/*
 * TODO
 *  Implement function which delete struct lab2_node
 *  ( refer to the ./include/lab2_sync_types.h for structure lab2_node )
 *
 *  @param lab2_tree *tree  : lab2_tree node which you want to remove. 
 *  @return                 : status(success or fail)
 */
void lab2_node_delete(lab2_node *node) {
	pthread_mutex_lock(&lock);         //lock
	free(node);
	pthread_mutex_unlock(&lock);         //unlock
}
