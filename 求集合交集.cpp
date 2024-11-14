/*
求整数集合A与整数集合B的交集。

输入格式:
输入有三行：

第一行是A和B的元素个数m和n（m,n <=100）；

第二行是集合A的m个元素；

第三行是集合A的n个元素。

输出格式:
输出交集的所有元素（按照在A集合出现的顺序输出，最后一个输出后面没有空格）。
若交集为空，输出“NULL”。

输入样例:
在这里给出一组输入。例如：

3 4
10 9 2
9 10 8 0
输出样例:
在这里给出相应的输出。例如：

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
