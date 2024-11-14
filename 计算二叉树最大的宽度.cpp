/*
����������Ԫ��Ϊ�����ַ��Ҹ�����ͬ��ȡֵ��ΧΪA~Z��a~z��
����������Ϊ�ա��������ݷ�Ϊ2�У���1��Ϊ��������ȫǰ�������ַ�(����#)��������2��Ϊ����������ȫǰ�����С�
���磬���������������Ϊ��ABD##FE###CG#H##I##������#����Ϊ�յ�λ�á�
*/
#include<iostream>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
typedef struct BTNode{
	struct BTNode* left,*right;
	char data;
} *BiTree,BTNode;

typedef struct Node{
	BiTree data;
	struct Node* next;
} *PtrToNode,Node;

typedef struct QNode{
	PtrToNode data;
	PtrToNode front;
	PtrToNode rear;
	int size;	
} *Queue,QNode;

Queue InitQueue();
void Add(Queue& Q,BiTree& X);
BiTree Delete(Queue& Q);
//BiTree InitTree();
BiTree CreatTree();
void GetWidth(BiTree& BT);

int main(){
	int n;
	scanf("%d",&n);
	BiTree BT = CreatTree();
	GetWidth(BT);
	return 0;
}
Queue InitQueue(){
	Queue Q=(Queue)malloc(sizeof(QNode));
	Q->data = (PtrToNode)malloc(sizeof(Node));
	Q->data->next = NULL;
	Q->front = Q->data;
	Q->rear = Q->data;
	Q->size = 0;
	return Q;
}
void Add(Queue& Q,BiTree& X){
	PtrToNode temp=(PtrToNode)malloc(sizeof(Node));
	temp->data = X;
	temp->next = Q->rear->next;
	Q->rear->next = temp;
	Q->rear = temp;
	Q->size++;
}
BiTree Delete(Queue& Q){
	if(Q->front == Q->rear) return NULL;
	PtrToNode temp=Q->front->next;
	BiTree data = temp->data;
	Q->front->next = temp->next;
	free(temp);
	Q->size--;
	return data;
}

BiTree InitTree(){
	BiTree BT = NULL;
	return BT;
}
BiTree CreatTree(){
	char a;
	cin>>a;
	if(a == '#') return NULL;
	else{
		BiTree BT=(BiTree)malloc(sizeof(BTNode));
		BT->data = a;
		BT->left = CreatTree();
		BT->right = CreatTree();
		return BT;
	}
	
}
void GetWidth(BiTree& BT){
	if(!BT) return;
	Queue Q=InitQueue();
	BiTree flag = NULL;
	vector<int> wid;
	Add(Q,BT);
	Add(Q,flag);
	int width=0;
	while(Q->size){
		BiTree T=Delete(Q);
		if(!T){
			wid.push_back(width);
			width=0;
		}
		else{
			if(T->left) Add(Q,T->left);
			if(T->right) Add(Q,T->right);
			if(Q->front->next->data==NULL) Add(Q,flag);
			width++;		
		}
	}
	//cout<<wid[0]<<wid[1]<<endl;
	cout<<*max_element(wid.begin(),wid.end());
}
