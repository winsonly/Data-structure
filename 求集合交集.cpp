/*
����������A����������B�Ľ�����

�����ʽ:
���������У�

��һ����A��B��Ԫ�ظ���m��n��m,n <=100����

�ڶ����Ǽ���A��m��Ԫ�أ�

�������Ǽ���A��n��Ԫ�ء�

�����ʽ:
�������������Ԫ�أ�������A���ϳ��ֵ�˳����������һ���������û�пո񣩡�
������Ϊ�գ������NULL����

��������:
���������һ�����롣���磺

3 4
10 9 2
9 10 8 0
�������:
�����������Ӧ����������磺

10 9
*/
#include<iostream>
#include<cstdlib>
using namespace std;
typedef struct LNode{
	int* data;
	int last;
	int MaxSize;
} *List,LNode;

List CreatList(int n);
void PrintList(List& L);
void Intersection(List& L1,List& L2,List& L3); 

int main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int m,n;
	cin>>m>>n;
	List La=CreatList(m);
	List Lb=CreatList(n);
	
	List Lc=(List)malloc(sizeof(LNode));
	Lc->last=-1;
	Lc->MaxSize=m; 
	Lc->data = (int*)malloc((Lc->MaxSize)*sizeof(int));
	
	Intersection(La,Lb,Lc);
	PrintList(Lc);
	free(La->data);
	free(La);
	free(Lb->data);
	free(Lb);
	free(Lc->data);
	free(Lc);
	return 0;
}
List CreatList(int n){
	int num;
	List L=(List)malloc(sizeof(LNode));
	L->MaxSize=n;
	L->last=n-1;
	L->data=(int*)malloc(L->MaxSize*sizeof(int));
	for(int i=0;i<=L->last;i++){
		cin>>num;
		L->data[i]=num;
	}
	return L; 
}
void PrintList(List& L){
	if(L->last == -1){
		cout<<"NULL";
		return; 
	} 
	for(int i=0;i<L->last;i++){
		cout<<L->data[i]<<' ';
	}
	cout<<L->data[L->last];
	
}
void Intersection(List& L1,List& L2,List& L3){
	int k=0;
	for(int i=0;i<=L1->last;i++){
		for(int j=0;j<=L2->last;j++){
			if(L1->data[i] == L2->data[j]){
				L3->data[k++] = L1->data[i];
				L3->last++;
			} 
		}
	}
}
