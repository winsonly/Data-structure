#include<iostream>
#include<malloc.h>
using namespace std;
//�߼��ṹ�����Ա�;�洢�ṹ����ʽ
//ʱ�䣺O�������ռ䣺O����
typedef float ElementType;
typedef struct LNode{
	ElementType coef;	//ϵ�� 
	ElementType exponent;	//ָ�� 
	struct LNode* next;
} *List,LNode;

void MakeList(List& L);
void SortList(List& L);	//ѡ������ 
void PrintList(List& L);
void MergeNodes(List& L);	//�ں���ָͬ�� 

int main(){
	List L1;
	MakeList(L1);
	printf("f(X)=");
	PrintList(L1);

	return 0;
}

//β�巨˳������ʽ 
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
	List temp;//�����ͷŽڵ�
	if(!p){
		printf("0.0");
		free(L); 
		return;
	}
	while(p){
		temp=p;
		if(temp->exponent==0){		//����������� 
			printf("%.1f",temp->coef);
		}
		else if(temp->coef==1 || temp->coef==-1){		//���ϵ��Ϊ1����
			if(temp->coef==-1) printf("-");
			if(temp->exponent==1) printf("X");
			else printf("X^%.0f",temp->exponent);
		}
		else if(temp->exponent==1) printf("%.1fX",temp->coef);//���ָ��Ϊ1 
		else printf("%.1fX^%.0f",temp->coef,temp->exponent);
		p=p->next;
		if(p){	//����������� 
			if(p->coef>0) printf("+");
		} 
		free(temp);
	} 
	//printf("\n");
	free(L); 
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
	p=L;	//ɸ��coef==0�Ľڵ� 
	while(p->next){
		if(p->next->coef==0){
			temp=p->next;
			p->next=temp->next;
			free(temp);
		} else p=p->next;
	}
}
