#include<iostream>
#define RIGHT MAZE[x][y+1]   // 右方向
#define LEFT MAZE[x][y-1]   // 左方向
#define DOWN MAZE[x+1][y]  // 下方向
#define UP MAZE[x-1][y]  // 上方向
using namespace std; 
typedef struct list{
	int x, y;
	struct list *next;
} node,*link;

int MAZE[10][10];
link push(link path, int x, int y);
link pop(link path, int& x, int& y);
int isExit(int x, int y, int ex, int ey);
void PrintPath(link& path); 

int main(void){
	//ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int n;
	link path = new node;
	path->next=NULL;
	path=push(path,1,1);
	int x = 1;        
	int y = 1;
	
	//创建迷宫        
	cin>>n;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)
			cin>>MAZE[i][j];
		//cout << endl;
	}
 
	// 开始走迷宫
	while (path->next){
		MAZE[x][y] = 2;
		if (RIGHT == 0){
			y++;
			path = push(path, x, y);
		}
		else if (DOWN == 0){
			x++;
			path = push(path, x, y);
		}
		else if (LEFT == 0){
			y--;
			path = push(path, x, y);
		}
		else if (UP == 0){
			x--;
			path = push(path, x, y);
		}
		else if (isExit(x, y, n-2, n-2))
			break;
		else path = pop(path, x, y);
	}
	if(!path->next) cout<<"NO";
	else PrintPath(path);
	return 0;
}
link push(link path, int x, int y){
	link newnode,p=path;
	while(p->next) p=p->next;
	newnode = new node;
	newnode->x = x;
	newnode->y = y;
	newnode->next = p->next;
	p->next = newnode;
	return path;
}
link pop(link path, int& x, int& y){
	link top=path;
	if (path->next != NULL)
	{
		while(top->next->next) top=top->next;
		x = top->x;
		y = top->y;
		delete top->next;
		top->next=NULL;
		return path;
	}
	else
		x--;
	return path;
}
int isExit(int x, int y, int ex, int ey){
	if ((x == ex) && (y == ey)) return 1;
	return 0;
}
void PrintPath(link& path){
	link p=path->next;
	while(p){
		printf("(%d,%d)",p->x,p->y);
		p=p->next;
	}
}
