/*
已知二叉树的完全前序序列可以唯一确定一棵二叉树。现给出二叉树的完全前序序列，使用C或C++编写算法完成：
(1) 以二叉链表为存储结构，建立二叉树；
(2) 编写先序遍历算法，输出先序遍历序列；
(3) 编写中序遍历算法，输出中序遍历序列；
(4) 编写后序遍历算法，输出后序遍历序列；
(5) 编写层序遍历算法，输出层序遍历序列，要求按层输出，每层输出一行；
(6) 编写算法，计算并输出二叉树的叶子数；
(7) 编写算法，计算并输出二叉树的高度
*/
#include<iostream>
#include<cstdlib>
#include<stack>
using namespace std;
typedef struct BTNode{
	char data;
	struct BTNode* left;
	struct BTNode* right;
} *BinTree,BTNode;
typedef struct QNode{
	BinTree data;
	struct QNode* next;
} *Queue,QNode;

void CreatBinTree(BinTree& BT);
void PreTraversal(BinTree& BT);
void InTraversal(BinTree& BT);
void PosTraversal(BinTree& BT);
void LevelTraversal(BinTree& BT);
int GetLeaf(BinTree& BT);
int GetHigh(BinTree& Bt);
void CreatQueue(Queue& Q);
void Push(Queue& Q,BinTree& X);
BinTree Pop(Queue& Q);

int main(){
	int n;
	cin>>n;
	BinTree BT;
	CreatBinTree(BT);
	printf("preorder traversal:");
	PreTraversal(BT);
	printf("\n");
	printf("inorder traversal:");
	InTraversal(BT);
	printf("\n");
	printf("postorder traversal:");
	PosTraversal(BT);
	printf("\n");
	printf("level traversal:\n");
	LevelTraversal(BT);
	printf("%d\n",GetLeaf(BT));
	printf("%d",GetHigh(BT));
	return 0;
}

void CreatQueue(Queue& Q){
	Q=(Queue)malloc(sizeof(QNode));
	Q->next = NULL;
}
void Push(Queue& Q,BinTree& X){
	Queue q = Q;
	Queue p=(Queue)malloc(sizeof(QNode));
	p->data = X;
	while(q->next) q=q->next;
	p->next = q->next;
	q->next = p;
}
BinTree Pop(Queue& Q){
	if(!Q->next) return NULL;
	Queue temp=Q->next;
	BinTree p = temp->data;
	Q->next=temp->next;
	free(temp);
	return p;
}
void CreatBinTree(BinTree& BT){
	char a;
	cin>>a;
	if(a == '#') BT = NULL;
	else{
		BT = (BinTree)malloc(sizeof(BTNode));
		BT->data = a;
		CreatBinTree(BT->left);
		CreatBinTree(BT->right);
	}
}
void PreTraversal(BinTree& BT){
	if(BT!=NULL){
		printf("%c",BT->data);
		PreTraversal(BT->left);
		PreTraversal(BT->right);
	}
}
void InTraversal(BinTree& BT){
	if(BT){
		InTraversal(BT->left);
		printf("%c",BT->data);
		InTraversal(BT->right);
	}
}
void PosTraversal(BinTree& BT){
	if(BT){
		PosTraversal(BT->left);
		PosTraversal(BT->right);
		printf("%c",BT->data);
	}
}
void LevelTraversal(BinTree& BT){
	Queue Q;
	BinTree T;
	BinTree temp = NULL;	
	CreatQueue(Q);
	if(!BT){
		return;
	}
	Push(Q,BT);
	Push(Q,temp);
	while(Q->next){
		if(Q->next->next==NULL && Q->next->data==NULL) return;
		T = Pop(Q);
		if(!T) printf("\n");
		else {
			printf("%c",T->data);
			if(T->left) Push(Q,T->left);
			if(T->right) Push(Q,T->right);
			if(Q->next->data==NULL) Push(Q,temp);
		}
	}	
}
int GetHigh(BinTree& BT){
	int HL,HR,MaxH;
	if(BT){
		HL = GetHigh(BT->left);
		HR = GetHigh(BT->right);
		MaxH = HL>HR?HL:HR;
		return MaxH+1;
	}
	else return 0;
}
int GetLeaf(BinTree& BT) {
    if (BT == NULL) return 0;
    if (BT->left == NULL && BT->right == NULL) return 1;
    return GetLeaf(BT->left) + GetLeaf(BT->right);
}
