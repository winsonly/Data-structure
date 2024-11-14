/*
�����ʽ:
����� 1 �и��������� n����10 
5
 ������� n �У�ÿ�и���һ��ָ���GET �� PUT���ֱ��ʾ�Ӷ�����ȡ����Ϣ����Ϣ��ӵ������С����ָ���� PUT���������һ����Ϣ���ơ��Լ�һ����������ʾ��Ϣ�����ȼ�������ԽС��ʾ���ȼ�Խ�ߡ���Ϣ�����ǳ��Ȳ����� 10 ���ַ��Ҳ����ո���ַ�������Ŀ��֤��������Ϣ�����ȼ����ظ���������������һ�� GET��

�����ʽ:
����ÿ�� GET ָ���һ���������Ϣ���������ȼ���ߵ���Ϣ�����ƺͲ����������Ϣ������û����Ϣ����� EMPTY QUEUE!������ PUT ָ����û�������
*/
#include<stdio.h>
#include<stdlib.h> 
#include<string.h>

#define MAXNUM 10000;

struct message {
    int priority;
    char name[20];
};

typedef struct message ElementType ;
typedef struct HNode *Heap; /* �ѵ����Ͷ��� */
typedef Heap MaxHeap;
struct HNode {
    ElementType *Data; /* �洢Ԫ�ص����� */
    int Size;          /* ���е�ǰԪ�ظ��� */
    int Capacity;      /* �ѵ�������� */
};


MaxHeap CreateHeap(int MaxSize){
    MaxHeap H = NULL;
    H = (MaxHeap)malloc(sizeof(struct HNode));
    H->Capacity = MaxSize;
    H->Data = (ElementType *)malloc(sizeof(ElementType)*(MaxSize+1));
    H->Data[0].priority = MAXNUM;
    H->Size = 0;
    return H;
}

ElementType CreateElement(char *n,int pri)
{
    ElementType M;
    strcpy(M.name,n);
    M.priority = pri;
    return M;
}

bool Insert(MaxHeap H,ElementType X)
{
    if(H->Size == H->Capacity)return 0;
    int i = ++H->Size;
    for( ;H->Data[i/2].priority < X.priority; i/=2){
        H->Data[i] = H->Data[i/2];
    }
    H->Data[i] = X;
    return 1;
}

void DeleteMax(MaxHeap H)
{
    if(H->Size == 0){
        printf("EMPTY QUEUE!\n"); 
    }
    else{
        printf("%s\n",H->Data[1].name);
        int parent , child;
        parent = 1;
        ElementType temp = H->Data[H->Size--];
        for( ;parent*2<=H->Size ; parent = child){
            child = parent * 2;
            if(child!=H->Size&&H->Data[child+1].priority > H->Data[child].priority)
                child++;
            if(temp.priority > H->Data[child].priority)break;
            else H->Data[parent] = H->Data[child];
        }
        H->Data[parent] = temp;
    }
}


int main()
{
    int n;
    scanf("%d",&n);
    MaxHeap H = CreateHeap(n);
    char ops[20];
    char names[20];
    int pri;
    ElementType temp;
    for(int i=0 ; i<n ; i++){
        scanf("%s",ops);
        if(ops[0]=='P')
        {
            scanf("%s",names);
            scanf("%d",&pri);
            Insert(H,CreateElement(names,pri*-1));
        }
        else
        {
            DeleteMax(H);
         } 
        
    }
    return 0;
}

