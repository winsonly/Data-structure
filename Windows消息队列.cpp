/*
输入格式:
输入第 1 行给出正整数 n（≤10 
5
 ），随后 n 行，每行给出一个指令——GET 或 PUT，分别表示从队列中取出消息或将消息添加到队列中。如果指令是 PUT，后面就有一个消息名称、以及一个正整数表示消息的优先级，此数越小表示优先级越高。消息名称是长度不超过 10 个字符且不含空格的字符串；题目保证队列中消息的优先级无重复，且输入至少有一个 GET。

输出格式:
对于每个 GET 指令，在一行中输出消息队列中优先级最高的消息的名称和参数。如果消息队列中没有消息，输出 EMPTY QUEUE!。对于 PUT 指令则没有输出。
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
typedef struct HNode *Heap; /* 堆的类型定义 */
typedef Heap MaxHeap;
struct HNode {
    ElementType *Data; /* 存储元素的数组 */
    int Size;          /* 堆中当前元素个数 */
    int Capacity;      /* 堆的最大容量 */
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

