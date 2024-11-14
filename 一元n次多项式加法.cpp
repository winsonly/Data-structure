#include<iostream>
#include<malloc.h>
using namespace std;
//逻辑结构：线性表;存储结构：链式
//时间：O（）；空间：O（）
typedef float ElementType;
typedef struct LNode{
	ElementType coef;	//系数 
	ElementType exponent;	//指数 
	struct LNode* next;
} *List,LNode;

void MakeList(List& L);
void SortList(List& L);	//选择排序法 
void AddLists(List& L1,List& L2);	//L2往L1上加 
void MultiLists(List& L1,List& L2);
void PrintList(List& L);
void MergeNodes(List& L);	//融合相同指数 

int main(){
	List L1,L2;

	MakeList(L1);
	MakeList(L2);
	

	printf("f(X)=");
	PrintList(L1);
	printf("\n");
	
	printf("g(X)=");
	PrintList(L2);
	printf("\n");
		
	AddLists(L1,L2);
	printf("f(X)+g(X)=");
	PrintList(L1);

		
	return 0;
}

//尾插法顺序存多项式 
void MakeList(List& L){
	L=(List)malloc(sizeof(LNode));
	L->next=NULL;
	List p=L,q;
	while(1){
		q=(List)malloc(sizeof(LNode));
		scanf("%f,%f",&q->coef,&q->exponent);
        if (q->coef == 0 && q->exponent == 0) {
            free(q);
            break;
        }
		if(q->coef==0) {
			free(q);
			continue;
		}
		q->next=p->next;
		p->next=q;
		p=q;
	}
	MergeNodes(L);
}

void PrintList(List& L){
	List p=L->next;
	List temp;//辅助释放节点
	if(!p){
		printf("0.0");
		//free(L); 
		return;
	}
	while(p){
		temp=p;
		if(temp->exponent==0){		//解决常数问题 
			printf("%.1f",temp->coef);
		}
		else if(temp->coef==1 || temp->coef==-1){		//解决系数为1问题
			if(temp->coef==-1) printf("-");
			if(temp->exponent==1) printf("X");
			else printf("X^%.0f",temp->exponent);
		}
		else if(temp->exponent==1) printf("%.1fX",temp->coef);//解决指数为1 
		else printf("%.1fX^%.0f",temp->coef,temp->exponent);
		p=p->next;
		if(p){	//解决符号问题 
			if(p->coef>0) printf("+");
		} 
		//free(temp);
	} 
	//free(L); 
}
void SortList(List& L){
	float temp_coef,temp_exponent; 
	List p=L->next;
	while(p){
		List max=p;
		List q=p->next;
		while(q){
			
			if(max->exponent < q->exponent){
				max=q;
			}
			q=q->next;
		}
		temp_exponent=max->exponent;
		max->exponent=p->exponent;
		p->exponent=temp_exponent;
		
		temp_coef=max->coef;
		max->coef=p->coef;
		p->coef=temp_coef;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
		p = p->next;
	}
}
void AddLists(List& L1,List& L2){
	List temp=L1;
	while(temp->next){
		temp=temp->next;
	}
	temp->next=L2->next;
	MergeNodes(L1);
}

void MultiLists(List& L1,List& L2){
	List temp1=L1->next;
	List temp2=L2->next;
	while(temp1){
		while(temp2){
			temp2->coef *= temp1->coef;
			temp2->exponent += temp2->exponent;
			temp2=temp2->next;
		}
	}
} 
void MergeNodes(List& L){
	SortList(L);
	List p=L->next;
	List temp=NULL;
	if(!p) return;
	while(p->next){
		if(p->exponent==p->next->exponent) {
			p->coef += p->next->coef;
			temp=p->next;
			p->next=temp->next;
			free(temp);
		}
		else p=p->next; 
	}
	p=L;	//筛除coef==0的节点 
	while(p->next){
		if(p->next->coef==0){
			temp=p->next;
			p->next=temp->next;
			free(temp);
		} else p=p->next;
	}
}
